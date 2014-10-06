project("External_dep")
ExternalProject_Add(	googletest
						# wszystko ląduje w Third_party/gtest
						SOURCE_DIR ${CMAKE_SOURCE_DIR}/External_dep/gtest
						SVN_REPOSITORY http://googletest.googlecode.com/svn/trunk/
						# Force separate output paths for debug and release builds to allow easy
						# identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
						CMAKE_ARGS -DCMAKE_CXX_FLAGS='-D_VARIADIC_MAX=10'
							-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
							-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
							-Dgtest_force_shared_crt=ON
							-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
						# Disable install step
						INSTALL_COMMAND ""
						# Wrap download, configure and build steps in a script to log output
						# LOG_DOWNLOAD ON
					)

ExternalProject_Add(	PBToolset
						# wszystko ląduje w Third_party/PBToolset
						SOURCE_DIR ${CMAKE_SOURCE_DIR}/External_dep/PBToolset
						GIT_REPOSITORY https://github.com/baniuk/PBToolset.git
						# Force separate output paths for debug and release builds to allow easy
						# identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
						CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
									-DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
						# Disable install step
						TEST_BEFORE_INSTALL 1
						INSTALL_COMMAND ""
						# Wrap download, configure and build steps in a script to log output
						# LOG_DOWNLOAD ON
					)					