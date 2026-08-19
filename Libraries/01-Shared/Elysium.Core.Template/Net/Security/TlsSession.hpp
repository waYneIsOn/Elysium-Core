/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_NET_SECURITY_TLSSESSION
#define ELYSIUM_CORE_TEMPLATE_NET_SECURITY_TLSSESSION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../Container/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_AUTHENTICATION_TLSPROTOCOL
#include "../../Security/Authentication/TlsProtocols.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATE
#include "../../Security/Cryptography/X509Certificates/X509Certificate.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_COMPILATIONSETTINGS
#include "../../System/CompilationSettings.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRINGVIEW
#include "../../Text/StringView.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
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
#endif

namespace Elysium::Core::Template::Net::Security
{
#if defined ELYSIUM_CORE_USEEXPERIMENTALIMPLEMENTATION_TLS

#elif defined ELYSIUM_CORE_OS_WINDOWS
	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="InnerSink"></typeparam>
	/// <typeparam name="InnerSource"></typeparam>
	template <class InnerSink, class InnerSource>
	class TlsSession
	{
	public:
		inline constexpr TlsSession(InnerSink& Sink, InnerSource& Source)
			: _Sink(Sink), _Source(Source),
			_TargetHost{}, _TlsProtocols{},
			_CredentialHandle{}, _Context{}, _Sizes{}
		{ }
	public:
		inline constexpr const bool operator==(const TlsSession& Other) const noexcept
		{	// @ToDo
			return this == &Other;
		}
	public:
		inline void AuthenticateAsClient(const Elysium::Core::Template::Text::StringView<char8_t> TargetHost,
			const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate>* ClientCertificates = nullptr,
			const Elysium::Core::Template::Security::Authentication::TlsProtocols EnabledTlsProtocols = Elysium::Core::Template::Security::Authentication::TlsProtocols::Tls12,
			const bool CheckCertficateRevocation = true)
		{
			throw;
		}
		/*
		inline void AuthenticateAsServer(const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate& ServerCertificate,
			const bool ClientCertificateRequired, const Elysium::Core::Security::Authentication::TlsProtocols EnabledTlsProtocols,
			const bool CheckCertficateRevocation)
		{

		}
		*/
	private:
		InnerSink& _Sink;
		InnerSource& _Source;

		Elysium::Core::Template::Text::String<char8_t> _TargetHost;
		Elysium::Core::Template::Security::Authentication::TlsProtocols _TlsProtocols;

		CredHandle _CredentialHandle;
		SecHandle _Context;
		SecPkgContext_StreamSizes _Sizes;
	};
#endif
}
#endif