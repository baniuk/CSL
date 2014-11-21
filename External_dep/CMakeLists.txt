project("External_dep")
# By default all external projects should ends with bins in External_dep_BINARY_DIR

ExternalProject_Add(	googletest
						SVN_REPOSITORY ${GTest_SVN_REPOSITORY}
						# Force separate output paths for debug and release builds to allow easy
						# identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
						CMAKE_ARGS -DCMAKE_CXX_FLAGS='-D_VARIADIC_MAX=10'
							-Dgtest_force_shared_crt=ON
							-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
						# Disable install step
						INSTALL_COMMAND ""
						UPDATE_COMMAND ""
						# Wrap download, configure and build steps in a script to log output
						# LOG_DOWNLOAD ON
					)


# get path to gtest to pass them to subproject
ExternalProject_Get_Property(googletest binary_dir)
set(GTest_LIB ${binary_dir})
ExternalProject_Get_Property(googletest source_dir)
set(GTest_SRC ${source_dir}) 
ExternalProject_Add(	PBToolset
						DEPENDS googletest
						GIT_REPOSITORY ${PBToolset_GIT_REPOSITORY}
						GIT_TAG master
						# Force separate output paths for debug and release builds to allow easy
						# identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
						# set all libs in main dir lib
						CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
							-DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
							-DGTest_LIB=${GTest_LIB}
							-DGTest_SRC=${GTest_SRC} 
							-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=${External_dep_BINARY_DIR}
							-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=${External_dep_BINARY_DIR}
						# Disable install step
						TEST_BEFORE_INSTALL 1
						INSTALL_COMMAND ""
						UPDATE_COMMAND git pull
						# Wrap download, configure and build steps in a script to log output
						# LOG_DOWNLOAD ON
					)		

# rename wrong named lib
# output dir set because all libs are spreaded out over bin dir
ExternalProject_Add(	clapack
						# wszystko ląduje w Third_party/clapack
						SOURCE_DIR ${CMAKE_SOURCE_DIR}/External_dep/clapack-3.2.1-CMAKE
						CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
							-DCMAKE_C_FLAGS="/w" # jest duzo ostrzezen - blokada
							-Wno-dev
							-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=${External_dep_BINARY_DIR}
							-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=${External_dep_BINARY_DIR}
						# Disable install step
						TEST_BEFORE_INSTALL 0
						# copy scattered libs to ona directory - binary_build
						INSTALL_COMMAND copy /y /b ..\\..\\..\\libf2c.lib ..\\..\\..\\f2c.lib
						# Wrap download, configure and build steps in a script to log output
						# LOG_DOWNLOAD ON
					)		

# need lib directory for clapack
ExternalProject_Add(	levmar
						DEPENDS clapack
						# wszystko ląduje w Third_party/levmar
						SOURCE_DIR ${CMAKE_SOURCE_DIR}/External_dep/levmar-2.6
						CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
							-DLAPACKBLAS_DIR=${External_dep_BINARY_DIR}
							-Wno-dev
							-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=${External_dep_BINARY_DIR}
							-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=${External_dep_BINARY_DIR}
						# Disable install step
						TEST_BEFORE_INSTALL 0
						INSTALL_COMMAND ""
						# Wrap download, configure and build steps in a script to log output
						# LOG_DOWNLOAD ON
					)												
