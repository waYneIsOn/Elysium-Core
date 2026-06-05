/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_SOURCE_MEMORYSOURCE
#define ELYSIUM_CORE_TEMPLATE_IO_SOURCE_MEMORYSOURCE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_DEVICE_MEMORYDEVICE
#include "../Device/MemoryDevice.hpp"
#endif

namespace Elysium::Core::Template::IO::Source
{
	class MemorySource
	{
	public:
		using DeviceType = Elysium::Core::Template::IO::Device::MemoryDevice;
	public:
		constexpr MemorySource() noexcept = delete;

		inline constexpr MemorySource(DeviceType& Device) noexcept
			: _Device(Device)
		{ }

		constexpr MemorySource(const MemorySource& Source) = delete;

		constexpr MemorySource(MemorySource&& Right) noexcept = delete;

		~MemorySource() = default;
	public:
		constexpr MemorySource& operator=(const MemorySource& Source) = delete;

		constexpr MemorySource& operator=(MemorySource&& Right) noexcept = delete;
	public:
		inline constexpr const Elysium::Core::Template::System::size GetLength() const
		{
			return _Device.GetLength();
		}

		inline constexpr const Elysium::Core::Template::System::uint64_t GetPosition() const
		{
			return _Device.GetPosition();
		}

		inline constexpr const DeviceType& GetDevice() const
		{
			return _Device;
		}
	public:
		inline void SetPosition(const Elysium::Core::Template::System::uint64_t Position)
		{
			_Device.SetPosition(Position);
		}
	public:
		inline const Elysium::Core::size Read(Elysium::Core::byte* Buffer, const Elysium::Core::size Count)
		{
			return _Device.Read(Buffer, Count);
		}
	private:
		DeviceType& _Device;
	};
}
#endif
