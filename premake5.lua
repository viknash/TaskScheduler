	workspace "task_scheduler"
        editorintegration "On"
		configurations { "release", "debug" }
        platforms { "Win64" }
        objdir "tmp"

		flags { "ExtraWarnings", "StaticRuntime", "MultiProcessorCompile" }

        filter { "platforms:Win64" }
            system "Windows"
            architecture "x64"

		filter "configurations:debug"
			defines     "_DEBUG"
			symbols		"On"

		filter "configurations:release"
			defines     "NDEBUG"
			optimize    "Full"
			flags       { "NoBufferSecurityCheck", "NoRuntimeChecks" }

		filter "action:vs*"
			defines     { "_CRT_SECURE_NO_DEPRECATE", "_CRT_SECURE_NO_WARNINGS", "_CRT_NONSTDC_NO_WARNINGS" }

		filter { "system:windows", "configurations:release" }
			flags       { "NoIncrementalLink", "LinkTimeOptimization" }

	group "samples"
	
		project "basic"
			targetname  "basic"
			language    "C++"
			kind        "ConsoleApp"
			location    "samples/basic"
			includedirs { "samples/basic", "include" }
			debugdir    "samples/basic"
			pchheader   "stdafx.h"
			pchsource   "samples/basic/stdafx.cpp"

			files
			{
				"*.txt", "**.lua","**.md",
				"samples/basic/**.h", "samples/basic/**.cpp",
				"include/*.h"
			}

			excludes
			{
			}

			filter "configurations:debug"
				targetdir   "bin/debug"
				debugdir    "samples/basic"

			filter "configurations:release"
				targetdir   "bin/release"
				debugdir    "samples/basic"

			filter "system:windows"

	group ""