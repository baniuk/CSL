# rzeczy do zmiany
set(LOCAL_PROJECT_NAME LV_Features_tests)
# test case kopiowne z source do binary
if(${CMAKE_GENERATOR} MATCHES "^(Visual Studio)")
	set(CMAKE_CURRENT_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}")
endif()

project(${LOCAL_PROJECT_NAME})
set(dependencies PCA_static LV_Features_static)
set(libs PCA_static)
addTest(${LOCAL_PROJECT_NAME} "${libs}" "${dependencies}")