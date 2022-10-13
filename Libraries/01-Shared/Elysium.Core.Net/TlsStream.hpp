/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_SECURITY_TLSSTREAM
#define ELYSIUM_CORE_NET_SECURITY_TLSSTREAM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_NET_SECURITY_AUTHENTICATEDSTREAM
#include "AuthenticatedStream.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SECURITY_TLSCLIENTAUTHENTICATIONOPTIONS
#include "TlsClientAuthenticationOptions.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATECOLLECTION
#include "../Elysium.Core.Security.Cryptography.X509Certificates/X509CertificateCollection.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_AUTHENTICATION_TLSPROTOCOLS
#include "../Elysium.Core.Security/TlsProtocols.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SECURITY_TLSCIPHERSUITE
#include "TlsCipherSuite.hpp"
#endif





#define SECURITY_WIN32
#include <security.h>

#ifndef __SSPI_H__
#include <sspi.h>
#endif






namespace Elysium::Core::Net::Security
{
	class ELYSIUM_CORE_NET_API TlsStream final : public AuthenticatedStream
	{
	public:
		TlsStream(IO::Stream & InnerStream, const bool LeaveInnerStreamOpen, const TlsClientAuthenticationOptions & AuthenticationOptions);
		TlsStream(const TlsStream& Source) = delete;
		TlsStream(TlsStream&& Right) noexcept = delete;
		virtual ~TlsStream();

		TlsStream& operator=(const TlsStream& Source) = delete;
		TlsStream& operator=(TlsStream&& Right) noexcept = delete;

		virtual const bool GetCanRead() const override;
		virtual const bool GetCanSeek() const override;
		virtual const bool GetCanTimeout() const override;
		virtual const bool GetCanWrite() const override;

		virtual const Elysium::Core::size GetLength() const override;

		virtual const bool GetIsAuthenticated() const override;
		virtual const bool GetIsEncrypted() const override;
		virtual const bool GetIsMutuallyAuthenticated() const override;
		virtual const bool GetIsServer() const override;
		virtual const bool GetIsSigned() const override;

		virtual void SetLength(const Elysium::Core::size Value) override;
		virtual void SetPosition(const Elysium::Core::uint64_t Position) override;

		virtual void Close() override;
		virtual void Flush() override;
		virtual const Elysium::Core::size Seek(const Elysium::Core::int64_t Offset, const IO::SeekOrigin Origin) override;
		virtual const Elysium::Core::size Read(Elysium::Core::byte* Buffer, const Elysium::Core::size Count) override;
		virtual Elysium::Core::byte ReadByte() override;
		virtual void Write(const Elysium::Core::byte* Buffer, const Elysium::Core::size Count) override;

		void AuthenticateAsClient(const Elysium::Core::Utf8String& TargetHost, const Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection* ClientCertificates = nullptr, const Elysium::Core::Security::Authentication::TlsProtocols EnabledTlsProtocols = Elysium::Core::Security::Authentication::TlsProtocols::Tls12, const bool CheckCertficateRevocation = true);
		void AuthenticateAsServer(const Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection& ClientCertificates, const bool ClientCertificateRequired, const Elysium::Core::Security::Authentication::TlsProtocols EnabledTlsProtocols, const bool CheckCertficateRevocation);
	private:
		const TlsClientAuthenticationOptions _AuthenticationOptions;

		Elysium::Core::Template::Container::Vector<Elysium::Core::byte> _ExtraBuffer;
		Elysium::Core::Collections::Template::Array<Elysium::Core::byte> _InBuffer;
		Elysium::Core::Collections::Template::Array<Elysium::Core::byte> _OutBuffer;

		Elysium::Core::Utf8String _TargetHost;
		Elysium::Core::Security::Authentication::TlsProtocols _TlsProtocols;
		CredHandle _CredentialHandle;
		_SecHandle _Context;
		SecPkgContext_StreamSizes _Sizes;

		void PerformClientHandshake();
		void ClientHandshakeLoop(const bool Read);
		void GetServersCertificate();
		void GetStreamEncryptionProperties();

		//void CreateCredentials();
		//void GetNewClientCredentials();
	};
}
#endif
