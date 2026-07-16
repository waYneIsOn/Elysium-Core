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

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_FIXEDSIZEBUFFER
#include "../../Container/FixedSizeBuffer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VIEW_SPAN
#include "../../Container/View/Span.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_READRESULT
#include "../ReadResult.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_DEVICE_FILEDEVICE
#include "../Device/FileDevice.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Source
{
	class FileSource
	{
	public:
		using DeviceType = Elysium::Core::Template::IO::Device::FileDevice;

		using MostInnerSourceType = FileSource;
	public:
		constexpr FileSource() noexcept = delete;

		inline constexpr FileSource(DeviceType& Device, const Elysium::Core::Template::System::size BufferSize = 4096) noexcept
			: _Buffer(0 == BufferSize ? 4096 : BufferSize), _ReadPosition(0), _WritePosition(0), _Device(Device)
		{ }

		constexpr FileSource(const FileSource& Source) = delete;

		constexpr FileSource(FileSource&& Right) noexcept = delete;

		~FileSource() = default;
	public:
		constexpr FileSource& operator=(const FileSource& Source) = delete;

		constexpr FileSource& operator=(FileSource&& Right) noexcept = delete;
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
		inline void SetPosition(const Elysium::Core::Template::System::uint64_t Position)
		{
			_Device.SetPosition(Position);
			_ReadPosition = 0;
			_WritePosition = 0;
		}
	public:
		inline void Close()
		{
			_Device.Close();
		}
	public:
		inline const Elysium::Core::Template::IO::ReadResult ReadBlock(Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte>& DataView)
		{
			if (_ReadPosition == _WritePosition)
			{
				_ReadPosition = 0;
				_WritePosition = _Device.Read(&_Buffer[_ReadPosition], _Buffer.GetCapacity());

				if (0 == _WritePosition)
				{
					return Elysium::Core::Template::IO::ReadResult::EndOfStream;
				}
			}

			DataView.SetData(&_Buffer[_ReadPosition]);
			DataView.SetLength(_WritePosition - _ReadPosition);

			return Elysium::Core::Template::IO::ReadResult::HasData;
		}

		inline void AdvanceReadingBlock(const Elysium::Core::Template::System::size Length)
		{
			if (_ReadPosition + Length > _Buffer.GetCapacity())
			{	// @ToDo
				throw 1;
			}

			_ReadPosition += Length;
		}
	private:
		Elysium::Core::Template::Container::FixedSizeBuffer<Elysium::Core::Template::System::byte> _Buffer;
		Elysium::Core::Template::System::size _ReadPosition;
		Elysium::Core::Template::System::size _WritePosition;
		DeviceType& _Device;
	};
}
#endif
