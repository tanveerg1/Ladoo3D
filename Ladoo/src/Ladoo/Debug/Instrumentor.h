#pragma once

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <iomanip>

#include <thread>

namespace Ladoo {

    using FPM = std::chrono::duration<double, std::micro>; // FloatingPointMicroseconds

    struct ProfileResult
    {
        std::string Name;
        
        FPM Start;
        std::chrono::microseconds ElapsedTime;
        std::thread::id ThreadID;
    };

    struct InstrumentationSession
    {
        std::string Name;
    };

    class Instrumentor
    {
    private:
        std::mutex m_Mutex;
        InstrumentationSession* m_CurrentSession;
        std::ofstream m_OutputStream;
    public:
        Instrumentor()
            : m_CurrentSession(nullptr)
        {
        }

        void BeginSession(const std::string& name, const std::string& filepath = "results.json")
        {
            std::lock_guard lock(m_Mutex);
            if (m_CurrentSession)
            {
                if (Log::GetCoreLogger())
                {
                    LD_CORE_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' already open", name, m_CurrentSession->Name);
                }
                InternalEndSession();
            }

            m_OutputStream.open(filepath);

            if (m_OutputStream.is_open())
            {
                WriteHeader();
                m_CurrentSession = new InstrumentationSession{ name };
            }
            else
            {
                if (Log::GetCoreLogger())
                {
                    LD_CORE_ERROR("Instrumentor could not open results file '{0}'", filepath);
                }
            }

        }

        void EndSession()
        {
            std::lock_guard lock(m_Mutex);
            InternalEndSession();
        }

        void WriteProfile(const ProfileResult& result)
        {
            //old colde to be removed
            //if (m_ProfileCount++ > 0)
            //    m_OutputStream << ",";

            std::stringstream json;

            std::string name = result.Name;
            std::replace(name.begin(), name.end(), '"', '\'');

            //old code to be removed
            //m_OutputStream << "{";
            //m_OutputStream << "\"cat\":\"function\",";
            //m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
            //m_OutputStream << "\"name\":\"" << name << "\",";
            //m_OutputStream << "\"ph\":\"X\",";
            //m_OutputStream << "\"pid\":0,";
            //m_OutputStream << "\"tid\":" << result.ThreadID << ",";
            //m_OutputStream << "\"ts\":" << result.Start;
            //m_OutputStream << "}";

            json << "{";
            json << "\"cat\":\"function\",";
            json << "\"dur\":" << (result.ElapsedTime.count()) << ',';
            json << "\"name\":\"" << name << "\",";
            json << "\"ph\":\"X\",";
            json << "\"pid\":0,";
            json << "\"tid\":" << result.ThreadID << ",";
            json << "\"ts\":" << result.Start.count();
            json << "}";

            std::lock_guard lock(m_Mutex);
            if (m_CurrentSession)
            {
                m_OutputStream << json.str();
                m_OutputStream.flush();
            }
        }

        void WriteHeader()
        {
            m_OutputStream << "{\"otherData\": {},\"traceEvents\":[{}";
            m_OutputStream.flush();
        }

        void WriteFooter()
        {
            m_OutputStream << "]}";
            m_OutputStream.flush();
        }

        static Instrumentor& Get()
        {
            static Instrumentor instance;
            return instance;
        }

        void InternalEndSession()
        {
            if (m_CurrentSession)
            {
                WriteFooter();
                m_OutputStream.close();
                delete m_CurrentSession;
                m_CurrentSession = nullptr;
            }
        }
    };

    class InstrumentationTimer
    {
    public:
        InstrumentationTimer(const char* name)
            : m_Name(name), m_Stopped(false)
        {
            m_StartTimepoint = std::chrono::steady_clock::now();
        }

        ~InstrumentationTimer()
        {
            if (!m_Stopped)
                Stop();
        }

        void Stop()
        {
            //old code to be removed
            //auto endTimepoint = std::chrono::high_resolution_clock::now();

            //long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
            //long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

            //uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());

            auto endTimepoint = std::chrono::steady_clock::now();
            auto highResolutinStart = FPM{ m_StartTimepoint.time_since_epoch() };
            auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch();

            Instrumentor::Get().WriteProfile({ m_Name, highResolutinStart, elapsedTime, std::this_thread::get_id() });

            m_Stopped = true;
        }
    private:
        const char* m_Name;
        std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
        bool m_Stopped;
    };
}

#define LD_PROFILE 1
#if LD_PROFILE
    #if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
    #define LD_FUNCSIG __PRETTY_FUNCTION__
    #elif defined(__DMC__) && (__DMC__ >= 0x810)
    #define LD_FUNCSIG __PRETTY_FUNCTION__
    #elif defined(__FUNCSIG__)
    #define LD_FUNCSIG __FUNCSIG__
    #elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
    #define LD_FUNCSIG __FUNCTION__
    #elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
    #define LD_FUNCSIG __FUNC__
    #elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
    #define LD_FUNCSIG __func__
    #elif defined(__cplusplus) && (__cplusplus >= 201103)
    #define LD_FUNCSIG __func__
    #else
    #define LD_FUNCSIG "LD_FUNCSIG unknown!"
    #endif

    #define LD_BEGIN_PROFILING(name, filepath) ::Ladoo::Instrumentor::Get().BeginSession(name, filepath)
    #define LD_END_PROFILING()                 ::Ladoo::Instrumentor::Get().EndSession()
    #define LD_PROFILE_SCOPE(name)             ::Ladoo::InstrumentationTimer timer##__LINE__(name)
    #define LD_PROFILE_FUNCTION()              LD_PROFILE_SCOPE(LD_FUNCSIG)
#else
    #define LD_BEGIN_PROFILING(name, filepath)
    #define LD_END_PROFILING()
    #define LD_PROFILE_SCOPE(name)
    #define LD_PROFILE_FUNCTION()
#endif