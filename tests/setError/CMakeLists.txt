# rzeczy do zmiany
set(LOCAL_PROJECT_NAME setError_Tests)

project(${LOCAL_PROJECT_NAME})
ExternalProject_Get_Property(googletest binary_dir)
set(GTest_LIB ${binary_dir})
ExternalProject_Get_Property(googletest source_dir)
set(GTest_SRC ${source_dir}) 	

include_directories(${GTest_SRC}/include ${${ROOT_PROJECT_NAME}_SOURCE_DIR}/include)
add_executable(${LOCAL_PROJECT_NAME} setError_Tests.cpp)
# gtest specific
target_compile_options(${LOCAL_PROJECT_NAME} PUBLIC -D_VARIADIC_MAX=10)
target_link_libraries(${LOCAL_PROJECT_NAME} ${GTest_LIB}/gtest${CMAKE_FIND_LIBRARY_SUFFIXES} ${GTest_LIB}/gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES})

# linking with tested lib
target_link_libraries(${LOCAL_PROJECT_NAME} setError)
add_dependencies(${LOCAL_PROJECT_NAME} googletest setError)
add_test(${LOCAL_PROJECT_NAME} ${LOCAL_PROJECT_NAME})