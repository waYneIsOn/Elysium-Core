#ifndef _WINDOWS_
#include <windows.h>
#endif

#ifndef ELYSIUM_CORE_REFLECTION_APPDOMAIN
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Reflection/AppDomain.hpp"
#endif

#ifndef ELYSIUM_CORE_REFLECTION_ASSEMBLY
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Reflection/Assembly.hpp"
#endif

#ifndef ELYSIUM_CORE_REFLECTION_MODULE
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Reflection/Module.hpp"
#endif

#ifndef ELYSIUM_CORE_REFLECTION_TYPE
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Reflection/Type.hpp"
#endif

inline static const Elysium::Core::Reflection::Assembly ReflectedAssembly =
Elysium::Core::Reflection::Assembly(Elysium::Core::Reflection::AssemblyName(u8"Elysium.Core.Speech", Elysium::Core::Version(0, 1)));

inline static const Elysium::Core::Reflection::Module ModuleCoreData =
Elysium::Core::Reflection::Module(ReflectedAssembly, u8"Elysium::Core::Speech");

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

