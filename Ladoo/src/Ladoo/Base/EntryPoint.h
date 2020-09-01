#pragma once

#ifdef LD_PLATFORM_WINDOWS

extern Ladoo::Application* Ladoo::CreateApplication();

int main(int argc, char** argv) 
{

	Ladoo::Log::Init();
	LD_CORE_WARN("Initialized Log!");
	int a = 5;
	LD_INFO("Hello! Var={0}", a);

	LD_BEGIN_PROFILING("Startup", "LadooProfile-Startup.json");
	auto app = Ladoo::CreateApplication();
	LD_END_PROFILING();
	
	LD_BEGIN_PROFILING("Runtime", "LadooProfile-Runtime.json");
	app->Run();
	LD_END_PROFILING();

	LD_BEGIN_PROFILING("Shutdown", "LadooProfile-Shutdown.json");
	delete app;
	LD_END_PROFILING();
}

#endif