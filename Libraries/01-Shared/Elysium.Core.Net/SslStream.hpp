/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_SECURITY_SSLSTREAM
#define ELYSIUM_CORE_NET_SECURITY_SSLSTREAM

#ifdef _MSC_VER
#pragma once
#endif

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

#ifndef __SSPI_H__
#define SECURITY_WIN32
#include <sspi.h>
#endif

namespace Elysium::Core::Net::Security
{
#define RemoteCertificateValidationCallback Delegate<const bool, const void*, const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&, const Elysium::Core::Security::Cryptography::X509Certificates::X509Chain&, const Elysium::Core::Net::Security::SslPolicyErrors>
#define LocalCertificateSelectionCallback Delegate<void, const void*, const String&, const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&, const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&, const Collections::Template::Array<String>&>

	class ELYSIUM_CORE_NET_API SslStream : public AuthenticatedStream
	{
	public:
		SslStream(IO::Stream& InnerStream, const bool LeaveInnerStreamOpen, const RemoteCertificateValidationCallback* UserCertificateValidationCallback, const LocalCertificateSelectionCallback* UserCertificateSelectionCallback, const EncryptionPolicy EncryptionPolicy);
		virtual ~SslStream();

		virtual bool GetCanRead() const override;
		virtual bool GetCanSeek() const override;
		virtual bool GetCanTimeout() const;
		virtual bool GetCanWrite() const override;

		virtual const size_t GetLength() override;

		virtual const bool GetIsAuthenticated() const override;
		virtual const bool GetIsEncrypted() const override;
		virtual const bool GetIsMutuallyAuthenticated() const override;
		virtual const bool GetIsServer() const override;
		virtual const bool GetIsSigned() const override;

		virtual void SetLength(size_t Value) override;
		virtual void SetPosition(int64_t Position) override;

		virtual void Close() override;
		virtual void Flush() override;
		virtual void Seek(const int64_t Offset, const IO::SeekOrigin Origin) override;
		virtual size_t Read(byte* Buffer, const size_t Count) override;
		virtual int32_t ReadByte() override;
		virtual void Write(const byte* Buffer, const size_t Count) override;

		virtual void AuthenticateAsClient(const String& TargetHost, const Core::Security::Cryptography::X509Certificates::X509CertificateCollection* ClientCertificates = nullptr, const SslProtocols EnabledSslProtocols = SslProtocols::Tls13, const bool CheckCertficateRevocation = true);
		virtual void AuthenticateAsServer(const Core::Security::Cryptography::X509Certificates::X509CertificateCollection& ClientCertificates, const bool ClientCertificateRequired, const SslProtocols EnabledSslProtocols, const bool CheckCertficateRevocation);
	private:
		HINSTANCE _SecurityLibraryHandle;
		PSecurityFunctionTable _SecuritySupportProviderInterface;

		CredHandle _hClientCreds;
		CtxtHandle _hContext;
		SecBuffer _ExtraData;

		HINSTANCE LoadSecurityLibrary();
		void UnloadSecurityLibrary();

		void PrepareCredentials();

		void ClientHandshakeLoop(const bool PerformInitialRead);
	};
}
#endif
