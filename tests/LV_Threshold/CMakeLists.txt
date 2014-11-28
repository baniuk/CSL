# rzeczy do zmiany
set(LOCAL_PROJECT_NAME LV_Threshold_tests)
# test case kopiowne z source do binary
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/imag2.dat 
				${CMAKE_CURRENT_BINARY_DIR}/imag2.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/im8bit.dat 
				${CMAKE_CURRENT_BINARY_DIR}/im8bit.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/100_01_91_005.dat 
				${CMAKE_CURRENT_BINARY_DIR}/100_01_91_005.dat
				COPYONLY)

project(${LOCAL_PROJECT_NAME})

getPathToExternals()	

include_directories(${ALL_EXTERNAL_INCS} ${${ROOT_PROJECT_NAME}_SOURCE_DIR}/include)
# link directories - external
link_directories(${ALL_EXTERNAL_LIBS})

add_executable(${LOCAL_PROJECT_NAME} LV_Threshold_tests.cpp)
# gtest specific
target_compile_options(${LOCAL_PROJECT_NAME} PUBLIC -D_VARIADIC_MAX=10)
target_link_libraries(	${LOCAL_PROJECT_NAME} 
						gtest${CMAKE_FIND_LIBRARY_SUFFIXES} 
						gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
						MatlabExchange${CMAKE_FIND_LIBRARY_SUFFIXES}
						LV_Threshold_static)

# linking with tested lib
add_dependencies(${LOCAL_PROJECT_NAME} googletest PBToolset LV_Threshold)
add_test(${LOCAL_PROJECT_NAME} ${LOCAL_PROJECT_NAME})