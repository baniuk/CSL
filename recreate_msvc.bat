rem Creates MSVC project files basing on cmake scripts

IF NOT EXIST bin mkdir bin
rem clear cache
IF EXIST bin\CMakeCache.txt del bin\CMakeCache.txt

cd bin

cmake -G "Visual Studio 11 2012" ..\
cd ..