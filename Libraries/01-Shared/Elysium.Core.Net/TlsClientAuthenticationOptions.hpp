/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_SECURITY_TLSCLIENTAUTHENTICATIONOPTIONS
#define ELYSIUM_CORE_NET_SECURITY_TLSCLIENTAUTHENTICATIONOPTIONS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_NET_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRINGVIEW
#include "../Elysium.Core/StringView.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SECURITY_TLSAUTHENTICATIONOPTIONS
#include "../Elysium.Core.Template/Net/Security/TlsClientAuthenticationOptions.hpp"
#endif





#ifndef ELYSIUM_CORE_CONTAINER_VECTOROFSTRING
#include "../Elysium.Core/VectorOfString.hpp"
#endif



#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATE
#include "../Elysium.Core.Security.Cryptography.X509Certificates/X509Certificate.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CHAIN
#include "../Elysium.Core.Security.Cryptography.X509Certificates/X509Chain.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SECURITY_TLSPOLICYERRORS
#include "../Elysium.Core.Template/Net/Security/TlsPolicyErrors.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SECURITY_TLSCIPHERSUITE
#include "../Elysium.Core.Template/Net/Security/TlsCipherSuite.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DELEGATE
#include "../Elysium.Core.Template/Container/Delegate.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Elysium.Core.Template/Container/Vector.hpp"
#endif

namespace Elysium::Core::Net::Security
{
	class ELYSIUM_CORE_NET_API Elysium::Core::Template::Net::Security::TlsClientAuthenticationOptions;

	using TlsClientAuthenticationOptions = Elysium::Core::Template::Net::Security::TlsClientAuthenticationOptions;
}
#endif
