# rzeczy do zmiany
set(LOCAL_PROJECT_NAME LV_FastMedian)
set(VERSION_MAJOR 1) # wersje powinny być skorelowane z /version w pliku
set(VERSION_MINOR 2)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/resources.rc.in
  ${CMAKE_CURRENT_BINARY_DIR}/resources.rc
  @ONLY)

project(${LOCAL_PROJECT_NAME})


addLibrary (STATIC
			${LOCAL_PROJECT_NAME}			# name of the project
			${LOCAL_PROJECT_NAME}_static    # name of the LIBRARY
			""
			""
			LV_FastMedian.cpp LV_fastMedian.h
			)

set(libs setError ${LOCAL_PROJECT_NAME}_static)
set(dep setError)
addLibrary(	SHARED 							# type
			${LOCAL_PROJECT_NAME}			# name of the project
			${LOCAL_PROJECT_NAME}		    # name of the LIBRARY
			"${libs}"						# libs to link
			"${dep}"
			dllmain.cpp LV_FastMedian_DLL_Wrapper.cpp LV_FastMedian_DLL_Wrapper.h
			${CMAKE_CURRENT_BINARY_DIR}/resources.rc
			errordef.rc) # files to build

# instalacja - kopiowanie wyników do katalogu po nmake install (nie potrzebne do testów)
install (TARGETS ${LOCAL_PROJECT_NAME} RUNTIME DESTINATION ${${ROOT_PROJECT_NAME}_SOURCE_DIR}/bin)
