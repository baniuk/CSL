# rzeczy do zmiany
set(LOCAL_PROJECT_NAME LV_Features)
set(VERSION_MAJOR 1) # wersje powinny być skorelowane z /version w pliku
set(VERSION_MINOR 0)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/resources.rc.in
  ${CMAKE_CURRENT_BINARY_DIR}/resources.rc
  @ONLY)

project(${LOCAL_PROJECT_NAME})

set(lib f2c blas tmglib lapack libf2c)
set(dep clapack)
addLibrary (STATIC
			${LOCAL_PROJECT_NAME}			# name of the project
			PCA_static    # name of the LIBRARY
			"${lib}"
			"${dep}"
			PCA.cpp PCA.h
			)

set(lib PCA_static)
set(dep PCA_static)
addLibrary (STATIC
			${LOCAL_PROJECT_NAME}			# name of the project
			${LOCAL_PROJECT_NAME}_static    # name of the LIBRARY
			"${lib}"
			"${dep}"
			LV_Features.cpp LV_Features.h
			C_Image_Container.cpp C_Image_Container.h
			C_Matrix_Container.cpp C_Matrix_Container.h
			C_Error.cpp C_Error.h
			)

set(libs setError ${LOCAL_PROJECT_NAME}_static)
set(dep setError)
addLibrary(	SHARED 							# type
			${LOCAL_PROJECT_NAME}			# name of the project
			${LOCAL_PROJECT_NAME}		    # name of the LIBRARY
			"${libs}"						# libs to link
			"${dep}"
			dllmain.cpp LV_Features_DLL_Wrapper.cpp LV_Features_DLL_Wrapper.h
			${CMAKE_CURRENT_BINARY_DIR}/resources.rc
			errordef.rc) # files to build

# instalacja - kopiowanie wyników do katalogu po nmake install (nie potrzebne do testów)
install (TARGETS ${LOCAL_PROJECT_NAME} RUNTIME DESTINATION ${${ROOT_PROJECT_NAME}_SOURCE_DIR}/bin)
