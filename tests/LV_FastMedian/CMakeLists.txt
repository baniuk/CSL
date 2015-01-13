# rzeczy do zmiany
set(LOCAL_PROJECT_NAME LV_FastMedian_tests)
# test case kopiowne z source do binary
# important if test is run with paameters or external files
if(${CMAKE_GENERATOR} MATCHES "^(Visual Studio)")
	set(CMAKE_CURRENT_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}")
endif()
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/imag2.dat 
				${CMAKE_CURRENT_BINARY_DIR}/imag2.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/testimag1.dat 
				${CMAKE_CURRENT_BINARY_DIR}/testimag1.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/testimag6.dat 
				${CMAKE_CURRENT_BINARY_DIR}/testimag6.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/testimag9.dat 
				${CMAKE_CURRENT_BINARY_DIR}/testimag9.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/testimag17.dat 
				${CMAKE_CURRENT_BINARY_DIR}/testimag17.dat
				COPYONLY)

project(${LOCAL_PROJECT_NAME})
set(dependencies PBToolset)
set(libs LV_FastMedian_static MatlabExchange)
addTest(${LOCAL_PROJECT_NAME} "${libs}" "${dependencies}")
