#include <Windows.h>
// get it from https://github.com/martona/mhook
#include "mhook-lib/mhook.h"

// typedef it and load it
typedef HANDLE (WINAPI *CREATEFILEA)(
  _In_     LPCTSTR               lpFileName,
  _In_     DWORD                 dwDesiredAccess,
  _In_     DWORD                 dwShareMode,
  _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  _In_     DWORD                 dwCreationDisposition,
  _In_     DWORD                 dwFlagsAndAttributes,
  _In_opt_ HANDLE                hTemplateFile
);

//
CREATEFILEA TrueCF = (CREATEFILEA)GetProcAddress( GetModuleHandle( "kernel32" ), "CreateFileA" );

// overload to apply
HANDLE WINAPI MyCF(
  _In_     LPCTSTR               lpFileName,
  _In_     DWORD                 dwDesiredAccess,
  _In_     DWORD                 dwShareMode,
  _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  _In_     DWORD                 dwCreationDisposition,
  _In_     DWORD                 dwFlagsAndAttributes,
  _In_opt_ HANDLE                hTemplateFile
)
{
	// remove FILE_FLAG_NO_BUFFERING from everything containing "rogue" in path
	if( strstr( lpFileName, "rogue" ) )
		dwFlagsAndAttributes &= ~FILE_FLAG_NO_BUFFERING;

	return TrueCF( lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile );
}


//
INT APIENTRY DllMain( HMODULE hDLL, DWORD Reason, LPVOID Reserved )
{
    switch(Reason) {
    case DLL_PROCESS_ATTACH: Mhook_SetHook( (PVOID*)&TrueCF, MyCF );	break;
    case DLL_PROCESS_DETACH: Mhook_Unhook( (PVOID*)&TrueCF );			break;
    case DLL_THREAD_ATTACH:												break;
    case DLL_THREAD_DETACH:												break;
    }

    return TRUE;
}