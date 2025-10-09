#ifndef _WINDOWS_
#include <windows.h>
#endif
/*
inline static const Elysium::Core::Reflection::Assembly ReflectedAssembly =
Elysium::Core::Reflection::Assembly(Elysium::Core::Reflection::AssemblyName(u8"Elysium.Core.CommandLine, Elysium::Core::Version(0, 1)));

inline static const Elysium::Core::Reflection::Module ModuleCoreData =
Elysium::Core::Reflection::Module(ReflectedAssembly, u8"Elysium.Core.CommandLine");
*/
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
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

