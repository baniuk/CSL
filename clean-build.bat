rem Main build script for project.
rem Performs clean build deleting all previous results
echo off

rem clear all dirs
IF EXIST doc rmdir doc /s /q
IF EXIST bin rmdir bin /s /q
IF EXIST build rmdir build /s/q
rem delete all external projects in Externals
FOR /D /R %%X IN (Externals\*) DO rmdir "%%X" /s /q

rem recreate dirs
mkdir build

rem start build process from build dir
cd build
rem Additional flags can be passed here or in CMakeLists.txt
cmake -DCMAKE_BUILD_TYPE=Debug -G "NMake Makefiles" ..\
IF %ERRORLEVEL% NEQ 0 goto :ERROR
nmake
ctest --verbose
cd ..
GOTO :EOF
:ERROR
echo Error occured
cd ..
GOTO :EOF