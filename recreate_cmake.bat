rem Main build script for project.
rem Performs build without deleting all previous results
rem Do not run tests
echo off
rem delete all cmake stuff
IF NOT EXIST bin mkdir bin
echo off
cd bin
FOR /R %%A IN (*) DO IF %%~nA%%~xA==cmake_install.cmake del /q %%~fA
FOR /R %%A IN (*) DO IF %%~nA%%~xA==CMakeCache.txt del /q %%~fA
FOR /D /R %%X IN (CMakeFiles*) DO rmdir "%%X" /s /q
echo on
rem Additional flags can be passed here or in CMakeLists.txt
cmake -DCMAKE_BUILD_TYPE=Debug -G "NMake Makefiles" --graphviz=Dep.dot ..\
dot -Tpng Dep.dot > Dep.png
nmake
cd ..
GOTO :EOF
:ERROR
echo Error occured
GOTO :EOF