project("External_dep")

# Google test jest projektem wspólnym więc SOURCE i BINARY dir musza być takie same. Do projektu PBToolset są te katalogi przekazywane
# pod nazwami ROOT_PROJECT_SOURCE_DIR i COMMON_EXT_LIB_OUTPUT  itam są używane w testach ora przy budowmie gtestu. Ustawienia wspólnych
# projektów powinny byc takie same

ExternalProject_Add(	googletest
						# wszystko ląduje w Third_party/gtest
						SOURCE_DIR ${CMAKE_SOURCE_DIR}/External_dep/gtest
						BINARY_DIR ${CMAKE_SOURCE_DIR}/bin/External_dep
						STAMP_DIR ${ROOT_PROJECT_SOURCE_DIR}/bin/External_dep/googletest-stamp
						SVN_REPOSITORY http://googletest.googlecode.com/svn/trunk/
						# Force separate output paths for debug and release builds to allow easy
						# identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
						CMAKE_ARGS -DCMAKE_CXX_FLAGS='-D_VARIADIC_MAX=10'
							-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY:PATH=${CMAKE_SOURCE_DIR}/lib
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
						GIT_REPOSITORY ${PBToolset_GIT_REPOSITORY}
						GIT_TAG ${PBToolset_GIT_TAG}
						# Force separate output paths for debug and release builds to allow easy
						# identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
						CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
							-DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
							-DCOMMON_EXT_LIB_OUTPUT=${CMAKE_SOURCE_DIR}/lib 	# zmienna definiująca cel dla bin lib
							-DROOT_PROJECT_SOURCE_DIR=${CMAKE_SOURCE_DIR}	# root dla projektu 9zakłada że wszystkie projekty mają taka sama strukturę)
						# Disable install step
						TEST_BEFORE_INSTALL 1
						INSTALL_COMMAND ""
						# Wrap download, configure and build steps in a script to log output
						# LOG_DOWNLOAD ON
					)					