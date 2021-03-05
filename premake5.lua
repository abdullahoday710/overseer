workspace "Overseer"
	architecture "x86_64"
	configurations
	{
		"Debug",
		"Release",
	}

	IncludeDir = {}
	IncludeDir["libanvil"] = "%{wks.location}/libanvil/include/"
	IncludeDir["regex"] = "%{wks.location}/boostregex/include/"
	IncludeDir["zlib"] = "%{wks.location}/zlib/"

	project "Overseer"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17"
		staticruntime "on"

		targetdir ("%{wks.location}/build/")
		objdir ("%{wks.location}/build-int/")

		files {
			"overseer/src/**.h",
			"overseer/src/**.cpp",
			"libanvil/**.cpp",
			"boostregex/**.cpp",
			"zlib/**.c",
		}

		excludes { "zlib/gun.c" }

		links {
			"LIBCMTD"
		}
		includedirs {
			"src/",
			"%{IncludeDir.libanvil}",
			"%{IncludeDir.regex}",
			"%{IncludeDir.zlib}",

		}

		filter "system:windows"
			systemversion "latest"

		filter "configurations:Debug"
			defines "OSE_DEBUG"
			runtime "Debug"
			symbols "on"
			optimize "off"

		filter "configurations:Release"
			defines "OSE_RELEASE"
			runtime "Release"
			optimize "on"