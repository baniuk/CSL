project("Error")
# includes in source files must be relative to ./include dir. Includes specific to 
# given project are in separate subdirectories
include_directories(${PBToolset_SOURCE_DIR}/include)

add_library(DumpAll STATIC C_DumpAll.cpp)
set_target_properties(DumpAll
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "${${ROOT_PROJECT_NAME}_SOURCE_DIR}/lib")