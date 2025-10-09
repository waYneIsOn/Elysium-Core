#ifndef ELYSIUM_CORE_NET_SOCKETS_INTERNAL_WINSOCKET
#include "../../01-Shared/Elysium.Core.Net/WinSocket.hpp"
#endif

#ifndef _WINDOWS_
#include <windows.h>    // make sure to include windows.h AFTER including any winsocket-header (WinSocket.hpp)
#endif
/*
#ifndef ELYSIUM_CORE_REFLECTION_APPDOMAIN
#include "../Elysium.Core.Reflection/AppDomain.hpp"
#endif

#ifndef ELYSIUM_CORE_REFLECTION_ASSEMBLY
#include "../Elysium.Core.Reflection/Assembly.hpp"
#endif

#ifndef ELYSIUM_CORE_REFLECTION_MODULE
#include "../Elysium.Core.Reflection/Module.hpp"
#endif

#ifndef ELYSIUM_CORE_REFLECTION_TYPE
#include "../Elysium.Core.Reflection/Type.hpp"
#endif

inline static const Elysium::Core::Reflection::Assembly ReflectedAssembly =
Elysium::Core::Reflection::Assembly(Elysium::Core::Reflection::AssemblyName(u8"Elysium.Core.Net", Elysium::Core::Version(0, 1)));

inline static const Elysium::Core::Reflection::Module ModuleCoreData =
Elysium::Core::Reflection::Module(ReflectedAssembly, u8"Elysium::Core::Net");
*/
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

