# rzeczy do zmiany
set(LOCAL_PROJECT_NAME LV_Threshold_tests)
# test case kopiowne z source do binary
if(${CMAKE_GENERATOR} MATCHES "^(Visual Studio)")
	set(CMAKE_CURRENT_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}")
endif()
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
set(dependencies PBToolset)
set(libs LV_Threshold_static MatlabExchange)
addTest(${LOCAL_PROJECT_NAME} "${libs}" "${dependencies}")