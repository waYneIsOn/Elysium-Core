/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CHAINPOLICY
#define ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CHAINPOLICY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../../Container/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CHRONO_DATETIME
#include "../../../Chrono/DateTime.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CHRONO_TIMESPAN
#include "../../../Chrono/TimeSpan.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_OIDCOLLECTION
#include "../Encoding/OidCollection.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509REVOCATIONFLAG
#include "X509RevocationFlag.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509REVOCATIONMODE
#include "X509RevocationMode.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509VERIFICATIONFLAGS
#include "X509VerificationFlags.hpp"
#endif

namespace Elysium::Core::Template::Security::Cryptography::X509Certificates
{
	class X509ChainPolicy
	{
	public:
		constexpr X509ChainPolicy() = default;

		constexpr X509ChainPolicy(const X509ChainPolicy& Source) = delete;

		constexpr X509ChainPolicy(X509ChainPolicy&& Right) noexcept = delete;

		constexpr ~X509ChainPolicy() = default;
	public:
		constexpr X509ChainPolicy& operator=(const X509ChainPolicy& Source) = delete;

		constexpr X509ChainPolicy& operator=(X509ChainPolicy&& Right) noexcept = delete;
	public:
		inline constexpr const Elysium::Core::Template::Security::Cryptography::Encoding::OidCollection& GetApplicationPolicy() const
		{
			return _ApplicationPolicy;
		}

		inline constexpr const Elysium::Core::Template::Security::Cryptography::Encoding::OidCollection& GetCertificatePolicy() const
		{
			return _CertificatePolicy;
		}

		inline constexpr const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate>& GetExtraStore() const
		{
			return _ExtraStore;
		}

		inline constexpr const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509RevocationFlag GetRevocationFlag() const
		{
			return _RevocationFlag;
		}

		inline constexpr const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509RevocationMode GetRevocationMode() const
		{
			return _RevocationMode;
		}

		inline constexpr const Elysium::Core::Template::Chrono::TimeSpan GetUrlRetrievalTimeout() const
		{
			return _UrlRetrievalTimeout;
		}

		inline constexpr const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509VerificationFlags GetVerificationFlags() const
		{
			return _VerificationFlags;
		}

		inline constexpr const Elysium::Core::Template::Chrono::DateTime GetVerificationTime() const
		{
			return _VerificationTime;
		}
	public:
		inline void SetRevocationFlag(const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509RevocationFlag Value)
		{
			_RevocationFlag = Value;
		}

		inline void SetRevocationMode(const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509RevocationMode Value)
		{
			_RevocationMode = Value;
		}
	public:
		inline void Reset()
		{	// @ToDo
			throw;
		}
	private:
		Elysium::Core::Template::Security::Cryptography::Encoding::OidCollection _ApplicationPolicy;
		Elysium::Core::Template::Security::Cryptography::Encoding::OidCollection _CertificatePolicy;
		Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate> _ExtraStore;
		Elysium::Core::Template::Security::Cryptography::X509Certificates::X509RevocationFlag _RevocationFlag = 
			Elysium::Core::Template::Security::Cryptography::X509Certificates::X509RevocationFlag::EntireChain;
		Elysium::Core::Template::Security::Cryptography::X509Certificates::X509RevocationMode _RevocationMode = 
			Elysium::Core::Template::Security::Cryptography::X509Certificates::X509RevocationMode::Offline;
		Elysium::Core::Template::Chrono::TimeSpan _UrlRetrievalTimeout;
		Elysium::Core::Template::Security::Cryptography::X509Certificates::X509VerificationFlags _VerificationFlags = 
			Elysium::Core::Template::Security::Cryptography::X509Certificates::X509VerificationFlags::AllFlags;
		Elysium::Core::Template::Chrono::DateTime _VerificationTime;
	};
}
#endif
