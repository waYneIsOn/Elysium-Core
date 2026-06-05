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

		virtual ~OutStream() = default;
	public:
		constexpr OutStream& operator=(const OutStream& Source) = delete;

		constexpr OutStream& operator=(OutStream&& Right) noexcept = delete;
	public:

	private:
		Sink& _Sink;
	};
}
#endif
