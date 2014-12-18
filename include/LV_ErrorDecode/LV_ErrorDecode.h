/**
 * \file LV_ErrorDecode.h
 * \brief Header for ErrorDecode LV library
 * \details Ranges of error codes assigned for DLLs:
 *	\li 0 - no error (defined in definitions.h)
 *	\li  9000 - 9999	- general errors for ErrorDecode lib
 *	\li 10000 - 19999 - LV_FastMedian
 *	\li 20000 - 29999 - LV_Threshold
 *	\li 30000 - 39999 - LV_WeldDetectApprox
 * \author PB
 * \date 2014/12/18
 */

#ifndef LV_ErrorDecode_h__
#define LV_ErrorDecode_h__

#include <stdint.h>
#include <string>
#include "setError/setError.h"
#include "definitions.h"

/**
 * \brief Converts error code to description
 * \details This method looks for error codes ranges and obtains name of the 
 * library which error code belongs to. Next loads selected library and read 
 * ints resources to obtain \a STRINGTABLE entry of given code. This string
 * is limited to certain length and returned. Absolute length of string is
 * defined by \a MAX_ERROR_STRING in definitions.h
 * \param[in] errCode code of the error to read
 * \param[out] errorDescription description of the error for \a errCode read 
 * from library
 * \return Description of the error if found
 * \retval \c void
 * \author PB
 * \date 2014/12/18
 * \note This method is for testing only. It returns raw c-string pointer
*/
extern "C" __declspec(dllexport) void getErrorDesc(uint32_t errCode,
	char* errorDescription);

/**
 * \brief Decodes name of the library
 * \details Basing on error code it returns name of the library
 * \param[in] errCode code of the error within specified range
 * \return Name of the library or empty string on error
 * \retval \c std::string
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