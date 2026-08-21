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
	// @ToDo: concept for sinks!
	template <class InnerSink, class TlsSession>
	class TlsSink
	{
	public:
		using DeviceType = InnerSink::DeviceType;
	public:
		constexpr TlsSink() noexcept = delete;

		constexpr TlsSink(InnerSink& Sink, TlsSession& Session)
			: _InnerSink(Sink), _Session(Session)
		{ }

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
		inline constexpr const DeviceType& GetDevice() const
		{
			return _InnerSink.GetDevice();
		}
		
		inline constexpr const TlsSession& GetSession() const
		{
			return _Session;
		}
	public:
		inline void Write(const Elysium::Core::Template::System::byte* Buffer, const Elysium::Core::Template::System::size Count)
		{
			_Session.Write(Buffer, Count);
		}

		inline void Flush()
		{
			_Session.Flush();
		}
	private:
		InnerSink& _InnerSink;
		TlsSession& _Session;
	};
}
#endif
