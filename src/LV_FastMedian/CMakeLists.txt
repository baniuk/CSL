# rzeczy do zmiany
set(LOCAL_PROJECT_NAME LV_FastMedian)
set(GENERIC_LIB_VERSION 1)
set(GENERIC_LIB_SOVERSION 0)

project(${LOCAL_PROJECT_NAME})
# includes in source files must be relative to ./include dir. Includes specific to 
# given project are in separate subdirectories
include_directories(${${ROOT_PROJECT_NAME}_SOURCE_DIR}/include)
add_library(${LOCAL_PROJECT_NAME} SHARED dllmain.cpp LV_FastMedian.cpp)

# Linkowanie z innymi bibliotekami
target_link_libraries(${LOCAL_PROJECT_NAME} setError)
add_dependencies(${LOCAL_PROJECT_NAME} setError)

set_target_properties(${LOCAL_PROJECT_NAME}  PROPERTIES
 	  VERSION ${GENERIC_LIB_VERSION}
 	  SOVERSION ${GENERIC_LIB_SOVERSION}
)

# dodatkowe ustawienia projektu
install (TARGETS ${LOCAL_PROJECT_NAME}
         RUNTIME DESTINATION ${${ROOT_PROJECT_NAME}_SOURCE_DIR}/lib)
# target_compile_options(setError PUBLIC "/D_CRT_SECURE_NO_WARNINGS")