/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_SOURCE_SOCKETSOURCE
#define ELYSIUM_CORE_TEMPLATE_IO_SOURCE_SOCKETSOURCE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_DEVICE_SOCKETDEVICE
#include "../Device/SocketDevice.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_SOURCE_POLICY_NOPOLICY
#include "Policy/NoPolicy.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Source
{
	class SocketSource
	{
	public:
		using DeviceType = Elysium::Core::Template::IO::Device::SocketDevice;

		using MostInnerSourceType = SocketSource;
	public:
		constexpr SocketSource() noexcept = delete;

		inline constexpr SocketSource(DeviceType& Device) noexcept
			: _Device(Device)
		{ }

		constexpr SocketSource(const SocketSource& Source) = delete;

		constexpr SocketSource(SocketSource&& Right) noexcept = delete;

		constexpr ~SocketSource() = default;
	public:
		constexpr SocketSource& operator=(const SocketSource& Source) = delete;

		constexpr SocketSource& operator=(SocketSource&& Right) noexcept = delete;
	public:
		inline MostInnerSourceType& GetMostInnerSource()
		{
			return *this;
		}

		inline DeviceType& GetDevice()
		{
			return _Device;
		}

		inline constexpr DeviceType& GetDevice() const
		{
			return _Device;
		}
	public:
		inline constexpr const Elysium::Core::Template::System::size GetLength() const
		{
			return _Device.GetLength();
		}

		inline constexpr const Elysium::Core::Template::System::uint64_t GetPosition() const
		{
			return _Device.GetPosition();
		}
	public:
		inline const Elysium::Core::Template::IO::ReadResult ReadBlock(Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte>& DataView)
		{
			throw;
		}

		inline void AdvanceReadingBlock(const Elysium::Core::Template::System::size Length)
		{
			throw;
		}
	private:
		DeviceType& _Device;
	};
}
#endif