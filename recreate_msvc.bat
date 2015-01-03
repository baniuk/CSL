rem Creates MSVC project files basing on cmake scripts

SETLOCAL ENABLEEXTENSIONS

rem delete all cmake stuff
IF NOT EXIST build mkdir build
echo off
cd build
rem FOR /R %%A IN (*) DO IF %%~nA%%~xA==cmake_install.cmake del /q %%~fA
rem FOR /R %%A IN (*) DO IF %%~nA%%~xA==Makefile del /q %%~fA
del /q CMakeCache.txt
rem FOR /D /R %%X IN (CMakeFiles*) DO rmdir "%%X" /s /q
echo on
cmake -DCMAKE_BUILD_TYPE=Debug -G "Visual Studio 12 2013" --graphviz=Dep.dot ..\
dot -Tpng Dep.dot > Dep.png
cd ..