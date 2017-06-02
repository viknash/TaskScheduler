pushd $dp0
python ../deps/IntelSEAPI/runtool/sea_runtool.py --bindir ../samples/profile -b ../deps/IntelSEAPI -o ../samples/profile -f gt qt gv dgml --stacks ! ../bin/debug/profile.exe
popd
pause