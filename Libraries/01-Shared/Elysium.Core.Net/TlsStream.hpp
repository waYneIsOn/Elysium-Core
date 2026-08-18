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

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_AUTHENTICATION_TLSPROTOCOL
#include "../Elysium.Core.Template/Security/Authentication/TlsProtocols.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SECURITY_TLSCIPHERSUITE
#include "../Elysium.Core.Template/Net/Security/TlsCipherSuite.hpp"
#endif

#ifndef ELYSIUM_CORE_CONTAINER_VECTOROFBYTE
#include "../Elysium.Core/VectorOfByte.hpp"
#endif
/*
#ifndef _WINDOWS_
#include <Windows.h>
#endif
*/
#ifndef _WINTERNL_
#include <winternl.h>
#endif

#define SECURITY_WIN32
#include <security.h>
/*
#ifndef __SSPI_H__
#include <sspi.h>
#endif
*/
#ifndef __SCHANNEL_H__
#define SCHANNEL_USE_BLACKLISTS
#include <schannel.h>
#endif

namespace Elysium::Core::Net::Security
{
	class ELYSIUM_CORE_NET_API TlsStream final 
		: public AuthenticatedStream
	{
	public:
		TlsStream(IO::Stream & InnerStream, const bool LeaveInnerStreamOpen, const TlsClientAuthenticationOptions & AuthenticationOptions);
		
		TlsStream(const TlsStream& Source) = delete;

		TlsStream(TlsStream&& Right) noexcept = delete;

		virtual ~TlsStream();
	public:
		TlsStream& operator=(const TlsStream& Source) = delete;

		TlsStream& operator=(TlsStream&& Right) noexcept = delete;
	public:
		virtual const bool GetIsAuthenticated() const override;

		virtual const bool GetIsEncrypted() const override;

		virtual const bool GetIsMutuallyAuthenticated() const override;

		virtual const bool GetIsServer() const override;

		virtual const bool GetIsSigned() const override;
	public:
		virtual void Close() override;

		virtual void Flush() override;

		virtual const Elysium::Core::size Seek(const Elysium::Core::int64_t Offset, const IO::SeekOrigin Origin) override;

		virtual const Elysium::Core::size Read(Elysium::Core::byte* Buffer, const Elysium::Core::size Count) override;

		virtual Elysium::Core::byte ReadByte() override;

		virtual void Write(const Elysium::Core::byte* Buffer, const Elysium::Core::size Count) override;
	public:
		void AuthenticateAsClient(const Elysium::Core::Utf8String& TargetHost,
			const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate>* ClientCertificates = nullptr,
			const Elysium::Core::Template::Security::Authentication::TlsProtocols EnabledTlsProtocols =
				Elysium::Core::Template::Security::Authentication::TlsProtocols::Tls12, const bool CheckCertficateRevocation = true);
		
		void AuthenticateAsServer(const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate& ServerCertificate,
			const bool ClientCertificateRequired, const Elysium::Core::Template::Security::Authentication::TlsProtocols EnabledTlsProtocols,
			const bool CheckCertficateRevocation);
	private:
		const TlsClientAuthenticationOptions _AuthenticationOptions;

		Elysium::Core::Container::VectorOfByte _ExtraBuffer;
		Elysium::Core::Container::VectorOfByte _InBuffer;
		Elysium::Core::Container::VectorOfByte _OutBuffer;

		Elysium::Core::Utf8String _TargetHost;
		Elysium::Core::Template::Security::Authentication::TlsProtocols _TlsProtocols;
		CredHandle _CredentialHandle;
		SecHandle _Context;
		SecPkgContext_StreamSizes _Sizes;
	private:
		void PerformClientHandshake();

		void ClientHandshakeLoop(const bool Read);

		void GetServersCertificate();

		void GetStreamEncryptionProperties();
	private:
		//void AquireCredentialHandle();
	};
}
#endif
