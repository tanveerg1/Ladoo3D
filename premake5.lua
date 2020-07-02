workspace "Ladoo"
	architecture "x64"
	startproject "Sandbox"

	configurations { "Debug", "Release", "Dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Ladoo/vendor/GLFW/include"
IncludeDir["Glad"] = "Ladoo/vendor/Glad/include"
IncludeDir["ImGui"] = "Ladoo/vendor/imgui"

include "Ladoo/vendor/GLFW" 
include "Ladoo/vendor/Glad" 
include "Ladoo/vendor/imgui" 

project "Ladoo"
	location "Ladoo"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "ldpch.h"
	pchsource "Ladoo/src/ldpch.cpp"

	files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

	includedirs { "%{prj.name}/src", "%{prj.name}/vendor/spdlog/include", "%{IncludeDir.GLFW}", "%{IncludeDir.Glad}", "%{IncludeDir.ImGui}" }
	
	links { "GLFW", "Glad", "ImGui", "opengl32.lib" }

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines { "LD_PLATFORM_WINDOWS", "LD_BUILD_DLL", "GLFW_INCLUDE_NONE" }

		postbuildcommands { ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"") }

	filter "configurations:Debug"
		defines "LD_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "LD_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "LD_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

	includedirs { "Ladoo/vendor/spdlog/include", "Ladoo/src" }

	links { "Ladoo" }

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines { "LD_PLATFORM_WINDOWS" }

	filter "configurations:Debug"
		defines "LD_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "LD_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "LD_DIST"
		runtime "Release"
		optimize "On"