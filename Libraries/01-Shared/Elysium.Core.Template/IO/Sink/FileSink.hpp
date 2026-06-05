/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_SINK_FILESINK
#define ELYSIUM_CORE_TEMPLATE_IO_SINK_FILESINK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_DEVICE_FILEDEVICE
#include "../Device/FileDevice.hpp"
#endif

namespace Elysium::Core::Template::IO::Sink
{
	class FileSink
	{
	public:
		using DeviceType = Elysium::Core::Template::IO::Device::FileDevice;
	public:
		constexpr FileSink() noexcept = delete;

		inline constexpr FileSink(DeviceType& Device) noexcept
			: _Device(Device)
		{ }

		constexpr FileSink(const FileSink& Source) = delete;

		constexpr FileSink(FileSink&& Right) noexcept = delete;

		~FileSink() = default;
	public:
		constexpr FileSink& operator=(const FileSink& Source) = delete;

		constexpr FileSink& operator=(FileSink&& Right) noexcept = delete;
	public:
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

		inline void Flush(const bool FlushToDisk = true)
		{
			_Device.Flush(FlushToDisk);
		}
	private:
		DeviceType& _Device;
	};
}
#endif
