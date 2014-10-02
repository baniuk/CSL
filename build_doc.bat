rem Doxygen building script
rem Results are in doc/ directory
echo off

IF EXIST doc rmdir doc /s /q
mkdir doc

cd configs
..\tools\doxygen1.8.8\doxygen.exe doxyfile
cd ..