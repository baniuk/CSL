# rzeczy do zmiany
set(LOCAL_PROJECT_NAME LV_ErrorDecode)
set(VERSION_MAJOR 1) # wersje powinny być skorelowane z /version w pliku
set(VERSION_MINOR 1)

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

# not using function because of extra settings passed here
getPathToExternals()
set(INC_DIR ${${ROOT_PROJECT_NAME}_SOURCE_DIR}/include/${LOCAL_PROJECT_NAME})
include_directories(${ALL_EXTERNAL_INCS}
					${CMAKE_SOURCE_DIR}/include)
link_directories(${ALL_EXTERNAL_LIBS})
add_library( ${LOCAL_PROJECT_NAME} SHARED
			 dllmain.cpp
			 ${INC_DIR}/LV_ErrorDecode.h
			 ${CMAKE_CURRENT_BINARY_DIR}/resources.rc)
target_link_libraries(  ${LOCAL_PROJECT_NAME}
						setError
						${LOCAL_PROJECT_NAME}_static
						labview.lib
						labviewv.lib)
add_dependencies(${LOCAL_PROJECT_NAME} setError)
# must be because of LV libraries
set_target_properties(  ${LOCAL_PROJECT_NAME}
						PROPERTIES
						LINK_FLAGS "/SAFESEH:NO")

set(libs "")
set(dep "")
addLibrary(	SHARED 							# type
			${LOCAL_PROJECT_NAME}			# name of the project
			${LOCAL_PROJECT_NAME}_dummyDLL	# name of the LIBRARY
			"${libs}"						# libs to link
			"${dep}"						# dependencies
			DUMMYdllmain.cpp
			${CMAKE_CURRENT_BINARY_DIR}/resources.rc
			errordef.rc) # files to build

# Test DLL (dummyDLL) must be copied to the same dir where tests are
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/copyDLL.bat "@echo off\n")
file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/copyDLL.bat "set CYGWIN=nodosfilewarning \n")
file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/copyDLL.bat "${CP_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Debug/${LOCAL_PROJECT_NAME}_dummyDLL.dll ${CMAKE_BINARY_DIR}/tests/LV_ErrorDecode/Debug/ \n")
add_custom_command(	TARGET ${LOCAL_PROJECT_NAME}_dummyDLL
					POST_BUILD
					COMMAND ${CMAKE_CURRENT_BINARY_DIR}/copyDLL.bat
	)
# instalacja - kopiowanie wyników do katalogu po nmake install (nie potrzebne do testów)
install (TARGETS ${LOCAL_PROJECT_NAME} RUNTIME DESTINATION ${${ROOT_PROJECT_NAME}_SOURCE_DIR}/bin)
install (TARGETS ${LOCAL_PROJECT_NAME}_dummyDLL RUNTIME DESTINATION ${${ROOT_PROJECT_NAME}_SOURCE_DIR}/bin)