/**
 * \file LV_ErrorDecode.h
 * \brief Header for ErrorDecode LV library
 * \details This library translates error codes returned from another libs to
 * description strings. These strings are appended to original DLLs as resurces
 * by means of \a STRINGTABLE fileds. The IDs assigned to strings are also
 * error codes. Every DLLs has assigned certain range of codes, which is
 * globally specified and maintained. All codes returned by such DLL must be in
 * this range. \n 
 * Ranges of error codes assigned for DLLs:
 * \li 0 - no error (defined in definitions.h)
 * \li 0xF0000000 - 0xF00000FF	- general errors for ErrorDecode lib
 * \li 0x01000000 - 0x010000FF - LV_FastMedian
 * \li 0x02000000 - 0x020000FF - LV_Threshold
 * \li 0x03000000 - 0x030000FF - LV_WeldDetectApprox
 * \li 0x04000000 - 0x040000FF - LV_Features
 * \li 0xFFFFFF00 - 0xFFFFFFFE - LV_ErrorDecode_dummyDLL.dll - only for tests
 * \n\n
 * \b Possible \b outputs \n
 * \li  code \c 0 returns "No error"
 * \li code of unsupported library - returns Unknown error code. Can not connect with any known library
 * \li code of supported library but library can not be loaded - returns library \c XX could not be found
 * \li code of supported library, library can be loaded but there is no that code in error list - returns Error of code: \c errCode could not be found in library \c libName
 * 
 * Sequence diagram. Red arrows mean error signals, blue correct signals.
 * \msc
 * LV [label="LabView"], ED [label="ErrorDecoder"];
 * LV=>ED [label="getErrorDesc"];
 * ED=>ED [label="getDllName"];
 * ED=>ED [label="getErrorDescription"];
 * ED>>LV [label="unknow error code", textcolour="red", linecolour="red"];
 * ED>>LV [label="lib could not be found", textcolour="red", linecolour="red"];
 * ED>>LV [label="error code not found in lib", textcolour="red", linecolour="red"];
 * ED>>LV [label="error desc", textcolour="blue", linecolour="blue"];
 * \endmsc
 * \warning All libraires must be accessible by system. they can be lacated in
 * any directory which is in system path.
 * \author PB
 * \date 2014/12/18
 */

#ifndef LV_ErrorDecode_h__
#define LV_ErrorDecode_h__

#include "extcode.h"
#include <stdint.h>
#include <string>
#include "setError/setError.h"
#include "definitions.h"

/**
 * \brief Converts error code to description
 * \details This method looks for error codes ranges and obtains name of the 
 * library which error code belongs to. Next loads selected library and read 
 * ints resources to obtain \c STRINGTABLE entry of given code. This string
 * is limited to certain length and returned. Absolute length of string is
 * defined by \c MAX_ERROR_STRING in definitions.h
 * \param[in] errCode code of the error to read
 * \param[out] errorDescription description of the error for \c errCode read 
 * from library
 * \return Description of the error if found
 * \retval void
 * \author PB
 * \date 2014/12/18
 * \note This method is for testing only. It returns raw c-string pointer
 * \remarks It is exportable method
*/
extern "C" __declspec(dllexport) void getErrorDesc(uint32_t errCode,
	char* errorDescription);

/**
* \brief Converts error code to description, uses LV memory handling
* \details This method looks for error codes ranges and obtains name of the
* library which error code belongs to. Next loads selected library and read
* ints resources to obtain \c STRINGTABLE entry of given code. This string
* is limited to certain length and returned. Absolute length of string is
* defined by \c MAX_ERROR_STRING in definitions.h. Uses memory handling from LV
* to resize input table
* \param[in] errCode code of the error to read
* \param[out] errorDescription description of the error for \c errCode read
* from library
* \return Description of the error if found
* \retval void
* \author PB
* \date 2014/12/18
* \remarks It is exportable method
* \see External code (DLL) Execution.vi
*/
extern "C" __declspec(dllexport) void LV_getErrorDesc(uint32_t errCode,
	LStrHandle errorDescription);

/**
 * \brief Decodes name of the library
 * \details Basing on error code it returns name of the library
 * \param[in] errCode code of the error within specified range
 * \return Name of the library or empty string on error
 * \retval std::string
 * \author PB
 * \date 2014/12/18
*/
std::string getDllName(uint32_t errCode);


/**
 * \brief Reads description of error from resources
 * \details Decodes error code and load relevan library and then reads
 * description of the error from its resurces
 * \param[in] errCode code of the error within specified range
 * \return Error description read from DLL or own internal error
 * \retval \c std::string
 * \author PB
 * \date 2014/12/18
 * \note Returned error string can be truncated here 
*/
std::string getErrorDescription(uint32_t errCode);
#endif // LV_ErrorDecode_h__