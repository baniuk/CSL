# rzeczy do zmiany
set(LOCAL_PROJECT_NAME LV_WeldDetectApprox_tests)
# test case kopiowne z source do binary
if(${CMAKE_GENERATOR} MATCHES "^(Visual Studio)")
	set(CMAKE_CURRENT_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}")
endif()
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/testimag1.dat 
				${CMAKE_CURRENT_BINARY_DIR}/testimag1.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/testimag2.dat 
				${CMAKE_CURRENT_BINARY_DIR}/testimag2.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/testimag3.dat 
				${CMAKE_CURRENT_BINARY_DIR}/testimag3.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/testimag4.dat 
				${CMAKE_CURRENT_BINARY_DIR}/testimag4.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/testimag5.dat 
				${CMAKE_CURRENT_BINARY_DIR}/testimag5.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/testimag6.dat 
				${CMAKE_CURRENT_BINARY_DIR}/testimag6.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/testimag7.dat 
				${CMAKE_CURRENT_BINARY_DIR}/testimag7.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/testimag8.dat 
				${CMAKE_CURRENT_BINARY_DIR}/testimag8.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/testimag9.dat 
				${CMAKE_CURRENT_BINARY_DIR}/testimag9.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/testimag10.dat 
				${CMAKE_CURRENT_BINARY_DIR}/testimag10.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/testimag11.dat 
				${CMAKE_CURRENT_BINARY_DIR}/testimag11.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/testimag12.dat 
				${CMAKE_CURRENT_BINARY_DIR}/testimag12.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/testimag13.dat 
				${CMAKE_CURRENT_BINARY_DIR}/testimag13.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/testimag14.dat 
				${CMAKE_CURRENT_BINARY_DIR}/testimag14.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/testimag15.dat 
				${CMAKE_CURRENT_BINARY_DIR}/testimag15.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/testimag16.dat 
				${CMAKE_CURRENT_BINARY_DIR}/testimag16.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/testimag17.dat 
				${CMAKE_CURRENT_BINARY_DIR}/testimag17.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/testimag18.dat 
				${CMAKE_CURRENT_BINARY_DIR}/testimag18.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/testimag19.dat 
				${CMAKE_CURRENT_BINARY_DIR}/testimag19.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/testimag20.dat 
				${CMAKE_CURRENT_BINARY_DIR}/testimag20.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/testimag21.dat 
				${CMAKE_CURRENT_BINARY_DIR}/testimag21.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/D_WeldDetexApprox_1.dat
				${CMAKE_CURRENT_BINARY_DIR}/D_WeldDetexApprox_1.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/G_WeldDetexApprox_1.dat
				${CMAKE_CURRENT_BINARY_DIR}/G_WeldDetexApprox_1.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/lineok_WeldDetexApprox_1.dat
				${CMAKE_CURRENT_BINARY_DIR}/lineok_WeldDetexApprox_1.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/Sample-20-60kV-12mA-8s-IQI.tif.dat
				${CMAKE_CURRENT_BINARY_DIR}/Sample-20-60kV-12mA-8s-IQI.tif.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/Sample-18-70kV-15mA-8s-IQI-B.tif.dat
				${CMAKE_CURRENT_BINARY_DIR}/Sample-18-70kV-15mA-8s-IQI-B.tif.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/Sample-18-70kV-15mA-8s-IQI-A.tif.dat
				${CMAKE_CURRENT_BINARY_DIR}/Sample-18-70kV-15mA-8s-IQI-A.tif.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/Sample-17-60kV-12mA-8s-IQI.tif.dat
				${CMAKE_CURRENT_BINARY_DIR}/Sample-17-60kV-12mA-8s-IQI.tif.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/Sample-15-70kV-15mA-8s-IQI.tif.dat
				${CMAKE_CURRENT_BINARY_DIR}/Sample-15-70kV-15mA-8s-IQI.tif.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/Sample-14-70kV-15mA-8s-IQI.tif.dat
				${CMAKE_CURRENT_BINARY_DIR}/Sample-14-70kV-15mA-8s-IQI.tif.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/Sample-13-65kV-12mA-8s-IQI.tif.dat
				${CMAKE_CURRENT_BINARY_DIR}/Sample-13-65kV-12mA-8s-IQI.tif.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/Sample-12-60kV-12mA-8s-IQI-B.tif.dat
				${CMAKE_CURRENT_BINARY_DIR}/Sample-12-60kV-12mA-8s-IQI-B.tif.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/Sample-12-60kV-12mA-8s-IQI-A.tif.dat
				${CMAKE_CURRENT_BINARY_DIR}/Sample-12-60kV-12mA-8s-IQI-A.tif.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/Sample-11-60kV-12mA-8s-IQI.tif.dat
				${CMAKE_CURRENT_BINARY_DIR}/Sample-11-60kV-12mA-8s-IQI.tif.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/Sample-10-60kV-12mA-8s-IQI.tif.dat
				${CMAKE_CURRENT_BINARY_DIR}/Sample-10-60kV-12mA-8s-IQI.tif.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/Sample-09-60kV-12mA-8s-IQI-B.tif.dat
				${CMAKE_CURRENT_BINARY_DIR}/Sample-09-60kV-12mA-8s-IQI-B.tif.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/Sample-09-60kV-12mA-8s-IQI-A.tif.dat
				${CMAKE_CURRENT_BINARY_DIR}/Sample-09-60kV-12mA-8s-IQI-A.tif.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/Sample-08-70kV-15mA-11s-IQI.tif.dat
				${CMAKE_CURRENT_BINARY_DIR}/Sample-08-70kV-15mA-11s-IQI.tif.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/Sample-07-60kV-15mA-8s-IQI.tif.dat
				${CMAKE_CURRENT_BINARY_DIR}/Sample-07-60kV-15mA-8s-IQI.tif.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/Sample-06-60kV-12mA-8s-IQI-B.tif.dat
				${CMAKE_CURRENT_BINARY_DIR}/Sample-06-60kV-12mA-8s-IQI-B.tif.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/Sample-06-60kV-12mA-8s-IQI-A.tif.dat
				${CMAKE_CURRENT_BINARY_DIR}/Sample-06-60kV-12mA-8s-IQI-A.tif.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/Sample-05-60kV-12mA-8s-IQI.tif.dat
				${CMAKE_CURRENT_BINARY_DIR}/Sample-05-60kV-12mA-8s-IQI.tif.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/Sample-04-60kV-12mA-8s-IQI.tif.dat
				${CMAKE_CURRENT_BINARY_DIR}/Sample-04-60kV-12mA-8s-IQI.tif.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/Sample-03-60kV-15mA-8s-IQI.tif.dat
				${CMAKE_CURRENT_BINARY_DIR}/Sample-03-60kV-15mA-8s-IQI.tif.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/Sample-02-60kV-12mA-8s-IQI.tif.dat
				${CMAKE_CURRENT_BINARY_DIR}/Sample-02-60kV-12mA-8s-IQI.tif.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/Sample-01-70kV-15mA-8s-IQI.tif.dat
				${CMAKE_CURRENT_BINARY_DIR}/Sample-01-70kV-15mA-8s-IQI.tif.dat
				COPYONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/Sample-01-60kV-12mA-8s-IQI.tif.dat
				${CMAKE_CURRENT_BINARY_DIR}/Sample-01-60kV-12mA-8s-IQI.tif.dat
				COPYONLY)

project(${LOCAL_PROJECT_NAME})
set(dependencies PBToolset LV_WeldDetectApprox LV_WeldDetectApprox_WeldPostProcess_static)
set(libs LV_WeldDetectApprox_static MatlabExchange LV_WeldDetectApprox_WeldPostProcess_static)
addTest(${LOCAL_PROJECT_NAME} "${libs}" "${dependencies}")
