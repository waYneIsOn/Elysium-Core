/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CHAIN
#define ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CHAIN

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_SECURITY_CRYPTOGRAPHY_CRYPTOGRAPHICEXCEPTION
#include "../../../Exceptions/Security/Cryptography/CryptographicException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATE
#include "X509Certificate.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CHAINPOLICY
#include "X509ChainPolicy.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_COMPILATIONSETTINGS
#include "../../../System/CompilationSettings.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../../System/OperatingSystem.hpp"
#endif

namespace Elysium::Core::Template::Security::Cryptography::X509Certificates
{
#if defined ELYSIUM_CORE_USE_CUSTOM_IMPLEMENTATION_X509CERTIFICATE
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
#elif defined ELYSIUM_CORE_OS_WINDOWS
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
			if (nullptr == Certificate._CertificateContext)
			{
				throw Elysium::Core::Template::Exceptions::Security::Cryptography::CryptographicException(u8"The certificate is unreadable.");
			}

			CERT_CHAIN_ENGINE_CONFIG CertificateChainEngineConfig{};
			CertificateChainEngineConfig.cbSize = sizeof(CERT_CHAIN_ENGINE_CONFIG);
			CertificateChainEngineConfig.hRestrictedRoot = nullptr;
			CertificateChainEngineConfig.hRestrictedTrust = nullptr;
			CertificateChainEngineConfig.hRestrictedOther = nullptr;
			CertificateChainEngineConfig.cAdditionalStore = 0;
			CertificateChainEngineConfig.rghAdditionalStore = nullptr;
			CertificateChainEngineConfig.dwFlags = CERT_CHAIN_CACHE_END_CERT;
			CertificateChainEngineConfig.dwUrlRetrievalTimeout = _ChainPolicy.GetUrlRetrievalTimeout().GetTotalMilliseconds();
			CertificateChainEngineConfig.MaximumCachedCertificates = 0;
			CertificateChainEngineConfig.CycleDetectionModulus = 0;

			HCERTCHAINENGINE CertificateChainEngine;
			if (FALSE == CertCreateCertificateChainEngine(&CertificateChainEngineConfig, &CertificateChainEngine))
			{
				throw Elysium::Core::Template::Exceptions::Security::Cryptography::CryptographicException(u8"Certificate chain engine creation failed.");
			}

			CERT_ENHKEY_USAGE CertificateEnhandedKeyUsage;
			CertificateEnhandedKeyUsage.cUsageIdentifier = 0;
			CertificateEnhandedKeyUsage.rgpszUsageIdentifier = nullptr;

			CERT_USAGE_MATCH CertificateUsage;
			CertificateUsage.dwType = USAGE_MATCH_TYPE_AND;
			CertificateUsage.Usage = CertificateEnhandedKeyUsage;

			CERT_CHAIN_PARA ChainParameter;
			ChainParameter.cbSize = sizeof(CERT_CHAIN_PARA);
			ChainParameter.RequestedUsage = CertificateUsage;

			DWORD Flags = 0;
			PCCERT_CHAIN_CONTEXT ChainContext;
			if (FALSE == CertGetCertificateChain(nullptr, Certificate._CertificateContext, nullptr, nullptr, &ChainParameter, Flags, nullptr, &ChainContext))
			{
				throw Elysium::Core::Template::Exceptions::Security::Cryptography::CryptographicException(u8"Certificate chain creation failed.");
			}

			//CertVerifyCertificateChainPolicy(CERT_CHAIN_POLICY_SSL, &ChainContext, 

			switch (ChainContext->TrustStatus.dwErrorStatus)
			{
			case CERT_TRUST_NO_ERROR:
				break;
			case CERT_TRUST_IS_NOT_TIME_VALID:
				break;
			case CERT_TRUST_IS_REVOKED:
				break;
			case CERT_TRUST_IS_NOT_SIGNATURE_VALID:
				break;
			case CERT_TRUST_IS_NOT_VALID_FOR_USAGE:
				break;
			case CERT_TRUST_IS_UNTRUSTED_ROOT:
				break;
			case CERT_TRUST_REVOCATION_STATUS_UNKNOWN:
				break;
			case CERT_TRUST_IS_CYCLIC:
				break;
			case CERT_TRUST_INVALID_EXTENSION:
				break;
			case CERT_TRUST_IS_PARTIAL_CHAIN:
				break;
			case CERT_TRUST_CTL_IS_NOT_TIME_VALID:
				break;
			case CERT_TRUST_CTL_IS_NOT_SIGNATURE_VALID:
				break;
			case CERT_TRUST_CTL_IS_NOT_VALID_FOR_USAGE:
				break;
			default:
				break;
			}

			switch (ChainContext->TrustStatus.dwInfoStatus)
			{
			case 0:
				break;
			case CERT_TRUST_HAS_EXACT_MATCH_ISSUER:
				break;
			case CERT_TRUST_HAS_KEY_MATCH_ISSUER:
				break;
			case CERT_TRUST_HAS_NAME_MATCH_ISSUER:
				break;
			case CERT_TRUST_IS_SELF_SIGNED:
				break;
			case CERT_TRUST_IS_COMPLEX_CHAIN:
				break;
			default:
				break;
			}

			CertFreeCertificateChain(ChainContext);
			CertFreeCertificateChainEngine(CertificateChainEngine);

			return true;
		}

		inline void Reset()
		{
			_ChainPolicy.Reset();
		}
	private:
		Elysium::Core::Template::Security::Cryptography::X509Certificates::X509ChainPolicy _ChainPolicy;
	};
#endif
}
#endif
