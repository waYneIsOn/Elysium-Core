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

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_FIXEDSIZEBUFFER
#include "../../Container/FixedSizeBuffer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_DEVICE_SOCKETDEVICE
#include "../Device/SocketDevice.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_MIN
#include "../../Math/Min.hpp"
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

		inline constexpr SocketSink(DeviceType& Device, const Elysium::Core::Template::System::size BufferSize = 4096) noexcept
			: _Buffer(0 == BufferSize ? 4096 : BufferSize), _Position{}, _Device(Device)
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
		inline void Write(const Elysium::Core::Template::System::byte* Buffer, const Elysium::Core::Template::System::size Count)
		{
			if (Count >= _Buffer.GetCapacity())
			{	// This case would possibly result in multiple copies to local buffer and then flushing to underlying stream.
				// The optimization here is to flush once and then write directly to the underlying buffer
				if (0 != _Position)
				{
					Flush();
				}

				_Device.Write(Buffer, Count);
			}
			else
			{	// Why not flush and then write?
				// In the case of "flush first, write afterwards" there could be a case where writing results in the local buffer being full and no more data needing to be written.
				// The underlying stream then won't receive that data until the "next write iteration" or until the stream gets destructed - so potentially for quite some time.
				// So basically the other way round just ensures the underlying stream getting data every time the buffer is full.
				Elysium::Core::Template::System::size TotalBytesWritten = 0;
				do
				{
					Elysium::Core::Template::System::size BytesToWrite = Elysium::Core::Template::Math::Min(_Buffer.GetCapacity(), Count - TotalBytesWritten);

					Elysium::Core::Template::Memory::MemCpy(&_Buffer[_Position], &Buffer[TotalBytesWritten], BytesToWrite);

					TotalBytesWritten += BytesToWrite;
					_Position += BytesToWrite;

					if (_Buffer.GetCapacity() <= _Position)
					{
						Flush();
					}
				} while (TotalBytesWritten < Count);
			}
		}

		inline void Flush()
		{
			_Device.Write(&_Buffer[0], _Position);
			_Position = 0;
		}
	private:
		Elysium::Core::Template::Container::FixedSizeBuffer<Elysium::Core::Template::System::byte> _Buffer;
		Elysium::Core::Template::System::size _Position;
		DeviceType& _Device;
	};
}
#endif
