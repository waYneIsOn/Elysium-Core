/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_SINK_DEFLATESINK
#define ELYSIUM_CORE_TEMPLATE_IO_SINK_DEFLATESINK

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
	template <class InnerSink>
	class DeflateSink
	{
	public:
		using DeviceType = InnerSink::DeviceType;
	public:
		inline constexpr DeflateSink(InnerSink& InnerSink, const Elysium::Core::Template::System::size BufferSize = 4096) noexcept
			: _Buffer(0 == BufferSize ? 4096 : BufferSize), _Position(0), _InnerSink(InnerSink)
		{}

		constexpr DeflateSink(const DeflateSink& Source) = delete;

		constexpr DeflateSink(DeflateSink&& Right) noexcept = delete;

		inline ~DeflateSink()
		{
			Close();
		}
	public:
		constexpr DeflateSink& operator=(const DeflateSink& Source) = delete;

		constexpr DeflateSink& operator=(DeflateSink&& Right) noexcept = delete;
	public:
		inline constexpr const Elysium::Core::Template::System::size GetLength() const
		{
			return _InnerSink.GetLength();
		}

		inline constexpr const Elysium::Core::Template::System::uint64_t GetPosition() const
		{
			return _InnerSink.GetPosition();
		}

		inline constexpr const DeviceType& GetDevice() const
		{
			return _InnerSink.GetDevice();
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

		}
	private:
		Elysium::Core::Template::Container::FixedSizeBuffer<Elysium::Core::Template::System::byte> _Buffer;
		Elysium::Core::Template::System::size _Position;
		InnerSink& _InnerSink;
	};
}
#endif
