#ifndef ELYSIUM_CORE_NET_SOCKETS_INTERNAL_WINSOCKET
#include "../../01-Shared/Elysium.Core.Net/WinSocket.hpp"
#endif

#ifndef _WINDOWS_
#include <windows.h>    // make sure to include windows.h AFTER including any winsocket-header (WinSocket.hpp)
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
        Elysium::Core::Net::Sockets::Internal::WinSocket::Initialize();
        return TRUE;
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        Elysium::Core::Net::Sockets::Internal::WinSocket::Shutdown();
        return TRUE;
    }
}

