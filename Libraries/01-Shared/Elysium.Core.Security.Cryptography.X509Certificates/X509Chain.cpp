#include "X509Chain.hpp"

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_SYSTEM
#include "System.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_CRYPTOGRAPHICEXCEPTION
#include "CryptographicException.hpp"
#endif

Elysium::Core::Security::Cryptography::X509Certificates::X509Chain::X509Chain()
	: _ChainPolicy()
{ }
Elysium::Core::Security::Cryptography::X509Certificates::X509Chain::~X509Chain()
{ }

Elysium::Core::Security::Cryptography::X509Certificates::X509ChainPolicy & Elysium::Core::Security::Cryptography::X509Certificates::X509Chain::GetChainPolicy()
{
	return _ChainPolicy;
}

const Elysium::Core::Security::Cryptography::X509Certificates::X509ChainPolicy & Elysium::Core::Security::Cryptography::X509Certificates::X509Chain::GetChainPolicy() const
{
	return _ChainPolicy;
}

const bool Elysium::Core::Security::Cryptography::X509Certificates::X509Chain::Build(const X509Certificate & Certificate)
{
	if (Certificate._CertificateContext == nullptr)
	{
		throw CryptographicException(u8"The certificate is unreadable.");
	}

	ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_CERTIFICATECHAINENGINECONFIG CertificateChainEngineConfig = ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_CERTIFICATECHAINENGINECONFIG();
	CertificateChainEngineConfig.cbSize = sizeof(ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_CERTIFICATECHAINENGINECONFIG);
	CertificateChainEngineConfig.hRestrictedRoot = nullptr;
	CertificateChainEngineConfig.hRestrictedTrust = nullptr;
	CertificateChainEngineConfig.hRestrictedOther = nullptr;
	CertificateChainEngineConfig.cAdditionalStore = 0;
	CertificateChainEngineConfig.rghAdditionalStore = nullptr;
	CertificateChainEngineConfig.dwFlags = CERT_CHAIN_CACHE_END_CERT;
	CertificateChainEngineConfig.dwUrlRetrievalTimeout = _ChainPolicy.GetUrlRetrievalTimeout().GetTotalMilliseconds();
	CertificateChainEngineConfig.MaximumCachedCertificates = 0;
	CertificateChainEngineConfig.CycleDetectionModulus = 0;

	ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_CERTIFICATECHAINENGINEHANDLE CertificateChainEngine;
	if (!CertCreateCertificateChainEngine(&CertificateChainEngineConfig, &CertificateChainEngine))
	{
		throw CryptographicException(u8"Certificate chain engine creation failed.");
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
	if(!CertGetCertificateChain(nullptr, Certificate._CertificateContext, nullptr, nullptr, &ChainParameter, Flags, nullptr, &ChainContext))
	{
		throw CryptographicException(u8"Certificate chain creation failed.");
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
void Elysium::Core::Security::Cryptography::X509Certificates::X509Chain::Reset()
{
	_ChainPolicy.Reset();
}
