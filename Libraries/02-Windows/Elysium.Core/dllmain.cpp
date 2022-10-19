#ifndef _WINDOWS_
#include <windows.h>
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "../Elysium.Core/Byte.hpp"
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

#ifndef _TYPEINFO_
#include <typeinfo>
#endif

inline static const Elysium::Core::Reflection::Assembly ReflectedAssembly =
Elysium::Core::Reflection::Assembly(Elysium::Core::Reflection::AssemblyName(u8"Elysium.Core", Elysium::Core::Version(0, 1)));

inline static const Elysium::Core::Reflection::Module ModuleCore =
Elysium::Core::Reflection::Module(ReflectedAssembly, u8"Elysium::Core");

inline static const Elysium::Core::Reflection::Type TypevoidPointer =
Elysium::Core::Reflection::Type(ModuleCore, typeid(void*).hash_code(), u8"void*");

inline static const Elysium::Core::Reflection::Type Typebool =
Elysium::Core::Reflection::Type(ModuleCore, typeid(bool).hash_code(), u8"bool");

inline static const Elysium::Core::Reflection::Type Typefloat =
Elysium::Core::Reflection::Type(ModuleCore, typeid(float).hash_code(), u8"float");

inline static const Elysium::Core::Reflection::Type Typedouble =
Elysium::Core::Reflection::Type(ModuleCore, typeid(double).hash_code(), u8"double");

inline static const Elysium::Core::Reflection::Type Typechar =
Elysium::Core::Reflection::Type(ModuleCore, typeid(char).hash_code(), u8"char");

inline static const Elysium::Core::Reflection::Type Typewchar_t =
Elysium::Core::Reflection::Type(ModuleCore, typeid(wchar_t).hash_code(), u8"wchar_t");

inline static const Elysium::Core::Reflection::Type Typechar8_t =
Elysium::Core::Reflection::Type(ModuleCore, typeid(char8_t).hash_code(), u8"char8_t");

inline static const Elysium::Core::Reflection::Type Typechar16_t =
Elysium::Core::Reflection::Type(ModuleCore, typeid(char16_t).hash_code(), u8"char16_t");

inline static const Elysium::Core::Reflection::Type Typechar32_t =
Elysium::Core::Reflection::Type(ModuleCore, typeid(char32_t).hash_code(), u8"char32_t");

inline static const Elysium::Core::Reflection::Type Typebyte =
Elysium::Core::Reflection::Type(ModuleCore, typeid(Elysium::Core::byte).hash_code(), u8"byte");

inline static const Elysium::Core::Reflection::Type Typesbyte =
Elysium::Core::Reflection::Type(ModuleCore, typeid(Elysium::Core::sbyte).hash_code(), u8"sbyte");

inline static const Elysium::Core::Reflection::Type Typeuint8_t =
Elysium::Core::Reflection::Type(ModuleCore, typeid(Elysium::Core::uint8_t).hash_code(), u8"uint8_t");

inline static const Elysium::Core::Reflection::Type Typeuint16_t =
Elysium::Core::Reflection::Type(ModuleCore, typeid(Elysium::Core::uint16_t).hash_code(), u8"uint16_t");

inline static const Elysium::Core::Reflection::Type Typeuint32_t =
Elysium::Core::Reflection::Type(ModuleCore, typeid(Elysium::Core::uint32_t).hash_code(), u8"uint32_t");

inline static const Elysium::Core::Reflection::Type Typeuint64_t =
Elysium::Core::Reflection::Type(ModuleCore, typeid(Elysium::Core::uint64_t).hash_code(), u8"uint64_t");

inline static const Elysium::Core::Reflection::Type Typeint8_t =
Elysium::Core::Reflection::Type(ModuleCore, typeid(Elysium::Core::int8_t).hash_code(), u8"int8_t");

inline static const Elysium::Core::Reflection::Type Typeint16_t =
Elysium::Core::Reflection::Type(ModuleCore, typeid(Elysium::Core::int16_t).hash_code(), u8"int16_t");

inline static const Elysium::Core::Reflection::Type Typeint32_t =
Elysium::Core::Reflection::Type(ModuleCore, typeid(Elysium::Core::int32_t).hash_code(), u8"int32_t");

inline static const Elysium::Core::Reflection::Type Typeint64_t =
Elysium::Core::Reflection::Type(ModuleCore, typeid(Elysium::Core::int64_t).hash_code(), u8"int64_t");

inline static const Elysium::Core::Reflection::Type TypeString =
Elysium::Core::Reflection::Type(ModuleCore, typeid(Elysium::Core::String).hash_code(), u8"String");

inline static const Elysium::Core::Reflection::Type TypeWideString =
Elysium::Core::Reflection::Type(ModuleCore, typeid(Elysium::Core::WideString).hash_code(), u8"WideString");

inline static const Elysium::Core::Reflection::Type TypeUtf8String =
Elysium::Core::Reflection::Type(ModuleCore, typeid(Elysium::Core::Utf8String).hash_code(), u8"Utf8String");

inline static const Elysium::Core::Reflection::Type TypeUtf16String =
Elysium::Core::Reflection::Type(ModuleCore, typeid(Elysium::Core::Utf16String).hash_code(), u8"Utf16String");

inline static const Elysium::Core::Reflection::Type TypeUtf32String =
Elysium::Core::Reflection::Type(ModuleCore, typeid(Elysium::Core::Utf32String).hash_code(), u8"Utf32String");

inline static const Elysium::Core::Reflection::Module ModuleCoreCollections =
Elysium::Core::Reflection::Module(ReflectedAssembly, u8"Elysium::Core::Collections");

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
