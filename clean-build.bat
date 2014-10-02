rem Main build script for project.
rem Performs clean build deleting all previous results
echo off

rem Check for tools
svn --version
IF %ERRORLEVEL% NEQ 0 GOTO :ERROR

rem clear all dirs
IF EXIST doc rmdir doc /s /q
IF EXIST bin rmdir bin /s /q
IF EXIST lib rmdir lib /s/q

rem recreate dirs
mkdir doc
mkdir bin
rem mkdir lib

rem start build process from bin dir
cd bin
rem Additional flags can be passed here or in CMakeLists.txt
cmake -DCMAKE_BUILD_TYPE=Debug -G "NMake Makefiles" ..\
nmake
ctest --verbose
cd ..
GOTO :EOF
:ERROR
echo Error occured
GOTO :EOF