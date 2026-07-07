/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_ALGORITHM_DEFLATE_DEFLATEENCODER
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_ALGORITHM_DEFLATE_DEFLATEENCODER

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::IO::Compression::Algorithm::Deflate
{
	class DeflateEncoder final
	{
	public:
		inline constexpr DeflateEncoder() noexcept = default;

		constexpr DeflateEncoder(const DeflateEncoder& Source) = delete;

		constexpr DeflateEncoder(DeflateEncoder&& Right) noexcept = delete;

		inline ~DeflateEncoder() = default;
	public:
		constexpr DeflateEncoder& operator=(const DeflateEncoder& Source) = delete;

		constexpr DeflateEncoder& operator=(DeflateEncoder&& Right) noexcept = delete;
	public:

	private:

	};
}
#endif