/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

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
#include "../Elysium.Core.Security/X509CertificateCollection.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_AUTHENTICATION_TLSPROTOCOLS
#include "../Elysium.Core.Security/TlsProtocols.hpp"
#endif

namespace Elysium::Core::Net::Security
{
	class ELYSIUM_CORE_NET_API TlsStream final : public AuthenticatedStream
	{
	public:
		TlsStream(IO::Stream& InnerStream, const bool LeaveInnerStreamOpen, const TlsClientAuthenticationOptions& AuthenticationOptions);
		TlsStream(const TlsStream& Source) = delete;
		TlsStream(TlsStream&& Right) noexcept = delete;
		virtual ~TlsStream();

		TlsStream& operator=(const TlsStream& Source) = delete;
		TlsStream& operator=(TlsStream&& Right) noexcept = delete;

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
		virtual Elysium::Core::byte ReadByte() override;
		virtual void Write(const byte* Buffer, const size_t Count) override;

		void AuthenticateAsClient(const String& TargetHost, const Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection* ClientCertificates = nullptr, const Elysium::Core::Security::Authentication::TlsProtocols EnabledTlsProtocols = Elysium::Core::Security::Authentication::TlsProtocols::Tls12, const bool CheckCertficateRevocation = true);
		void AuthenticateAsServer(const Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection& ClientCertificates, const bool ClientCertificateRequired, const Elysium::Core::Security::Authentication::TlsProtocols EnabledTlsProtocols, const bool CheckCertficateRevocation);
	private:
		const TlsClientAuthenticationOptions _AuthenticationOptions;

		void WriteClientHello(const Elysium::Core::Security::Authentication::TlsProtocols EnabledTlsProtocols);
		void ReadServerHello();
		void ReadServerCertificates();
		void ReadServerKeyExchange();
		void ReadServerHelloDone();
	};
}
#endif
