/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_DEFLATE_DEFLATECOMPRESSOR
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_DEFLATE_DEFLATECOMPRESSOR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_DEFLATE_DEFLATEUTILITY
#include "DeflateUtility.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::HuffmanCoding
{
	class DeflateCompressor
	{
	private:
		using SymbolType = DeflateUtility::SymbolType;
	public:
		constexpr DeflateCompressor() = delete;

		constexpr DeflateCompressor(const DeflateCompressor& Source) = delete;

		constexpr DeflateCompressor(DeflateCompressor&& Right) noexcept = delete;

		constexpr ~DeflateCompressor() = delete;
	public:
		constexpr DeflateCompressor& operator=(const DeflateCompressor& Source) = delete;

		constexpr DeflateCompressor& operator=(DeflateCompressor&& Right) noexcept = delete;
	};
}
#endif
