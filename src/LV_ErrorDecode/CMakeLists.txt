# rzeczy do zmiany
set(LOCAL_PROJECT_NAME LV_ErrorDecode)
set(VERSION_MAJOR 1) # wersje powinny być skorelowane z /version w pliku
set(VERSION_MINOR 0)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/resources.rc.in
  ${CMAKE_CURRENT_BINARY_DIR}/resources.rc
  @ONLY)

project(${LOCAL_PROJECT_NAME})

set(libs setError)
set(dep setError)

addLibrary( STATIC
			${LOCAL_PROJECT_NAME}			# name of the project
			${LOCAL_PROJECT_NAME}_static	# name of the LIBRARY
			"${libs}"						# libs to link
			"${dep}"						# dependencies
			LV_ErrorDecode.cpp LV_ErrorDecode.h
	)
set(libs setError ${LOCAL_PROJECT_NAME}_static)
addLibrary(	SHARED 							# type
			${LOCAL_PROJECT_NAME}			# name of the project
			${LOCAL_PROJECT_NAME}			# name of the LIBRARY
			"${libs}"						# libs to link
			"${dep}"						# dependencies
			dllmain.cpp 
			${CMAKE_CURRENT_BINARY_DIR}/resources.rc) # files to build

# instalacja - kopiowanie wyników do katalogu po nmake install (nie potrzebne do testów)
install (TARGETS ${LOCAL_PROJECT_NAME} RUNTIME DESTINATION ${${ROOT_PROJECT_NAME}_SOURCE_DIR}/bin)