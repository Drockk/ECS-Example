workspace "ECS Example"
	architecture "x86_64"
	startproject "ecs"

	configurations
	{
		"Debug",
		"Release"
	}

	flags
	{
		"MultiProcessorCompile"
	}

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    project "ecs"
	    kind "ConsoleApp"
	    language "C++"
	    cppdialect "C++17"
	    staticruntime "off"

	    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	    objdir ("%{wks.location}/bin/int/" .. outputdir .. "/%{prj.name}")

	    files
	    {
		    "Source/**.h",
		    "Source/**.cpp",
	    }

	    defines
	    {
		    "_CRT_SECURE_NO_WARNINGS",
	    }

	    includedirs
	    {
		    "Source",
		    "%{wks.location}/entt/include"
	    }

	    links
	    {
	    }

	    filter "system:windows"
		    systemversion "latest"

		    defines
		    {
		    }

	    filter "configurations:Debug"
		    runtime "Debug"
		    symbols "on"

		    links
		    {
		    }

	    filter "configurations:Release"
		    runtime "Release"
		    optimize "on"

		    links
		    {
		    }
