#ifndef _WINDOWS_
#include <windows.h>
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "../Elysium.Core/Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_DIAGNOSTICS_INTERNAL_WINSYMBOLS
#include "../Elysium.Core.Diagnostics/WinSymbols.hpp"
#endif

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

#ifndef ELYSIUM_CORE_CONTAINER_RINGBUFFEROFINTEGER
#include "../Elysium.Core/RingBufferOfInteger.hpp"
#endif

#ifndef ELYSIUM_CORE_CONTAINER_VECTOROFBYTE
#include "../Elysium.Core/VectorOfByte.hpp"
#endif

#ifndef ELYSIUM_CORE_CONTAINER_VECTOROFINTEGER
#include "../Elysium.Core/VectorOfInteger.hpp"
#endif

#ifndef ELYSIUM_CORE_CONTAINER_VECTOROFSTRING
#include "../Elysium.Core/VectorOfString.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_ATOMIC
#include "../Elysium.Core.Threading/Atomic.hpp"
#endif

inline static const Elysium::Core::Reflection::Assembly ReflectedAssembly =
Elysium::Core::Reflection::Assembly(Elysium::Core::Reflection::AssemblyName(u8"Elysium.Core", Elysium::Core::Version(0, 1)));

inline static const Elysium::Core::Reflection::Module ModuleCore =
Elysium::Core::Reflection::Module(ReflectedAssembly, u8"Elysium::Core");

inline static const Elysium::Core::Reflection::Type TypevoidPointer =
Elysium::Core::Reflection::Type(ModuleCore, u8"void*");

inline static const Elysium::Core::Reflection::Type Typebool =
Elysium::Core::Reflection::Type(ModuleCore, u8"bool");

inline static const Elysium::Core::Reflection::Type Typefloat =
Elysium::Core::Reflection::Type(ModuleCore, u8"float");

inline static const Elysium::Core::Reflection::Type Typedouble =
Elysium::Core::Reflection::Type(ModuleCore, u8"double");

inline static const Elysium::Core::Reflection::Type Typechar =
Elysium::Core::Reflection::Type(ModuleCore, u8"char");

inline static const Elysium::Core::Reflection::Type Typewchar_t =
Elysium::Core::Reflection::Type(ModuleCore, u8"wchar_t");

inline static const Elysium::Core::Reflection::Type Typechar8_t =
Elysium::Core::Reflection::Type(ModuleCore, u8"char8_t");

inline static const Elysium::Core::Reflection::Type Typechar16_t =
Elysium::Core::Reflection::Type(ModuleCore, u8"char16_t");

inline static const Elysium::Core::Reflection::Type Typechar32_t =
Elysium::Core::Reflection::Type(ModuleCore, u8"char32_t");

inline static const Elysium::Core::Reflection::Type Typebyte =
Elysium::Core::Reflection::Type(ModuleCore, u8"byte");

inline static const Elysium::Core::Reflection::Type Typesbyte =
Elysium::Core::Reflection::Type(ModuleCore, u8"sbyte");

inline static const Elysium::Core::Reflection::Type Typeuint8_t =
Elysium::Core::Reflection::Type(ModuleCore, u8"uint8_t");

inline static const Elysium::Core::Reflection::Type Typeuint16_t =
Elysium::Core::Reflection::Type(ModuleCore, u8"uint16_t");

inline static const Elysium::Core::Reflection::Type Typeuint32_t =
Elysium::Core::Reflection::Type(ModuleCore, u8"uint32_t");

inline static const Elysium::Core::Reflection::Type Typeuint64_t =
Elysium::Core::Reflection::Type(ModuleCore, u8"uint64_t");

inline static const Elysium::Core::Reflection::Type Typeint8_t =
Elysium::Core::Reflection::Type(ModuleCore, u8"int8_t");

inline static const Elysium::Core::Reflection::Type Typeint16_t =
Elysium::Core::Reflection::Type(ModuleCore, u8"int16_t");

inline static const Elysium::Core::Reflection::Type Typeint32_t =
Elysium::Core::Reflection::Type(ModuleCore, u8"int32_t");

inline static const Elysium::Core::Reflection::Type Typeint64_t =
Elysium::Core::Reflection::Type(ModuleCore, u8"int64_t");

inline static const Elysium::Core::Reflection::Type TypeString =
Elysium::Core::Reflection::Type(ModuleCore, u8"String");

inline static const Elysium::Core::Reflection::Type TypeWideString =
Elysium::Core::Reflection::Type(ModuleCore, u8"WideString");

inline static const Elysium::Core::Reflection::Type TypeUtf8String =
Elysium::Core::Reflection::Type(ModuleCore, u8"Utf8String");

inline static const Elysium::Core::Reflection::Type TypeUtf16String =
Elysium::Core::Reflection::Type(ModuleCore, u8"Utf16String");

inline static const Elysium::Core::Reflection::Type TypeUtf32String =
Elysium::Core::Reflection::Type(ModuleCore, u8"Utf32String");

inline static const Elysium::Core::Reflection::Module ModuleCoreCollections =
Elysium::Core::Reflection::Module(ReflectedAssembly, u8"Elysium::Core::Collections");

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        Elysium::Core::Diagnostics::Internal::WinSymbols::Initialize(); // doesn't need to be called on every thread
        return TRUE;
    case DLL_THREAD_ATTACH:
        return TRUE;
    case DLL_THREAD_DETACH:
        return TRUE;
    case DLL_PROCESS_DETACH:
        Elysium::Core::Diagnostics::Internal::WinSymbols::Shutdown(); // doesn't need to be called on every thread
        return TRUE;
    }
}
