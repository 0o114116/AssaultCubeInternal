// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include "HackMainLoop.h"

BOOL APIENTRY DllMain( const HMODULE hModule,
                       const DWORD  ulReasonForCall,
                       LPVOID lpReserved )
{
    switch (ulReasonForCall)
    {
    case DLL_PROCESS_ATTACH:
    {
        CloseHandle(CreateThread(
            nullptr, 
            0, 
            reinterpret_cast<LPTHREAD_START_ROUTINE>(HackThread), 
            hModule, 
            0, 
            nullptr));
        break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
    default:
        break;
    }
    return TRUE;
}
