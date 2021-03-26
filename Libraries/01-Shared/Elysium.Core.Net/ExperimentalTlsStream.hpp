/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_SECURITY_EXPERIMENTALTLSSTREAM
#define ELYSIUM_CORE_NET_SECURITY_EXPERIMENTALTLSSTREAM

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

namespace Elysium::Core::Net::Security
{
	class ELYSIUM_CORE_NET_API ExperimentalTlsStream final : public AuthenticatedStream
	{
	public:
		ExperimentalTlsStream(IO::Stream& InnerStream, const bool LeaveInnerStreamOpen, const TlsClientAuthenticationOptions& AuthenticationOptions);
		ExperimentalTlsStream(const ExperimentalTlsStream& Source) = delete;
		ExperimentalTlsStream(ExperimentalTlsStream&& Right) noexcept = delete;
		virtual ~ExperimentalTlsStream();

		ExperimentalTlsStream& operator=(const ExperimentalTlsStream& Source) = delete;
		ExperimentalTlsStream& operator=(ExperimentalTlsStream&& Right) noexcept = delete;

		virtual const bool GetCanRead() const override;
		virtual const bool GetCanSeek() const override;
		virtual const bool GetCanTimeout() const override;
		virtual const bool GetCanWrite() const override;

		virtual const size_t GetLength() const override;

		virtual const bool GetIsAuthenticated() const override;
		virtual const bool GetIsEncrypted() const override;
		virtual const bool GetIsMutuallyAuthenticated() const override;
		virtual const bool GetIsServer() const override;
		virtual const bool GetIsSigned() const override;

		virtual void SetLength(const size_t Value) override;
		virtual void SetPosition(const Elysium::Core::uint64_t Position) override;

		virtual void Close() override;
		virtual void Flush() override;
		virtual const size_t Seek(const Elysium::Core::int64_t Offset, const IO::SeekOrigin Origin) override;
		virtual const size_t Read(Elysium::Core::byte* Buffer, const size_t Count) override;
		virtual Elysium::Core::byte ReadByte() override;
		virtual void Write(const Elysium::Core::byte* Buffer, const size_t Count) override;

		void AuthenticateAsClient(const Elysium::Core::String& TargetHost, const Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection* ClientCertificates = nullptr, const Elysium::Core::Security::Authentication::TlsProtocols EnabledTlsProtocols = Elysium::Core::Security::Authentication::TlsProtocols::Tls12, const bool CheckCertficateRevocation = true);
		void AuthenticateAsServer(const Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection& ClientCertificates, const bool ClientCertificateRequired, const Elysium::Core::Security::Authentication::TlsProtocols EnabledTlsProtocols, const bool CheckCertficateRevocation);
	private:
		const TlsClientAuthenticationOptions _AuthenticationOptions;

		Elysium::Core::Collections::Template::Array<Elysium::Core::byte> _LocalRandom;
		Elysium::Core::Collections::Template::Array<Elysium::Core::byte> _SessionId;
		Elysium::Core::Collections::Template::Array<Elysium::Core::byte> _RemoteRandom;
		TlsCipherSuite _ServerSelectedCipherSuite;
		uint8_t _ServerSelectedCompressionMethod;

		void WriteClientHello(const Elysium::Core::Security::Authentication::TlsProtocols EnabledTlsProtocols);
		void ReadServerHello();
		void ReadServerCertificates();
		void ReadServerKeyExchange();
		void ReadServerHelloDone();
	};
}
#endif
