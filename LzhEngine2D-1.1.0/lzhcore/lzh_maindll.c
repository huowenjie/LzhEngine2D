/*===========================================================================*/

#ifdef _WINDOWS
#include <windows.h>

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
        break;

    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}
#endif

/*===========================================================================*/
