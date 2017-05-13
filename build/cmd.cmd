@echo off
pushd %~dp0\..
title TaskScheduler Environment

REM Detect 32/64 bit windows
if exist "%SYSTEMDRIVE%\Program Files (x86)\" (
set SYS_ARCH=64
) else (
set SYS_ARCH=32
)

set ROOT_DIR=%CD%
set PATH=%CD%\bin;%CD%\tools\bin;%PATH%
set PATH=%CD%\build;%PATH%

REM Setup Visual Studio Environment
doskey devenv=devenv.exe /useenv $*
IF "%VS140COMNTOOLS%"=="" (
	ECHO Visual Studio 2012
	%comspec% /k "%VS110COMNTOOLS%\..\..\VC\vcvarsall.bat" x86
) ELSE (
	ECHO Visual Studio 2015
	%comspec% /k "%VS140COMNTOOLS%\..\..\VC\vcvarsall.bat" x86
)
popd