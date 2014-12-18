# -*- coding: utf-8 -*-
## @package CreateModuleFiles
# Skrytpt tworzy strukturę katalogów i plików.
#
# Tworzy puste pliki `*.h` oraz `*.cpp` o nazwie przekazanej przez parametr `param`
# w podkatalogach o nazwie parametru `param` w katalogach:
# \li ``Tests``
# \li ``src``
# \li ``include``
# Musi być uruchomiony z głównego katalogu \b projektu
# Składnia `CreateModuleFiles.py ModuleName` 

import glob # provides a function for making file lists from directory wildcard searches
import os
import sys # Common utility scripts often need to process command line arguments.

# sprawdzanie parametrów wejściowych
if len(sys.argv) < 2:
    print("Zła składnia: CreateModuleFiles.py ModuleName")
    sys.exit(1)
ModuleName=sys.argv[1]

# list of required subdirs
RequiredSubdir = ['Tests', 'src', 'include']
FileExtension = ['.cpp', '.cpp', '.h'] # musi paować do RequiredSubdir
CMakeFiles = [True, True, False]  # musi pasowac do listy katalogów, określa czy w danym katalogu ma być CMakeLists.txt 

LocalDir = os.getcwd() # local dir (must be project root)
print("Katalog lokalny",LocalDir)
# test for required subdirectories
DirTest = True # po testowaniu zawiera True jesli sa wszystkie podkatalogi
for dirs in RequiredSubdir:
    print("Test for: ", dirs, " ", end="")
    JoinedPath = os.path.join(LocalDir,dirs)
    if(os.path.isdir(JoinedPath)):
        print("\tOK")
        DirTest = DirTest and True
    else:
        print("\tFail")
        DirTest = DirTest and False
if not DirTest:
    print("Brakuje katalogu")
    print("Czy zostało uruchomione z root projektu?")
    # exit(1)
else:
    print("Tworzenie struktury")
    l = 0
    for dirs in RequiredSubdir:
        JoinedPath = os.path.join(LocalDir,dirs, ModuleName) # łącze lokalny dir z nazwą modułu (dir)
        if not os.path.isdir(JoinedPath):   # czy ten katalog istnieje?
            os.makedirs(JoinedPath)         # jeśli nie to tworzymu
        FileName = os.path.join(JoinedPath, ModuleName+FileExtension[l])    # generowanie nazwy pliku wraz ze scierzką (lokalna + nazwa modułu + nazwapliku + rozszerzenie)
        print("\t", FileName)
        open(FileName, 'a').close() # tworzenie pustego pliku cpp lub h
        if CMakeFiles[l]:   # jesli ma być CMakeLists.txt
            FileName = os.path.join(JoinedPath, "CMakeLists.txt")    # generowanie nazwy pliku wraz ze sciezką
            open(FileName, 'a').close() # tworzenie pustego pliku cmake
            print("\t", FileName)
        l = l + 1   # indeksacja po rozszerzeniach przypisanych do okreslonych katalogów
        
        

