	workspace "task_scheduler"
        editorintegration "On"
		configurations { "release", "debug" }
        platforms { "Win64" }
        objdir "tmp"

		flags { "ExtraWarnings", "MultiProcessorCompile" }

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

	group "tests"

		project "multi_threaded_detector"
			targetname  "multi_threaded_detector"
			language    "C++"
			kind        "ConsoleApp"
			location    "tests/multi_threaded_detector"
			includedirs { "tests/multi_threaded_detector", "include", "packages/googletest.1.8.0.0/build/native/include" }
			debugdir    "tests/multi_threaded_detector"
			pchheader   "stdafx.h"
			pchsource   "tests/multi_threaded_detector/stdafx.cpp"
			targetname	"multi_threaded_detector.test"

			files
			{
				"*.txt", "**.lua","**.md",
				"tests/multi_threaded_detector/**.h", "tests/multi_threaded_detector/**.cpp",
				"include/*.h",
                "packages/googletest.1.8.0.0/build/native/include/gtest/**.h"
			}

			excludes
			{
			}

			filter "configurations:debug"
				targetdir   "bin/debug"
				debugdir    "samples/basic"
                links       { "packages/googletest.1.8.0.0/build/native/lib/x64/v140/Debug/googletest_v140.lib" }

			filter "configurations:release"
				targetdir   "bin/release"
				debugdir    "samples/basic"
                links       { "packages/googletest.1.8.0.0/build/native/lib/x64/v140/Release/googletest_v140.lib" }

			filter "system:windows"


	group ""