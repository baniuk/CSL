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

ExternalProject_Get_Property(PBToolset source_dir)
set(PBToolset_SRC ${source_dir}) 
ExternalProject_Get_Property(levmar source_dir)
set(levmar_SRC ${source_dir}) 

# set include directory - patch to have include files in VC project (in add_library)
set(INC_DIR ${${ROOT_PROJECT_NAME}_SOURCE_DIR}/include/${LOCAL_PROJECT_NAME})

project(${LOCAL_PROJECT_NAME})
# includes in source files must be relative to ./include dir. Includes specific to 
# given project are in separate subdirectories
include_directories(${${ROOT_PROJECT_NAME}_SOURCE_DIR}/include ${PBToolset_SRC}/include ${levmar_SRC})
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
			C_Matrix_Container.cpp ${INC_DIR}/C_Matrix_Container.h)
target_link_libraries(	${LOCAL_PROJECT_NAME}_static
						${CMAKE_SOURCE_DIR}/lib/Geom${CMAKE_FIND_LIBRARY_SUFFIXES}
						${CMAKE_SOURCE_DIR}/lib/levmar${CMAKE_FIND_LIBRARY_SUFFIXES}
						${CMAKE_SOURCE_DIR}/lib/f2c${CMAKE_FIND_LIBRARY_SUFFIXES}
						${CMAKE_SOURCE_DIR}/lib/blas${CMAKE_FIND_LIBRARY_SUFFIXES}
						${CMAKE_SOURCE_DIR}/lib/tmglib${CMAKE_FIND_LIBRARY_SUFFIXES}
						${CMAKE_SOURCE_DIR}/lib/lapack${CMAKE_FIND_LIBRARY_SUFFIXES})
# budowanie DLL (linkuje static)
add_library(${LOCAL_PROJECT_NAME} SHARED 
			dllmain.cpp LV_WeldDetectApprox_DLL_Wrapper.cpp
			${CMAKE_CURRENT_BINARY_DIR}/resources.rc
			${INC_DIR}/LV_WeldDetectApprox_DLL_Wrapper.h)
target_link_libraries(${LOCAL_PROJECT_NAME} setError ${LOCAL_PROJECT_NAME}_static)

add_dependencies(${LOCAL_PROJECT_NAME} setError PBToolset)

# instalacja - kopiowanie wyników do katalogu po nmake install (nie potrzebne do testów)
install (TARGETS ${LOCAL_PROJECT_NAME} RUNTIME DESTINATION ${${ROOT_PROJECT_NAME}_SOURCE_DIR}/lib)

# dodatkowe ustawienia projektu
#set_target_properties(${LOCAL_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${${ROOT_PROJECT_NAME}_SOURCE_DIR}/lib)
# 
# target_compile_options(setError PUBLIC "/D_CRT_SECURE_NO_WARNINGS")