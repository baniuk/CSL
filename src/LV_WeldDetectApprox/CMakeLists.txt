# rzeczy do zmiany
set(LOCAL_PROJECT_NAME LV_WeldDetectApprox)
set(VERSION_MAJOR 1) # wersje powinny być skorelowane z /version w pliku
set(VERSION_MINOR 1)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/resources.rc.in
  ${CMAKE_CURRENT_BINARY_DIR}/resources.rc
  @ONLY)

project(${LOCAL_PROJECT_NAME})

set(lib Geom levmar${CMAKE_FIND_LIBRARY_SUFFIXES} f2c blas tmglib lapack)
set(dep setError PBToolset levmar clapack)
addLibrary(	STATIC 							# type
			${LOCAL_PROJECT_NAME}			# name of the project
			${LOCAL_PROJECT_NAME}_static	# name of the LIBRARY
			"${lib}"						# libs to link (if any)
			"${dep}"						# dependencies (if any)
			C_LineInterp.cpp C_LineInterp.h
			C_LineWeldApprox.cpp C_LineWeldApprox.h
			C_Levmar_Warp.cpp C_Levmar_Warp.h
			interpol.cpp interpol.h
			coeff.cpp coeff.h
			C_LinearWeld.cpp C_LinearWeld.h
			C_WeldlineDetect.cpp C_WeldlineDetect.h
			C_WeldPos.cpp C_WeldPos.h
			C_CircBuff.h
			ParamEstimation.cpp ParamEstimation.h) # files to build

addLibrary(	STATIC 							# type
			${LOCAL_PROJECT_NAME}			# name of the project
			${LOCAL_PROJECT_NAME}_WeldPostProcess_static	# name of the LIBRARY
			"${OpenCV_LIBS}"				# libs to link (if any)
			"${dep}"								# dependencies (if any)
			CV_WeldPostProcess.cpp CV_WeldPostProcess.h) # files to build

set(libs setError ${LOCAL_PROJECT_NAME}_static ${LOCAL_PROJECT_NAME}_WeldPostProcess_static)
set(dep setError PBToolset)
addLibrary(	SHARED 							# type
			${LOCAL_PROJECT_NAME}			# name of the project
			${LOCAL_PROJECT_NAME}			# name of the LIBRARY
			"${libs}"						# libs to link
			"${dep}"						# dependencies
			dllmain.cpp LV_WeldDetectApprox_DLL_Wrapper.cpp LV_WeldDetectApprox_DLL_Wrapper.h
			${CMAKE_CURRENT_BINARY_DIR}/resources.rc
			errordef.rc) # files to build

# instalacja - kopiowanie wyników do katalogu po nmake install (nie potrzebne do testów)
install (TARGETS ${LOCAL_PROJECT_NAME} RUNTIME DESTINATION ${${ROOT_PROJECT_NAME}_SOURCE_DIR}/bin)
