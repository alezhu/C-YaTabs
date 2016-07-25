// dllmain.cpp : Implementation of DllMain.

#include "stdafx.h"
#include "resource.h"
#include "YaTabs_i.h"
#include "dllmain.h"

CYaTabsModule _AtlModule;

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	hInstance;
    if (dwReason == DLL_PROCESS_ATTACH)
    {
		TCHAR pszLoader[MAX_PATH];
		GetModuleFileName(NULL, pszLoader, MAX_PATH);
		_tcslwr(pszLoader);
		if (_tcsstr(pszLoader, _T("explorer.exe"))) 
		   return FALSE;

        DisableThreadLibraryCalls(hInstance);
    }
	return _AtlModule.DllMain(dwReason, lpReserved); 
}
