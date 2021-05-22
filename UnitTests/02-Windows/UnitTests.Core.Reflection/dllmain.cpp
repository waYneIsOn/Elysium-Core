#include <windows.h>

#ifndef ELYSIUM_CORE_REFLECTION_APPDOMAIN
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Reflection/AppDomain.hpp"
#endif

inline const static Elysium::Core::Reflection::Assembly ReflectedAssembly =
    Elysium::Core::Reflection::Assembly(Elysium::Core::Reflection::AssemblyName(u8"UnitTests::Core::Reflection", u8"Codebase", Elysium::Core::Version(0, 1)));

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        Elysium::Core::Reflection::AppDomain::Add(ReflectedAssembly);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
