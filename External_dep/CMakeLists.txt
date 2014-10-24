project("External_dep")

# Google test jest projektem wspólnym więc SOURCE i BINARY dir musza być takie same. Do projektu PBToolset są te katalogi przekazywane
# pod nazwami ROOT_PROJECT_SOURCE_DIR i COMMON_EXT_LIB_OUTPUT  itam są używane w testach ora przy budowmie gtestu. Ustawienia wspólnych
# projektów powinny byc takie same
# jesli oba google testy sa do tego samego katalogu to jeden daje locka drugiemu przy rebuild - trzeba usunąć
set(SYSTEM_UPDATE_COMMAND svn cleanup ${CMAKE_SOURCE_DIR}/External_dep/gtest)
ExternalProject_Add(	googletest
						# wszystko ląduje w Third_party/gtest
						SOURCE_DIR ${CMAKE_SOURCE_DIR}/External_dep/gtest
						BINARY_DIR ${CMAKE_SOURCE_DIR}/bin/External_dep/gtest
						STAMP_DIR ${ROOT_PROJECT_SOURCE_DIR}/bin/External_dep/gtest/stamp
						SVN_REPOSITORY ${GTest_SVN_REPOSITORY}
						# Force separate output paths for debug and release builds to allow easy
						# identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
						CMAKE_ARGS -DCMAKE_CXX_FLAGS='-D_VARIADIC_MAX=10'
							-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=${CMAKE_SOURCE_DIR}/lib
							-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=${CMAKE_SOURCE_DIR}/lib
							-Dgtest_force_shared_crt=ON
							-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
						# Disable install step
						INSTALL_COMMAND ""
						UPDATE_COMMAND ${SYSTEM_UPDATE_COMMAND}
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
						# set all libs in main dir lib
						CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
							-DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
							-DCOMMON_EXT_LIB_OUTPUT=${CMAKE_SOURCE_DIR}/lib 	# zmienna definiująca cel dla bin lib zewnętrznych
							-DROOT_PROJECT_SOURCE_DIR=${CMAKE_SOURCE_DIR}	# root dla projektu 9zakłada że wszystkie projekty mają taka sama strukturę)
							-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=${CMAKE_SOURCE_DIR}/lib # biblioteki wewnętrzne tego projektu, w tym przypadku wyrzucane tez do lib (ale niekoniecznie musi tak byc, tka jest łatwiej bo nie ma problemu ze sciezkami)
							-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=${CMAKE_SOURCE_DIR}/lib
						# Disable install step
						TEST_BEFORE_INSTALL 1
						INSTALL_COMMAND ""
						# Wrap download, configure and build steps in a script to log output
						# LOG_DOWNLOAD ON
					)		

ExternalProject_Add(	clapack
						# wszystko ląduje w Third_party/clapack
						SOURCE_DIR ${CMAKE_SOURCE_DIR}/External_dep/clapack-3.2.1-CMAKE
						# GIT_REPOSITORY ${PBToolset_GIT_REPOSITORY}
						# GIT_TAG ${PBToolset_GIT_TAG}
						# Force separate output paths for debug and release builds to allow easy
						# identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
						# set all libs in main dir lib
						CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
							-DCMAKE_CXX_FLAGS="/w" # jest duzo ostrzezen - blokada
							-DCMAKE_C_FLAGS="/w"
							-DCOMMON_EXT_LIB_OUTPUT=${CMAKE_SOURCE_DIR}/lib 	# zmienna definiująca cel dla bin lib zewnętrznych
							-DROOT_PROJECT_SOURCE_DIR=${CMAKE_SOURCE_DIR}	# root dla projektu 9zakłada że wszystkie projekty mają taka sama strukturę)
							-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=${CMAKE_SOURCE_DIR}/lib # biblioteki wewnętrzne tego projektu, w tym przypadku wyrzucane tez do lib (ale niekoniecznie musi tak byc, tka jest łatwiej bo nie ma problemu ze sciezkami)
							-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=${CMAKE_SOURCE_DIR}/lib
							-Wno-dev
						# Disable install step
						TEST_BEFORE_INSTALL 0
						INSTALL_COMMAND  copy /y /b ..\\..\\..\\..\\..\\lib\\libf2c.lib ..\\..\\..\\..\\..\\lib\\f2c.lib # nazwa sie nie zgadza i levmar nie linkuje
						# Wrap download, configure and build steps in a script to log output
						# LOG_DOWNLOAD ON
					)		

ExternalProject_Add(	levmar
						# wszystko ląduje w Third_party/levmar
						SOURCE_DIR ${CMAKE_SOURCE_DIR}/External_dep/levmar-2.6
						# GIT_REPOSITORY ${PBToolset_GIT_REPOSITORY}
						# GIT_TAG ${PBToolset_GIT_TAG}
						# Force separate output paths for debug and release builds to allow easy
						# identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
						# set all libs in main dir lib
						CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
							-DLAPACKBLAS_DIR=${CMAKE_SOURCE_DIR}/lib
							-DCOMMON_EXT_LIB_OUTPUT=${CMAKE_SOURCE_DIR}/lib 	# zmienna definiująca cel dla bin lib zewnętrznych
							-DROOT_PROJECT_SOURCE_DIR=${CMAKE_SOURCE_DIR}	# root dla projektu 9zakłada że wszystkie projekty mają taka sama strukturę)
							-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=${CMAKE_SOURCE_DIR}/lib # biblioteki wewnętrzne tego projektu, w tym przypadku wyrzucane tez do lib (ale niekoniecznie musi tak byc, tka jest łatwiej bo nie ma problemu ze sciezkami)
							-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=${CMAKE_SOURCE_DIR}/lib
							-Wno-dev
						# Disable install step
						TEST_BEFORE_INSTALL 0
						INSTALL_COMMAND ""
						# Wrap download, configure and build steps in a script to log output
						# LOG_DOWNLOAD ON
					)												
