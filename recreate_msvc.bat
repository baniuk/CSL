rem Creates MSVC project files basing on cmake scripts

IF EXIST bin rmdir bin /s /q
mkdir bin
cd bin

cmake -G "Visual Studio 11 2012" ..\
cd ..