#ifndef _WINDOWS_
#include <Windows.h>
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_CONTAINER_VECTOROFX509CERTIFICATE
#include "../../01-Shared/Elysium.Core.Security.Cryptography.X509Certificates/VectorOfX509Certificate.hpp"
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
Elysium::Core::Reflection::Assembly(Elysium::Core::Reflection::AssemblyName(u8"Elysium.Core.Security", Elysium::Core::Version(0, 1)));

inline static const Elysium::Core::Reflection::Module ModuleCoreData =
Elysium::Core::Reflection::Module(ReflectedAssembly, u8"Elysium::Core::Security");
*/

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_BERDECODER
#include "../../01-Shared/Elysium.Core.Security.Cryptography.Encoding/Asn1/BERDecoder.hpp"
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
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

