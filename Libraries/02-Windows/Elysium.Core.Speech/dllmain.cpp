#ifndef ELYSIUM_CORE_SPEECH_INTERNAL_WINSAPI
#include "../../01-Shared/Elysium.Core.Speech/WinSAPI.hpp"
#endif

#ifndef _WINDOWS_
#include <windows.h>
#endif

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
        Elysium::Core::Speech::Internal::WinSAPI::Initialize();
        return TRUE;
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        Elysium::Core::Speech::Internal::WinSAPI::Shutdown();
        return TRUE;
    }
    return TRUE;
}

