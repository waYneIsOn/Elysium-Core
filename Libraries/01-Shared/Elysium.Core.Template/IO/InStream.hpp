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
	// @ToDo: concept for sources!
	template<class Source>
	class InStream
	{
	public:
		constexpr InStream() noexcept = delete;

		inline constexpr InStream(Source& Source) noexcept
			: _Sink(_Source)
		{ }

		constexpr InStream(const InStream& Source) = delete;

		constexpr InStream(InStream&& Right) noexcept = delete;

		virtual ~InStream() = default;
	public:
		constexpr InStream& operator=(const InStream& Source) = delete;

		constexpr InStream& operator=(InStream&& Right) noexcept = delete;
	public:

	private:
		Source& _Source;
	};
}
#endif
