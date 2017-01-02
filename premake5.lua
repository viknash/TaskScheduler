	workspace "task_scheduler"
        editorintegration "On"
		configurations { "release", "debug" }
        platforms { "Win64", "Win64-Clang", "Win64-MSClang" }
        objdir "tmp"

        filter { "platforms:Win64" }
            system "Windows"
            architecture "x64"
            toolset "v140"
		    flags { "ExtraWarnings", "MultiProcessorCompile" }
            buildoptions    { "/GR-", "/doc" }

        filter { "platforms:Win64-Clang" }
            system "Windows"
            architecture "x64"
            toolset "msc-llvm-vs2014"

        filter { "platforms:Win64-MSClang" }
            system "Windows"
            architecture "x64"
            toolset "v140_clang_c2"
            buildoptions    { "-frtti", "-fms-compatibility" }

		filter "configurations:debug"
			defines     "_DEBUG"
            links { "MSVCRTD.LIB" }
            linkoptions { "/NODEFAULTLIB:msvcrt" }

		filter "configurations:release"
			defines     "NDEBUG"
			optimize    "Full"
			flags       { "NoBufferSecurityCheck", "NoRuntimeChecks" }

		filter { "configurations:debug", "platforms:Win64" }
			symbols		"On"

		filter { "configurations:debug", "platforms:Win64-MSClang" }
			buildoptions    { "-g2", "-Wall" }

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
			includedirs { "samples/basic", "include", "samples" }
			debugdir    "samples/basic"
			pchheader   "stdafx.h"
			pchsource   "samples/basic/stdafx.cpp"

			files
			{
				"*.txt", "**.lua","**.md",
				"samples/basic/**.h", "samples/basic/**.cpp",
				"include/*.h",
                "samples/common/**.h", "samples/common/**.cpp"
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