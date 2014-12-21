# rzeczy do zmiany
set(LOCAL_PROJECT_NAME OpenCV_Tests)
# test case kopiowne z source do binary
if(${CMAKE_GENERATOR} MATCHES "^(Visual Studio)")
	set(CMAKE_CURRENT_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}")
endif()
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/lena.jpg 
				${CMAKE_CURRENT_BINARY_DIR}/lena.jpg
				COPYONLY)

project(${LOCAL_PROJECT_NAME})

getPathToExternals()	

include_directories(${ALL_EXTERNAL_INCS} ${OpenCV_INCLUDE_DIRS})
# link directories - external
link_directories(${ALL_EXTERNAL_LIBS})

add_executable(${LOCAL_PROJECT_NAME} DisplayImage.cpp)

target_link_libraries(${LOCAL_PROJECT_NAME} gtest${CMAKE_FIND_LIBRARY_SUFFIXES} gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES})

# linking with tested lib
target_link_libraries(${LOCAL_PROJECT_NAME} ${OpenCV_LIBS})
add_test(${LOCAL_PROJECT_NAME} ${LOCAL_PROJECT_NAME} "lena.jpg")