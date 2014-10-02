project("setError_Test")
# get directory prefixes for libs and includes of external tools
ExternalProject_Get_Property(googletest binary_dir)
set(GTest_LIB ${binary_dir})
ExternalProject_Get_Property(googletest source_dir)
set(GTest_SRC ${source_dir}) 		

include_directories(${GTest_SRC}/include ${${ROOT_PROJECT_NAME}_SOURCE_DIR}/include)
add_executable(setError_Tests setError_Tests.cpp)
# gtest specific
set_target_properties(setError_Tests PROPERTIES COMPILE_FLAGS "${cxx_flags} -D_VARIADIC_MAX=10")
target_link_libraries(setError_Tests ${GTest_LIB}/DebugLibs/gtest${CMAKE_FIND_LIBRARY_SUFFIXES} ${GTest_LIB}/DebugLibs/gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES})

# linking with tested lib
target_link_libraries(setError_Tests setError)
add_dependencies(setError_Tests googletest setError)
add_test(setError_Tests setError_Tests)