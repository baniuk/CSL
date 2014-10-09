# CMake build script for PBToolset

cmake_minimum_required (VERSION 3.0.2)

find_package(Subversion REQUIRED)

# do ustawienia
set(ROOT_PROJECT_NAME "LabView_Extensions")
#set(PBToolset_GIT_REPOSITORY https://github.com/baniuk/PBToolset.git) 
set(PBToolset_GIT_REPOSITORY i:/Projekty/PBToolset)
set(PBToolset_GIT_TAG feature/DumpAll)

project(${ROOT_PROJECT_NAME})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# set additional compiler flags
IF (${WIN32})
	# default RELEASE flags /DWIN32 /D_WINDOWS /W3 /GR /EHsc /MP /MD /O2 /Ob2 /D NDEBUG
	SET(EXTRA_COMPILER_FLAGS "/MP")
ELSEIF (${UNIX})
	SET(EXTRA_COMPILER_FLAGS "") 
ELSE (${WIN32})
	message(FATAL_ERROR "Wrong System")
ENDIF(${WIN32})	

# FORCE flag is necessary for updating default variable in cmake cache
# final flags results from  CMAKE_CXX_FLAGS & (CMAKE_CXX_FLAGS_DEBUG | CMAKE_CXX_FLAGS_RELEASE)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_COMPILER_FLAGS}" CACHE STRING "" FORCE)

# create lib output directory that can be removed by clean-build
file(MAKE_DIRECTORY lib)
# create doc output directory that can be removed by clean-build
file(MAKE_DIRECTORY doc)

enable_language(RC)

include(ExternalProject)
add_subdirectory(External_dep)

# additional subdirs are there - see src dir
add_subdirectory(src)

enable_testing()
add_subdirectory(tests)