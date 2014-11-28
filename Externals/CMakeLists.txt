project("Externals")
# By default all external projects should ends with bins in External_dep_BINARY_DIR

set(PROGRAM_UPDATE_COMMAND "") # found http://www.cmake.org/pipermail/cmake/2014-February/056988.html

ExternalProject_Add(	googletest
						SVN_REPOSITORY ${GTest_SVN_REPOSITORY}
						# Force separate output paths for debug and release builds to allow easy
						# identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
						CMAKE_ARGS -DCMAKE_CXX_FLAGS='-D_VARIADIC_MAX=10'
							-Dgtest_force_shared_crt=ON
							-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
							-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=${CMAKE_SOURCE_DIR}/Externals/googletest/lib
							-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=${CMAKE_SOURCE_DIR}/Externals/googletest/lib
						# Disable install step
						INSTALL_COMMAND ""
						UPDATE_COMMAND ${PROGRAM_UPDATE_COMMAND}
						INSTALL_DIR ${CMAKE_SOURCE_DIR}/Externals/googletest 
						# Wrap download, configure and build steps in a script to log output
						# LOG_DOWNLOAD ON
					)


# get path to gtest to pass them to subproject
ExternalProject_Get_Property(googletest install_dir)
ExternalProject_Get_Property(googletest source_dir) 
ExternalProject_Add(	PBToolset
						DEPENDS googletest
						GIT_REPOSITORY ${PBToolset_GIT_REPOSITORY}
						GIT_TAG master
						# Force separate output paths for debug and release builds to allow easy
						# identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
						# set all libs in main dir lib
						CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
							-DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
							-DGTest_LIB=${install_dir}/lib
							-DGTest_SRC=${source_dir}
							-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=${CMAKE_SOURCE_DIR}/Externals/PBToolset/lib
							-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=${CMAKE_SOURCE_DIR}/Externals/PBToolset/lib
						# Disable install step
						TEST_BEFORE_INSTALL 1
						INSTALL_COMMAND ""
						UPDATE_COMMAND ${PROGRAM_UPDATE_COMMAND}
						INSTALL_DIR ${CMAKE_SOURCE_DIR}/Externals/PBToolset
						# Wrap download, configure and build steps in a script to log output
						# LOG_DOWNLOAD ON
					)		

# rename wrong named lib
# output dir set because all libs are spreaded out over bin dir
ExternalProject_Add(	clapack
						# wszystko ląduje w Third_party/clapack
						URL ${CMAKE_SOURCE_DIR}/static_resources/clapack-3.2.1-CMAKE.tgz
						# SOURCE_DIR ${CMAKE_SOURCE_DIR}/Externals
						CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
							-DCMAKE_C_FLAGS="/w" # jest duzo ostrzezen - blokada
							-Wno-dev
							-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=${CMAKE_SOURCE_DIR}/Externals/clapack/lib
							-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=${CMAKE_SOURCE_DIR}/Externals/clapack/lib
						# Disable install step
						TEST_BEFORE_INSTALL 0
						UPDATE_COMMAND ${PROGRAM_UPDATE_COMMAND}
						# copy scattered libs to ona directory - binary_build
						INSTALL_COMMAND ${CP_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Externals/clapack/lib/libf2c.lib ${CMAKE_SOURCE_DIR}/Externals/clapack/lib/f2c.lib
						INSTALL_DIR ${CMAKE_SOURCE_DIR}/Externals/clapack
						# Wrap download, configure and build steps in a script to log output
						# LOG_DOWNLOAD ON
					)		

# need lib directory for clapack
ExternalProject_Add(	levmar
						DEPENDS clapack
						URL ${CMAKE_SOURCE_DIR}/static_resources/levmar-2.6.tgz
						# wszystko ląduje w Third_party/levmar
						# SOURCE_DIR ${CMAKE_SOURCE_DIR}/Externals
						CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
							-DLAPACKBLAS_DIR=${CMAKE_SOURCE_DIR}/Externals/clapack/lib
							-Wno-dev
							-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=${CMAKE_SOURCE_DIR}/Externals/levmar/lib
							-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=${CMAKE_SOURCE_DIR}/Externals/levmar/lib
						# Disable install step
						TEST_BEFORE_INSTALL 0
						UPDATE_COMMAND ${PROGRAM_UPDATE_COMMAND}
						INSTALL_COMMAND ""
						INSTALL_DIR ${CMAKE_SOURCE_DIR}/Externals/levmar
						# Wrap download, configure and build steps in a script to log output
						# LOG_DOWNLOAD ON
					)												
