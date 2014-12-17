# rzeczy do zmiany
set(LOCAL_PROJECT_NAME ErrorHandling)
set(VERSION_MAJOR 1) # wersje powinny być skorelowane z /version w pliku
set(VERSION_MINOR 0)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/resources.rc.in
  ${CMAKE_CURRENT_BINARY_DIR}/resources.rc
  @ONLY)

project(${LOCAL_PROJECT_NAME})

set(libs "")
set(dep "")
addLibrary(	SHARED 							# type
			${LOCAL_PROJECT_NAME}_DLL		# name of the project
			${LOCAL_PROJECT_NAME}_DLL		# name of the LIBRARY
			"${libs}"						# libs to link
			"${dep}"						# dependencies
			dllmain.cpp
			${CMAKE_CURRENT_BINARY_DIR}/resources.rc
			errordef.rc) # files to build

addLibrary(	SHARED 							# type
			${LOCAL_PROJECT_NAME}_DLL		# name of the project
			ErrorDecoder					# name of the LIBRARY
			"${libs}"						# libs to link
			"${dep}"						# dependencies
			ErrorDecoder.cpp) # files to build

getPathToExternals()
include_directories(${ALL_EXTERNAL_INCS} ${CMAKE_SOURCE_DIR}/include)
# link directories - external
link_directories(${ALL_EXTERNAL_LIBS})
# build executable
add_executable(${LOCAL_PROJECT_NAME}_tests ErrorHandling_tests.cpp)
# important for gtest MSVC
target_compile_options(${LOCAL_PROJECT_NAME}_tests PUBLIC -D_VARIADIC_MAX=10)
# externals (BOOST links automatically)
target_link_libraries(	${LOCAL_PROJECT_NAME}_tests
						gtest${CMAKE_STATIC_LIBRARY_SUFFIX} 
						gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX})
# depends on:
add_dependencies(${LOCAL_PROJECT_NAME}_tests googletest)
# add TEST
add_test(${LOCAL_PROJECT_NAME}_tests ${LOCAL_PROJECT_NAME}_tests)