# rzeczy do zmiany
set(LOCAL_PROJECT_NAME LV_FastMedian_tests)
# test case kopiowne z source do binary
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/imag2.dat 
				${CMAKE_CURRENT_BINARY_DIR}/imag2.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/testimag1.dat 
				${CMAKE_CURRENT_BINARY_DIR}/testimag1.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/testimag6.dat 
				${CMAKE_CURRENT_BINARY_DIR}/testimag6.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/testimag9.dat 
				${CMAKE_CURRENT_BINARY_DIR}/testimag9.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/testimag17.dat 
				${CMAKE_CURRENT_BINARY_DIR}/testimag17.dat
				COPYONLY)

project(${LOCAL_PROJECT_NAME})
ExternalProject_Get_Property(googletest binary_dir)
set(GTest_LIB ${binary_dir})
ExternalProject_Get_Property(googletest source_dir)
set(GTest_SRC ${source_dir}) 	

ExternalProject_Get_Property(PBToolset binary_dir)
set(PBToolset_LIB ${binary_dir})
ExternalProject_Get_Property(PBToolset source_dir)
set(PBToolset_SRC ${source_dir}) 	

include_directories(${GTest_SRC}/include ${${ROOT_PROJECT_NAME}_SOURCE_DIR}/include ${PBToolset_SRC}/include)

add_executable(${LOCAL_PROJECT_NAME} LV_FastMedian_tests.cpp)
# gtest specific
target_compile_options(${LOCAL_PROJECT_NAME} PUBLIC -D_VARIADIC_MAX=10)
target_link_libraries(${LOCAL_PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/gtest${CMAKE_FIND_LIBRARY_SUFFIXES} 
${CMAKE_SOURCE_DIR}/lib/gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES} ${CMAKE_SOURCE_DIR}/lib/MatlabExchange${CMAKE_FIND_LIBRARY_SUFFIXES} )

# linking with tested lib
add_dependencies(${LOCAL_PROJECT_NAME} googletest PBToolset)
add_test(${LOCAL_PROJECT_NAME} ${LOCAL_PROJECT_NAME})