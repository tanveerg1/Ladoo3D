workspace "Ladoo"
	architecture "x64"
	startproject "Sandbox"

	configurations { "Debug", "Release", "Dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Ladoo/vendor/GLFW/include"
IncludeDir["Glad"] = "Ladoo/vendor/Glad/include"
IncludeDir["ImGui"] = "Ladoo/vendor/imgui"
IncludeDir["glm"] = "Ladoo/vendor/glm"

group "Dependencies"
	include "Ladoo/vendor/GLFW" 
	include "Ladoo/vendor/Glad" 
	include "Ladoo/vendor/imgui"
group ""

project "Ladoo"
	location "Ladoo"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "ldpch.h"
	pchsource "Ladoo/src/ldpch.cpp"

	files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp", "%{prj.name}/vendor/glm/glm/**.hpp", "%{prj.name}/vendor/glm/glm/**.inl" }

	defines { "_CRT_SECURE_NO_WARNINGS" }
	
	includedirs { "%{prj.name}/src", "%{prj.name}/vendor/spdlog/include", "%{IncludeDir.GLFW}", "%{IncludeDir.Glad}", "%{IncludeDir.ImGui}", "%{IncludeDir.glm}" }
	
	links { "GLFW", "Glad", "ImGui", "opengl32.lib" }

	filter "system:windows"
		systemversion "latest"

		defines { "LD_PLATFORM_WINDOWS", "LD_BUILD_DLL", "GLFW_INCLUDE_NONE" }

	filter "configurations:Debug"
		defines "LD_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "LD_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "LD_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

	includedirs { "Ladoo/vendor/spdlog/include", "Ladoo/src", "Ladoo/vendor", "%{IncludeDir.glm}" }

	links { "Ladoo" }

	filter "system:windows"
		systemversion "latest"

		defines { "LD_PLATFORM_WINDOWS" }

	filter "configurations:Debug"
		defines "LD_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "LD_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "LD_DIST"
		runtime "Release"
		optimize "on"