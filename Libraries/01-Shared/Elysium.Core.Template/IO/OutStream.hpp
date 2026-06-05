/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_OUTSTREAM
#define ELYSIUM_CORE_TEMPLATE_IO_OUTSTREAM

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::IO
{
	// @ToDo: concept for sinks!
	template<class Sink>
	class OutStream
	{
	public:
		constexpr OutStream() noexcept = default;

		inline constexpr OutStream(Sink& Sink) noexcept
			: _Sink(Sink)
		{ }

		constexpr OutStream(const OutStream& Source) = delete;

		constexpr OutStream(OutStream&& Right) noexcept = delete;

		inline ~OutStream()
		{
			Flush();
			Close();
		}
	public:
		constexpr OutStream& operator=(const OutStream& Source) = delete;

		constexpr OutStream& operator=(OutStream&& Right) noexcept = delete;
	public:
		inline void Close()
		{
			if constexpr (requires { _Sink.Close(); })
			{
				_Sink.Close();
			}
		}
	public:
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
