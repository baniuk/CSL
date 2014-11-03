# CMake build script for CASELOT

cmake_minimum_required (VERSION 3.0.2)
# check for external dependencies - OpenCV
# OpenCV must be installed and env variable OPENCV_DIR must be st poining to OpenCVConfig.cmake Moreover correct bin (dlls) dir must be set in PATH
# vc8 = Visual Studio 2005
# vc9 = Visual Studio 2008
# vc10 = Visual Studio 2010
# vc11 = Visual Studio 2012
# vc12 = Visual Studio 2013
IF(NOT DEFINED ENV{OPENCV_DIR}) 
	message(FATAL_ERROR "Env variable OPENCV_DIR not set. It must point to location of OpenCVConfig.cmake file") 
ELSE ()
	# for OpenCV find package
	set(OpenCV_DIR $ENV{OPENCV_DIR}) 
ENDIF() 

# If these variables are set in env build is performed offline:
# 	PBToolset_GIT_REPOSITORY - path to PBToolset git repository (local)
#	GTest_SVN_REPOSITORY - any value (gtest must be in /external_dep/gtest)
# WARNING - Paths must be in unix mode /
IF(DEFINED ENV{PBToolset_GIT_REPOSITORY})
	set(PBToolset_GIT_REPOSITORY $ENV{PBToolset_GIT_REPOSITORY})
	message("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
	message("Use local PBToolset repo " ${PBToolset_GIT_REPOSITORY})
	message("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
ELSE ()
	set(PBToolset_GIT_REPOSITORY https://github.com/baniuk/PBToolset.git) 
ENDIF()
set(PBToolset_GIT_TAG master)
IF(DEFINED ENV{GTest_SVN_REPOSITORY})
	set(GTest_SVN_REPOSITORY "")
	message("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
	message("Use local gtest repo " External_dep/gtest)
	message("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
ELSE ()
	set(GTest_SVN_REPOSITORY http://googletest.googlecode.com/svn/trunk/) 
ENDIF()

# set additional cmake modules and check dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)
find_package(Subversion REQUIRED)
find_package(OpenCV REQUIRED)

# do ustawienia
set(ROOT_PROJECT_NAME "LabView_Extensions")

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