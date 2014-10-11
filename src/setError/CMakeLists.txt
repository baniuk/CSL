# rzeczy do zmiany
set(LOCAL_PROJECT_NAME setError)

# set include directory - patch to have include files in VC project (in add_library)
set(INC_DIR ${${ROOT_PROJECT_NAME}_SOURCE_DIR}/include/${LOCAL_PROJECT_NAME})

project(${LOCAL_PROJECT_NAME})
# includes in source files must be relative to ./include dir. Includes specific to 
# given project are in separate subdirectories
include_directories(${${ROOT_PROJECT_NAME}_SOURCE_DIR}/include)
 
add_library(${LOCAL_PROJECT_NAME} STATIC
			setError.cpp
			${INC_DIR}/setError.h)
# dodatkowe ustawienia projektu
target_compile_options(${LOCAL_PROJECT_NAME} PUBLIC "/D_CRT_SECURE_NO_WARNINGS")

# nie trzeba na zewnatrz nagrywac bo to nie są biblioteki końcowe
#set_target_properties(${LOCAL_PROJECT_NAME} PROPERTIES	ARCHIVE_OUTPUT_DIRECTORY "${${ROOT_PROJECT_NAME}_SOURCE_DIR}/lib")