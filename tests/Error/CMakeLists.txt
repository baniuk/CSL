project("DumpAll_Test")
# get directory prefixes for libs and includes of external tools
ExternalProject_Get_Property(googletest binary_dir)
set(GTest_LIB ${binary_dir})
ExternalProject_Get_Property(googletest source_dir)
set(GTest_SRC ${source_dir}) 		

include_directories(${GTest_SRC}/include ${PBToolset_SOURCE_DIR}/include)
add_executable(C_DumpAll_Tests C_DumpAll_Tests.cpp)
# gtest specific
set_target_properties(C_DumpAll_Tests PROPERTIES COMPILE_FLAGS "${cxx_flags} -D_VARIADIC_MAX=10")
target_link_libraries(C_DumpAll_Tests ${GTest_LIB}/DebugLibs/gtest${CMAKE_FIND_LIBRARY_SUFFIXES} ${GTest_LIB}/DebugLibs/gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES})

# linking with tested lib
target_link_libraries(C_DumpAll_Tests DumpAll)
add_dependencies(C_DumpAll_Tests googletest DumpAll)
add_test(C_DumpAll_Tests C_DumpAll_Tests)