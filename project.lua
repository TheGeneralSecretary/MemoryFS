project "MemoryFS"
kind "ConsoleApp"
language "C++"
cppdialect "C++20"
staticruntime "off"

targetdir ("%{wks.location}/build/" .. outputdir .. "/%{prj.name}")
objdir ("%{wks.location}/build/intermediates/" .. outputdir .. "/%{prj.name}")

pchheader "buildpch.h"
pchsource "Source/buildpch.cpp"

files
{
	"Source/**.h",
	"Source/**.cpp",
	"Source/**.c",
}

includedirs
{
	"Source",
	"%{IncludeDir.spdlog}",
	"%{IncludeDir.winfsp}",
}

libdirs
{
	"%{LibDir.winfsp}",
}

links
{
	"spdlog",
	"winfsp-x64",
}

filter "files:**.c"
	flags { "NoPCH" }

filter "system:windows"
	systemversion "latest"

	defines
	{
		"BUILD_PLATFORM_WINDOWS",
	}

	links
	{
		"delayimp",
	}

	linkoptions
	{
		"/DELAYLOAD:winfsp-x64.dll",
	}

filter "system:linux"
	systemversion "latest"

	defines
	{
		"BUILD_PLATFORM_LINUX",
	}

filter "configurations:Debug"
	defines "BUILD_DEBUG"
	runtime "Debug"
	symbols "On"

filter "configurations:Release"
	defines "BUILD_RELEASE"
	runtime "Release"
	optimize "On"
