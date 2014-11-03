# rzeczy do zmiany
set(LOCAL_PROJECT_NAME OpenCV_Tests)
# test case kopiowne z source do binary
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/lena.jpg 
				${CMAKE_CURRENT_BINARY_DIR}/lena.jpg
				COPYONLY)

project(${LOCAL_PROJECT_NAME})

include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(${LOCAL_PROJECT_NAME} DisplayImage.cpp)

target_link_libraries(${LOCAL_PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/gtest${CMAKE_FIND_LIBRARY_SUFFIXES} ${CMAKE_SOURCE_DIR}/lib/gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES})

# linking with tested lib
target_link_libraries(${LOCAL_PROJECT_NAME} ${OpenCV_LIBS})
add_test(${LOCAL_PROJECT_NAME} ${LOCAL_PROJECT_NAME} "lena.jpg")