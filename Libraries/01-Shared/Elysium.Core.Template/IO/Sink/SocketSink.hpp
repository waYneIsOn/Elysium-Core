/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_SINK_SOCKETSINK
#define ELYSIUM_CORE_TEMPLATE_IO_SINK_SOCKETSINK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_DEVICE_SOCKETDEVICE
#include "../Device/SocketDevice.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Sink
{
	class SocketSink
	{
	public:
		using DeviceType = Elysium::Core::Template::IO::Device::SocketDevice;
	public:
		constexpr SocketSink() noexcept = delete;

		inline constexpr SocketSink(DeviceType& Device) noexcept
			: _Device(Device)
		{ }

		constexpr SocketSink(const SocketSink& Source) = delete;

		constexpr SocketSink(SocketSink&& Right) noexcept = delete;

		constexpr ~SocketSink() = default;
	public:
		constexpr SocketSink& operator=(const SocketSink& Source) = delete;

		constexpr SocketSink& operator=(SocketSink&& Right) noexcept = delete;
	public:
		inline DeviceType& GetDevice()
		{
			return _Device;
		}

		inline constexpr DeviceType& GetDevice() const
		{
			return _Device;
		}
	public:
		inline void Close()
		{
			_Device.Close();
		}
	public:
		inline void Write(const Elysium::Core::Template::System::byte* Buffer, const Elysium::Core::Template::System::size Count)
		{
			_Device.Write(Buffer, Count);
		}

		inline void Flush()
		{
			_Device.Flush();
		}
	private:
		DeviceType& _Device;
	};
}
#endif
