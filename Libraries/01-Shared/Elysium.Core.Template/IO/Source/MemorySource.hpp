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
		inline void SetPosition(const Elysium::Core::Template::System::uint64_t Position)
		{
			_Device.SetPosition(Position);
		}
	public:
		inline const Elysium::Core::Template::IO::ReadResult ReadBlock(Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte>& DataView)
		{
			return _Device.ReadBlock(DataView);
		}

		inline void AdvanceReadingBlock(const Elysium::Core::Template::System::size Length)
		{
			_Device.AdvanceReadingBlock(Length);
		}
	private:
		DeviceType& _Device;
	};
}
#endif
