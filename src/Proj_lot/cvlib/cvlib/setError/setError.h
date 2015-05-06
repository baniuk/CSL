#ifndef setError_h__
#define setError_h__

#include <string>
#include <cstring>
#include "definitions.h"


class setError
{
public:

	static retCode throwError(const char* _errorDesc, char** _formattedErrorDesc);
private:
	setError(void) {};
	~setError(void) {};
};
#endif // setError_h__