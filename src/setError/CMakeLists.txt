project("setError")
# includes in source files must be relative to ./include dir. Includes specific to 
# given project are in separate subdirectories
include_directories(${${ROOT_PROJECT_NAME}_SOURCE_DIR}/include)


 
add_library(setError STATIC setError.cpp)
set_target_properties(setError
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "${${ROOT_PROJECT_NAME}_SOURCE_DIR}/lib"
	COMPILE_FLAGS "/D_CRT_SECURE_NO_WARNINGS")