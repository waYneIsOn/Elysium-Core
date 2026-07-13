/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_INSTREAM
#define ELYSIUM_CORE_TEMPLATE_IO_INSTREAM

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::IO
{
	// @ToDo: concept for sinks!
	template<class Sink>
	class InStream
	{
	public:
		using DeviceType = Sink::DeviceType;
	public:
		constexpr InStream() noexcept = default;

		inline constexpr InStream(Sink& Sink) noexcept
			: _Sink(Sink)
		{ }

		constexpr InStream(const InStream& Source) = delete;

		constexpr InStream(InStream&& Right) noexcept = delete;

		inline ~InStream()
		{
			Flush();
			Close();
		}
	public:
		constexpr InStream& operator=(const InStream& Source) = delete;

		constexpr InStream& operator=(InStream&& Right) noexcept = delete;
	public:
		inline void SetPosition(const Elysium::Core::Template::System::size Value)
		{
			_Sink.SetPosition(Value);
		}
	public:
		inline void Close()
		{
			if constexpr (requires { _Sink.Close(); })
			{
				_Sink.Close();
			}
		}
	public:
		inline void Write(const Elysium::Core::Template::System::byte* Buffer, const Elysium::Core::Template::System::size Count)
		{
			_Sink.Write(Buffer, Count);
		}

		inline void Flush()
		{
			if constexpr (requires { _Sink.Flush(); })
			{
				_Sink.Flush();
			}
		}
	private:
		Sink& _Sink;
	};
}
#endif
