/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_SOURCE_FILESOURCE
#define ELYSIUM_CORE_TEMPLATE_IO_SOURCE_FILESOURCE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_DEVICE_FILEDEVICE
#include "../Device/FileDevice.hpp"
#endif

namespace Elysium::Core::Template::IO::Source
{
	class FileSource
	{
	public:
		using DeviceType = Elysium::Core::Template::IO::Device::FileDevice;
	public:
		constexpr FileSource() noexcept = delete;

		inline constexpr FileSource(DeviceType& Device) noexcept
			: _Device(Device)
		{ }

		constexpr FileSource(const FileSource& Source) = delete;

		constexpr FileSource(FileSource&& Right) noexcept = delete;

		~FileSource() = default;
	public:
		constexpr FileSource& operator=(const FileSource& Source) = delete;

		constexpr FileSource& operator=(FileSource&& Right) noexcept = delete;
	public:
		inline constexpr const DeviceType& GetDevice() const
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
		inline const Elysium::Core::size Read(Elysium::Core::byte* Buffer, const Elysium::Core::size Count)
		{
			return _Device.Read(Buffer, Count);
		}
	private:
		DeviceType& _Device;
	};
}
#endif
