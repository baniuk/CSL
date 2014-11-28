# rzeczy do zmiany
set(LOCAL_PROJECT_NAME LV_WeldDetectApprox)
set(VERSION_MAJOR 1) # wersje powinny być skorelowane z /version w pliku
set(VERSION_MINOR 0)

IF(${CMAKE_GENERATOR} MATCHES "^(Visual Studio)")
	set(CMAKE_CURRENT_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}")
ENDIF()
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/resources.rc.in
  ${CMAKE_CURRENT_BINARY_DIR}/resources.rc
  @ONLY)

getPathToExternals()

# set include directory - patch to have include files in VC project (in add_library)
set(INC_DIR ${${ROOT_PROJECT_NAME}_SOURCE_DIR}/include/${LOCAL_PROJECT_NAME})

project(${LOCAL_PROJECT_NAME})
# includes in source files must be relative to ./include dir. Includes specific to 
# given project are in separate subdirectories
include_directories(${${ROOT_PROJECT_NAME}_SOURCE_DIR}/include ${ALL_EXTERNAL_INCS})
# link directories - external
link_directories(${ALL_EXTERNAL_LIBS})
# budowanie biblioteki statycznej
add_library(${LOCAL_PROJECT_NAME}_static STATIC 
			C_LineInterp.cpp ${INC_DIR}/C_LineInterp.h
			C_LineWeldApprox.cpp ${INC_DIR}/C_LineWeldApprox.h
			C_Levmar_Warp.cpp ${INC_DIR}/C_Levmar_Warp.h
			interpol.cpp ${INC_DIR}/interpol.h
			coeff.cpp ${INC_DIR}/coeff.h
			C_LinearWeld.cpp ${INC_DIR}/C_LinearWeld.h
			C_WeldlineDetect.cpp ${INC_DIR}/C_WeldlineDetect.h
			C_WeldPos.cpp ${INC_DIR}/C_WeldPos.h
			${INC_DIR}/C_CircBuff.h
			ParamEstimation.cpp ${INC_DIR}/ParamEstimation.h)
add_library(${LOCAL_PROJECT_NAME}_WeldPostProcess_static STATIC 
			CV_WeldPostProcess.cpp ${INC_DIR}/CV_WeldPostProcess.h)		
# external libs				
target_link_libraries(	${LOCAL_PROJECT_NAME}_static
						Geom${CMAKE_FIND_LIBRARY_SUFFIXES}
						levmar${CMAKE_FIND_LIBRARY_SUFFIXES}
						f2c${CMAKE_FIND_LIBRARY_SUFFIXES}
						blas${CMAKE_FIND_LIBRARY_SUFFIXES}
						tmglib${CMAKE_FIND_LIBRARY_SUFFIXES}
						lapack${CMAKE_FIND_LIBRARY_SUFFIXES})
# linkowanie OpenCV
target_link_libraries(${LOCAL_PROJECT_NAME}_WeldPostProcess_static ${OpenCV_LIBS})
# budowanie DLL (linkuje static)
add_library(${LOCAL_PROJECT_NAME} SHARED 
			dllmain.cpp LV_WeldDetectApprox_DLL_Wrapper.cpp
			${CMAKE_CURRENT_BINARY_DIR}/resources.rc
			${INC_DIR}/LV_WeldDetectApprox_DLL_Wrapper.h)
target_link_libraries(${LOCAL_PROJECT_NAME} setError ${LOCAL_PROJECT_NAME}_static ${LOCAL_PROJECT_NAME}_WeldPostProcess_static)

add_dependencies(${LOCAL_PROJECT_NAME} setError PBToolset)
add_dependencies(${LOCAL_PROJECT_NAME}_static setError PBToolset levmar clapack)

# instalacja - kopiowanie wyników do katalogu po nmake install (nie potrzebne do testów)
install (TARGETS ${LOCAL_PROJECT_NAME} RUNTIME DESTINATION ${${ROOT_PROJECT_NAME}_SOURCE_DIR}/lib)

# dodatkowe ustawienia projektu
#set_target_properties(${LOCAL_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${${ROOT_PROJECT_NAME}_SOURCE_DIR}/lib)
# 
# target_compile_options(setError PUBLIC "/D_CRT_SECURE_NO_WARNINGS")