/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_SINK_MEMORYSINK
#define ELYSIUM_CORE_TEMPLATE_IO_SINK_MEMORYSINK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_DEVICE_MEMORYDEVICE
#include "../Device/MemoryDevice.hpp"
#endif

namespace Elysium::Core::Template::IO::Sink
{
	class MemorySink
	{
	public:
		using DeviceType = Elysium::Core::Template::IO::Device::MemoryDevice;
	public:
		constexpr MemorySink() noexcept = delete;

		inline constexpr MemorySink(DeviceType& Device) noexcept
			: _Device(Device)
		{ }

		constexpr MemorySink(const MemorySink& Source) = delete;

		constexpr MemorySink(MemorySink&& Right) noexcept = delete;

		~MemorySink() = default;
	public:
		constexpr MemorySink& operator=(const MemorySink& Source) = delete;

		constexpr MemorySink& operator=(MemorySink&& Right) noexcept = delete;
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
		inline void Write(const Elysium::Core::Template::System::byte* Buffer, const Elysium::Core::Template::System::size Count)
		{
			_Device.Write(Buffer, Count);
		}
	private:
		DeviceType& _Device;
	};
}
#endif
