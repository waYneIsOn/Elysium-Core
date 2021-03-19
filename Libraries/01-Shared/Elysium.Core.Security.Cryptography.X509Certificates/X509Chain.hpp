/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CHAIN
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CHAIN

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATE
#include "X509Certificate.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CHAINPOLICY
#include "X509ChainPolicy.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::X509Certificates
{
	class ELYSIUM_CORE_SECURITY_API X509Chain final
	{
	public:
		X509Chain();
		X509Chain(const X509Chain& Source) = delete;
		X509Chain(X509Chain&& Right) noexcept = delete;
		~X509Chain();

		X509Chain& operator=(const X509Chain& Source) = delete;
		X509Chain& operator=(X509Chain&& Right) noexcept = delete;

		const X509ChainPolicy& GetChainPolicy() const;

		const bool Build(const X509Certificate& Certificate);
		void Reset();
	private:
		X509ChainPolicy _ChainPolicy;
	};
}
#endif
