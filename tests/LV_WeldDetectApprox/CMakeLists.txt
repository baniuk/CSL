# rzeczy do zmiany
set(LOCAL_PROJECT_NAME LV_WeldDetectApprox_tests)
# test case kopiowne z source do binary
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/testimag1.dat 
				${CMAKE_CURRENT_BINARY_DIR}/testimag1.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/testimag2.dat 
				${CMAKE_CURRENT_BINARY_DIR}/testimag2.dat
				COPYONLY)

project(${LOCAL_PROJECT_NAME})

# Biblioteki zewnętrzne - targety trafiają do lib więc nie ma potrzeby pobierania scierzki do bin
ExternalProject_Get_Property(googletest source_dir)
set(GTest_SRC ${source_dir}) 	
ExternalProject_Get_Property(PBToolset source_dir)
set(PBToolset_SRC ${source_dir}) 	
ExternalProject_Get_Property(levmar source_dir)
set(levmar_SRC ${source_dir}) 

include_directories(${GTest_SRC}/include ${${ROOT_PROJECT_NAME}_SOURCE_DIR}/include ${PBToolset_SRC}/include ${levmar_SRC})

add_executable(${LOCAL_PROJECT_NAME} LV_WeldDetectApprox_tests.cpp)
# gtest specific
target_compile_options(${LOCAL_PROJECT_NAME} PUBLIC -D_VARIADIC_MAX=10)
target_link_libraries(	${LOCAL_PROJECT_NAME} 
						${CMAKE_SOURCE_DIR}/lib/gtest${CMAKE_FIND_LIBRARY_SUFFIXES} 
						${CMAKE_SOURCE_DIR}/lib/gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
						${CMAKE_SOURCE_DIR}/lib/MatlabExchange${CMAKE_FIND_LIBRARY_SUFFIXES}
						LV_WeldDetectApprox_static)

# linking with tested lib
add_dependencies(${LOCAL_PROJECT_NAME} googletest PBToolset LV_WeldDetectApprox)
add_test(${LOCAL_PROJECT_NAME} ${LOCAL_PROJECT_NAME})