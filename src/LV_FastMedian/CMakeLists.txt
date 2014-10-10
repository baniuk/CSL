# rzeczy do zmiany
set(LOCAL_PROJECT_NAME LV_FastMedian)
set(VERSION_MAJOR 1) # wersje powinny być skorelowane z /version w pliku
set(VERSION_MINOR 0)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/resources.rc.in
  ${CMAKE_CURRENT_BINARY_DIR}/resources.rc
  @ONLY)

# set include directory - patch to have include files in VC project  (in add_library)
set(INC_DIR ${${ROOT_PROJECT_NAME}_SOURCE_DIR}/include/${LOCAL_PROJECT_NAME})

project(${LOCAL_PROJECT_NAME})
# includes in source files must be relative to ./include dir. Includes specific to 
# given project are in separate subdirectories
include_directories(${${ROOT_PROJECT_NAME}_SOURCE_DIR}/include)
# budowanie DLL
add_library(${LOCAL_PROJECT_NAME} SHARED
 			dllmain.cpp LV_FastMedian.cpp 
 			${LV_FastMedian_BINARY_DIR}/resources.rc 
 			${INC_DIR}/LV_fastMedian.h)

# Linkowanie z innymi bibliotekami
target_link_libraries(${LOCAL_PROJECT_NAME} setError)
add_dependencies(${LOCAL_PROJECT_NAME} setError)

# instalacja - kopiowanie wyników do katalogu po nmake install (nie potrzebne do testów)
install (TARGETS ${LOCAL_PROJECT_NAME} RUNTIME DESTINATION ${${ROOT_PROJECT_NAME}_SOURCE_DIR}/lib)

# dodatkowe ustawienia projektu
#set_target_properties(${LOCAL_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${${ROOT_PROJECT_NAME}_SOURCE_DIR}/lib)
# 
# target_compile_options(setError PUBLIC "/D_CRT_SECURE_NO_WARNINGS")