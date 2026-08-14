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

		inline constexpr SocketSource(DeviceType& Device, const Elysium::Core::Template::System::size BufferSize = 4096) noexcept
			: _Buffer(0 == BufferSize ? 4096 : BufferSize), _ReadPosition(0), _WritePosition(0), _Device(Device)
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
				throw;
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