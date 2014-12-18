# rzeczy do zmiany
set(LOCAL_PROJECT_NAME LV_ErrorDecode_tests)

project(${LOCAL_PROJECT_NAME})
set(dependencies LV_ErrorDecode_static)
set(libs LV_ErrorDecode_static)
addTest(${LOCAL_PROJECT_NAME} "${libs}" "${dependencies}")