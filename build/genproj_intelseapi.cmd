@echo off

pushd %~dp0
pushd ..\deps\IntelSEAPI
..\..\tools\cmake\bin\cmake . -G"Visual Studio 14 Win64" -DARCH_64=1
popd