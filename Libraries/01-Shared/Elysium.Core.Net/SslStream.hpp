/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_NET_SECURITY_SSLSTREAM
#define ELYSIUM_CORE_NET_SECURITY_SSLSTREAM

#ifndef ELYSIUM_CORE_NET_SECURITY_AUTHENTICATEDSTREAM
#include "AuthenticatedStream.hpp"
#endif

#ifndef ELYSIUM_CORE_DELEGATE
#include "../Elysium.Core/Delegate.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CHAIN
#include "../Elysium.Core.Security/X509Chain.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SECURITY_SSLPOLICYERRORS
#include "SslPolicyErrors.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SECURITY_ENCRYPTIONPOLICY
#include "EncryptionPolicy.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATECOLLECTION
#include "../Elysium.Core.Security/X509CertificateCollection.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SECURITY_SSLPROTOCOLS
#include "SslProtocols.hpp"
#endif

namespace Elysium::Core::Net::Security
{
#define RemoteCertificateValidationCallback Delegate<bool, const void*, const Core::Security::Cryptography::X509Certificates::X509Certificate&, const Core::Security::Cryptography::X509Certificates::X509Chain&, const SslPolicyErrors>
#define LocalCertificateSelectionCallback Delegate<void, const void*, const String&, const Core::Security::Cryptography::X509Certificates::X509Certificate&, const Core::Security::Cryptography::X509Certificates::X509Certificate&, const Collections::Template::Array<String>&>

	class ELYSIUM_CORE_NET_API SslStream : public AuthenticatedStream
	{
	public:
		SslStream(IO::Stream& InnerStream, const bool LeaveInnerStreamOpen, const RemoteCertificateValidationCallback* UserCertificateValidationCallback, const LocalCertificateSelectionCallback* UserCertificateSelectionCallback, const EncryptionPolicy EncryptionPolicy);
		virtual ~SslStream();

		virtual const bool GetIsAuthenticated() const override;
		virtual const bool GetIsEncrypted() const override;
		virtual const bool GetIsMutuallyAuthenticated() const override;
		virtual const bool GetIsServer() const override;
		virtual const bool GetIsSigned() const override;

		virtual void AuthenticateAsClient(const String& TargetHost, const Core::Security::Cryptography::X509Certificates::X509CertificateCollection& ClientCertificates, const SslProtocols EnabledSsslProtocols, const bool CheckCertficateRevocation);
		virtual void AuthenticateAsServer(const Core::Security::Cryptography::X509Certificates::X509CertificateCollection& ClientCertificates, const bool ClientCertificateRequired, const SslProtocols EnabledSsslProtocols, const bool CheckCertficateRevocation);
	};
}
#endif
