@echo off

pushd %~dp0
pushd ..
tools\premake\premake5 vs2015
popd
popd