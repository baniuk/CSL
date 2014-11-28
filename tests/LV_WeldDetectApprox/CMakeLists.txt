# rzeczy do zmiany
set(LOCAL_PROJECT_NAME LV_WeldDetectApprox_tests)
# test case kopiowne z source do binary
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

project(${LOCAL_PROJECT_NAME})

getPathToExternals()

include_directories(${ALL_EXTERNAL_INCS} ${${ROOT_PROJECT_NAME}_SOURCE_DIR}/include)
# link directories - external
link_directories(${ALL_EXTERNAL_LIBS})

add_executable(${LOCAL_PROJECT_NAME} GTest_starter.cpp
				LV_WeldDetectApprox_DLL_tests.cpp
				LV_WeldDetectApprox_tests.cpp
				LV_WeldDetectApprox_WeldPostProcess_tests.cpp
				C_Matrix_Container.cpp  C_Matrix_Container.h)
# gtest specific
target_compile_options(${LOCAL_PROJECT_NAME} PUBLIC -D_VARIADIC_MAX=10)
target_link_libraries(	${LOCAL_PROJECT_NAME} 
						gtest${CMAKE_FIND_LIBRARY_SUFFIXES} 
						gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
						MatlabExchange${CMAKE_FIND_LIBRARY_SUFFIXES}
						LV_WeldDetectApprox_static
						LV_WeldDetectApprox_WeldPostProcess_static)

# linking with tested lib
add_dependencies(${LOCAL_PROJECT_NAME} googletest PBToolset LV_WeldDetectApprox LV_WeldDetectApprox_WeldPostProcess_static)
add_test(${LOCAL_PROJECT_NAME} ${LOCAL_PROJECT_NAME})