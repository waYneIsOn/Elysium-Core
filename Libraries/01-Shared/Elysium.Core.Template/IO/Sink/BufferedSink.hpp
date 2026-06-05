/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_SINK_BUFFEREDSINK
#define ELYSIUM_CORE_TEMPLATE_IO_SINK_BUFFEREDSINK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_FIXEDSIZEBUFFER
#include "../../Container/FixedSizeBuffer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_MIN
#include "../../Math/Min.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMCPY
#include "../../Memory/MemCpy.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Sink
{
	// @ToDo: concept for sinks!
	template <class S>
	class BufferedSink
	{
	public:
		inline constexpr BufferedSink(S& InnerSink, const Elysium::Core::Template::System::size BufferSize = 4096) noexcept
			: _Buffer(0 == BufferSize ? 4096 : BufferSize), _Position(0), _InnerSink(InnerSink)
		{ }

		constexpr BufferedSink(const BufferedSink& Source) = delete;

		constexpr BufferedSink(BufferedSink&& Right) noexcept = delete;

		inline ~BufferedSink()
		{
			Close();
		}
	public:
		constexpr BufferedSink& operator=(const BufferedSink& Source) = delete;

		constexpr BufferedSink& operator=(BufferedSink&& Right) noexcept = delete;
	public:
		inline constexpr const Elysium::Core::Template::System::size GetLength() const
		{
			return _InnerSink.GetLength();
		}

		inline constexpr const Elysium::Core::Template::System::uint64_t GetPosition() const
		{
			return _InnerSink.GetPosition();
		}
	public:
		inline void SetPosition(const Elysium::Core::Template::System::uint64_t Position)
		{
			_InnerSink.SetPosition(Position);
			_Position = Position;
		}
	public:
		inline void Close()
		{
			Flush();
			if constexpr (requires { _InnerSink.Close(); })
			{
				_InnerSink.Close();
			}
		}

		inline void Flush()
		{
			_InnerSink.Write(&_Buffer[0], _Position);
			if constexpr (requires { _InnerSink.Flush(); })
			{
				_InnerSink.Flush();
			}

			_Position = 0;
		}

		inline void Write(const Elysium::Core::Template::System::byte* Buffer, const Elysium::Core::Template::System::size Count)
		{
			if (Count >= _Buffer.GetCapacity())
			{	// This case would possibly result in multiple copies to local buffer and then flushing to underlying stream.
				// The optimization here is to flush once and then write directly to the underlying buffer
				if (0 != _Position)
				{
					Flush();
				}

				_InnerSink.Write(Buffer, Count);
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
	private:
		Elysium::Core::Template::Container::FixedSizeBuffer<Elysium::Core::Template::System::byte> _Buffer;
		Elysium::Core::Template::System::size _Position;
		S& _InnerSink;
	};
}
#endif
