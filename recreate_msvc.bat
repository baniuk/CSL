rem Creates MSVC project files basing on cmake scripts

SETLOCAL ENABLEEXTENSIONS

rem delete all cmake stuff
IF NOT EXIST bin mkdir bin
echo off
cd bin
FOR /R %%A IN (*) DO IF %%~nA%%~xA==cmake_install.cmake del /q %%~fA
FOR /R %%A IN (*) DO IF %%~nA%%~xA==CMakeCache.txt del /q %%~fA
FOR /D /R %%X IN (CMakeFiles*) DO rmdir "%%X" /s /q
echo on
cmake -DCMAKE_BUILD_TYPE=Debug -G "Visual Studio 11 2012" --graphviz=Dep.dot ..\
dot -Tpng Dep.dot > Dep.png
cd ..