rem Doxygen building script
rem Results are in doc/ directory
echo off

IF EXIST doc rmdir doc /s /q
mkdir doc

cd configs
doxygen.exe doxyfile
cd ..