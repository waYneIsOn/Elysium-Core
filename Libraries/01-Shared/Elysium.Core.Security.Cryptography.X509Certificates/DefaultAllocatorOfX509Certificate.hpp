/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_MEMORY_DEFAULTALLOCATOROFX509CERTIFICATE
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_MEMORY_DEFAULTALLOCATOROFX509CERTIFICATE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATE
#include "X509Certificate.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTALLOCATOR
#include "../Elysium.Core.Template/DefaultAllocator.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::X509Certificates::Memory
{
	template class ELYSIUM_CORE_SECURITY_API Elysium::Core::Template::Memory::DefaultAllocator<Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate>;
}
#endif
