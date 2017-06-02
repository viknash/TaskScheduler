pushd %~dp0
pushd ..\samples\profile
python ../../deps/IntelSEAPI/runtool/sea_runtool.py -b ../../deps/IntelSEAPI/bin -o ../samples/profile/sea -f gt qt gv dgml --stacks ! ../../bin/debug/profile.exe
popd
popd
pause