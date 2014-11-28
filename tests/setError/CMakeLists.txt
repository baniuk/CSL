# rzeczy do zmiany
set(LOCAL_PROJECT_NAME setError_Tests)

project(${LOCAL_PROJECT_NAME})

getPathToExternals()

include_directories(${ALL_EXTERNAL_INCS} ${${ROOT_PROJECT_NAME}_SOURCE_DIR}/include)
# link directories - external
link_directories(${ALL_EXTERNAL_LIBS})

add_executable(${LOCAL_PROJECT_NAME} setError_Tests.cpp)
# gtest specific
target_compile_options(${LOCAL_PROJECT_NAME} PUBLIC -D_VARIADIC_MAX=10)
target_link_libraries(${LOCAL_PROJECT_NAME} gtest${CMAKE_FIND_LIBRARY_SUFFIXES} gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES})

# linking with tested lib
target_link_libraries(${LOCAL_PROJECT_NAME} setError)
add_dependencies(${LOCAL_PROJECT_NAME} googletest setError)
add_test(${LOCAL_PROJECT_NAME} ${LOCAL_PROJECT_NAME})