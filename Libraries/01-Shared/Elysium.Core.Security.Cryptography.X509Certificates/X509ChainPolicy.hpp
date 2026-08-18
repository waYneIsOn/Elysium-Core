/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CHAINPOLICY
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CHAINPOLICY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_CONTAINER_VECTOROFX509CERTIFICATE
#include "VectorOfX509Certificate.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CHAINPOLICY
#include "../Elysium.Core.Template/Security/Cryptography/X509Certificates/X509ChainPolicy.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::X509Certificates
{
	class ELYSIUM_CORE_SECURITY_API Elysium::Core::Template::Security::Cryptography::X509Certificates::X509ChainPolicy;

	using X509ChainPolicy = Elysium::Core::Template::Security::Cryptography::X509Certificates::X509ChainPolicy;
}
#endif
