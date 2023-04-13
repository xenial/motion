// dllmain.cpp : Defines the entry point for the DLL application.
#include "interfaces.h"
#include "hooks.h"

int hackThread() {
    Interfaces::init();
    Hooks::init();

    return 1;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)hackThread, NULL, NULL, NULL);
        break;
    case DLL_THREAD_ATTACH: 
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

