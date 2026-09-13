/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CHAIN_CUSTOM
#define ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CHAIN_CUSTOM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_COMPILATIONSETTINGS
#include "../../../System/CompilationSettings.hpp"
#endif

#if defined ELYSIUM_CORE_USE_CUSTOM_IMPLEMENTATION_X509CERTIFICATE
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATE
#include "X509Certificate.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CHAINPOLICY
#include "X509ChainPolicy.hpp"
#endif

namespace Elysium::Core::Template::Security::Cryptography::X509Certificates
{
	class X509Chain
	{
	public:
		constexpr X509Chain() = default;

		constexpr X509Chain(const X509Chain& Source) = delete;

		constexpr X509Chain(X509Chain&& Right) noexcept = delete;

		constexpr ~X509Chain() = default;
	public:
		constexpr X509Chain& operator=(const X509Chain& Source) = delete;

		constexpr X509Chain& operator=(X509Chain&& Right) noexcept = delete;
	public:
		inline constexpr Elysium::Core::Template::Security::Cryptography::X509Certificates::X509ChainPolicy& GetChainPolicy()
		{
			return _ChainPolicy;
		}

		inline constexpr const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509ChainPolicy& GetChainPolicy() const
		{
			return _ChainPolicy;
		}
	public:
		inline constexpr const bool Build(const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate& Certificate)
		{
			throw 1;
		}
	private:
		Elysium::Core::Template::Security::Cryptography::X509Certificates::X509ChainPolicy _ChainPolicy;
	};
}
#endif
#endif
