/**
 * \file ErrorDecoder.cpp
 * \brief Decodes error from its name
 * \details 
 * \pre 
 * \author PB
 * \date 2014/12/16
 * \warning
 */

#include <windows.h>
#include <string>
#include <ctime>
#include <crtdbg.h>
#include <definitions.h>

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	HANDLE hLogFile;
	time_t seconds;
	time(&seconds);

	hLogFile = CreateFile("errordecoder.log", FILE_APPEND_DATA,
		FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, hLogFile);
	_RPT1(_CRT_WARN, "The current local time is: %s\n", ctime(&seconds));

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		_RPT0(_CRT_WARN, "Free Library");
		break;
	}
	CloseHandle(hLogFile);
	return TRUE;
}

// http://msdn.microsoft.com/en-us/library/ms648008%28v=VS.85%29.aspx#_win32_Updating_Resources
extern "C" __declspec(dllexport) void decode(UINT32 err, std::string& out)
{
	std::string libName;
	if (err >= 100 && err <= 199)
		libName = "ErrorHandling_tests_DLL.dll";
	else
	{
		out = "Unknown DLL";
		return;
	}

	HMODULE hExe = LoadLibrary(libName.c_str());

}