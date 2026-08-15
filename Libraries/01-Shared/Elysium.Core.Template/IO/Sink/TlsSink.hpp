/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_SINK_TLSSINK
#define ELYSIUM_CORE_TEMPLATE_IO_SINK_TLSSINK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../System/OperatingSystem.hpp"
#endif

namespace Elysium::Core::Template::IO::Sink
{
#if defined ELYSIUM_CORE_USEEXPERIMENTALIMPLEMENTATION_TLS

#elif defined ELYSIUM_CORE_OS_WINDOWS
	// @ToDo: concept for sinks!
	template <class InnerSink>
	class TlsSink
	{
	public:
		using DeviceType = InnerSink::DeviceType;
	public:
		constexpr TlsSink(InnerSink& InnerSink)
			: _InnerSink(InnerSink)
		{}

		constexpr TlsSink(const TlsSink& Source) = delete;

		constexpr TlsSink(TlsSink&& Right) noexcept = delete;

		inline constexpr ~TlsSink()
		{
			Flush();
		}
	public:
		constexpr TlsSink& operator=(const TlsSink& Source) = delete;

		constexpr TlsSink& operator=(TlsSink&& Right) noexcept = delete;
	public:
		inline constexpr const Elysium::Core::Template::System::size GetLength() const
		{
			return _InnerSink.GetLength();
		}

		inline constexpr const Elysium::Core::Template::System::uint64_t GetPosition() const
		{
			return _InnerSink.GetPosition();
		}

		inline constexpr const DeviceType& GetDevice() const
		{
			return _InnerSink.GetDevice();
		}
	public:
		/*
		inline void AuthenticateAsClient(const Elysium::Core::Template::Text::StringView<char8_t> TargetHost,
			const Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection* ClientCertificates = nullptr,
			const Elysium::Core::Security::Authentication::TlsProtocols EnabledTlsProtocols = Elysium::Core::Security::Authentication::TlsProtocols::Tls12,
			const bool CheckCertficateRevocation = true)
		{

		}

		inline void AuthenticateAsServer(const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate& ServerCertificate,
			const bool ClientCertificateRequired, const Elysium::Core::Security::Authentication::TlsProtocols EnabledTlsProtocols,
			const bool CheckCertficateRevocation)
		{

		}
		*/
	public:
		inline void Write(const Elysium::Core::Template::System::byte* Buffer, const Elysium::Core::Template::System::size Count)
		{
			throw;
		}

		inline void Flush()
		{
			throw;
		}
	private:
		InnerSink& _InnerSink;
	};
#endif
}
#endif
