rem Main build script for project.
rem Performs build without deleting all previous results
rem Do not run tests
echo off

rem clear cache
IF NOT EXIST bin mkdir bin
rem clear cache
IF EXIST bin\CMakeCache.txt del bin\CMakeCache.txt

rem start build process from bin dir
cd bin
rem Additional flags can be passed here or in CMakeLists.txt
cmake -DCMAKE_BUILD_TYPE=Debug -G "NMake Makefiles" ..\
nmake
cd ..
GOTO :EOF
:ERROR
echo Error occured
GOTO :EOF