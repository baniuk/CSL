###############################################################################
#    \brief   Macros and functions                                            #
#    \author  Piotr Baniukiewicz                                              #
#    \date    28.11.2014                                                      #
#    \remarks Any changes in External projexts must be reflected in           #
#             getPathToExternals                                              #
#                                                                             #
###############################################################################

# Function returns to caller variables pointing to
# SRC and LIB with general name syntax:
# ALL_EXTERNAL_[LIBS|INCS] which contain all paths space 
# separated for including in functions
function(getPathToExternals)
	# GTEST
	ExternalProject_Get_Property(googletest install_dir)
	ExternalProject_Get_Property(googletest source_dir)
	set(googletest_LIB ${install_dir}/lib)
	set(googletest_INC ${source_dir}/include)

	ExternalProject_Get_Property(PBToolset install_dir)
	ExternalProject_Get_Property(PBToolset source_dir)
	set(PBToolset_LIB ${install_dir}/lib)
	set(PBToolset_INC ${source_dir}/include)

	ExternalProject_Get_Property(clapack install_dir)
	ExternalProject_Get_Property(clapack source_dir)
	set(clapack_LIB ${install_dir}/lib)
	set(clapack_INC ${source_dir}/include)

	ExternalProject_Get_Property(levmar install_dir)
	ExternalProject_Get_Property(levmar source_dir)
	set(levmar_LIB ${install_dir}/lib)
	set(levmar_INC ${source_dir})

	set(ALL_EXTERNAL_LIBS ${googletest_LIB} ${PBToolset_LIB} ${clapack_LIB} ${levmar_LIB} PARENT_SCOPE)
	set(ALL_EXTERNAL_INCS ${googletest_INC} ${PBToolset_INC} ${clapack_INC} ${levmar_INC} PARENT_SCOPE)
endfunction()


# Adds subdirectories for further processing
# makro zakłada ze w danym katalogu wszystkie podkatalogi zawierają pliki cmake.txt
# \param[in]	curdir - CMAKE_CURRENT_LIST_DIR directory to process
macro(addSubirectories curdir)
	file(GLOB children RELATIVE ${curdir} ${curdir}/*)
  	set(dirlist "")
  	foreach(child ${children})
    	if(IS_DIRECTORY ${curdir}/${child})
    		add_subdirectory(${child})
    	endif()
  	endforeach()
endmacro()

# Adds TEST
# add test that depends on ALL files in directory (all for one target)
# automatically gets all paths to external dependencies
# Provides paths for:
#	All external projects (LIB/INC)
#	./include dir (all includes paths in source files are relative to ./include)
# \param[in]	LOCAL_PROJECT_NAME - name of the test project
# \param[in]	libs - 	list of libs to link to (external libs are automatically linked inside function,
#						except those that do not support auto linking)
# \param[in]	dependencies - names of porjects that LOCAL_PROJECT_NAME depends on
# \todo for multi-target projects compile options should be set by function
function(addTest LOCAL_PROJECT_NAME libs dependencies)
	project(${LOCAL_PROJECT_NAME})
	# external dependencies in format ExternalProject_[INC LIB]
	getPathToExternals()
	# add all files in DIRECTORY
	file(GLOB local_files ${CMAKE_CURRENT_SOURCE_DIR} "*.h" "*.cpp" "*.rc")
	# important if test is run with paameters or external files
	IF(${CMAKE_GENERATOR} MATCHES "^(Visual Studio)")
		set(CMAKE_CURRENT_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}")
	ENDIF()
	# set includes - external
	include_directories(${ALL_EXTERNAL_INCS} ${CMAKE_SOURCE_DIR}/include)
	# link directories - external
	link_directories(${ALL_EXTERNAL_LIBS})
	# build executable
	add_executable(${LOCAL_PROJECT_NAME} ${local_files})
	# important for gtest MSVC
	target_compile_options(${LOCAL_PROJECT_NAME} PUBLIC -D_VARIADIC_MAX=10)
	# externals (BOOST links automatically)
	target_link_libraries(	${LOCAL_PROJECT_NAME}
							gtest${CMAKE_STATIC_LIBRARY_SUFFIX} 
							gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX})
	target_link_libraries(	${LOCAL_PROJECT_NAME} ${libs})
	message(STATUS "-------- ${libs} -------- ${dependencies}")

	# depends on:
	IF(dependencies)
		add_dependencies(${LOCAL_PROJECT_NAME} ${dependencies})
	ENDIF()
	# add TEST
	add_test(${LOCAL_PROJECT_NAME} ${LOCAL_PROJECT_NAME})
endfunction()

# Creates test template of GTest Running
# uses _GTest_starter.cpp that must be in ./CMake dir
function(addTestStarter)
	# gets current date and store in DATE var (the same as in _GTest_starter.cpp)
	string(TIMESTAMP DATE)
	# copy to dest dir
	configure_file(	${CMAKE_SOURCE_DIR}/CMake/_GTest_starter.cpp
					${CMAKE_CURRENT_SOURCE_DIR}/__GTest_starter.cpp
               		@ONLY)
endfunction()

# Creates test template of GTest Running with Pantheios logging
# uses _GTest_starter_logger.cpp that must be in ./CMake dir
function(addTestStarterLogger proces_id log_file)
	# gets current date and store in DATE var (the same as in _GTest_starter.cpp)
	string(TIMESTAMP DATE)
	set(PROCESS_IDENTITY ${proces_id})
	set(LOG_FILENAME ${log_file})
	# copy to dest dir
	configure_file(	${CMAKE_SOURCE_DIR}/CMake/_GTest_starter_logger.cpp
					${CMAKE_CURRENT_SOURCE_DIR}/__GTest_starter_logger.cpp
               		@ONLY)
endfunction()


