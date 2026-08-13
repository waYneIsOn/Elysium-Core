/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_SINK_TLSSINK
#define ELYSIUM_CORE_TEMPLATE_IO_SINK_TLSSINK

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::IO::Sink
{
	// @ToDo: concept for sinks!
	template <class InnerSink>
	class TlsSink
	{
	public:
		using DeviceType = InnerSink::DeviceType;
	public:
		constexpr TlsSink(InnerSink& InnerSink)
			: _InnerSink(InnerSink)
		{ }

		constexpr TlsSink(const TlsSink& Source) = delete;

		constexpr TlsSink(TlsSink&& Right) noexcept = delete;

		inline constexpr ~TlsSink()
		{
			Flush();
		}
	public:
		constexpr TlsSink& operator=(const TlsSink& Source) = delete;

		constexpr TlsSink& operator=(TlsSink&& Right) noexcept = delete;
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
			//_Position = Position;
		}
	public:
		inline void Flush()
		{
			//_InnerSink.Write(&_Buffer[0], _Position);
			if constexpr (requires { _InnerSink.Flush(); })
			{
				_InnerSink.Flush();
			}

			//_Position = 0;
		}

		inline void Write(const Elysium::Core::Template::System::byte* Buffer, const Elysium::Core::Template::System::size Count)
		{
			
		}
	private:
		InnerSink& _InnerSink;
	};
}
#endif
