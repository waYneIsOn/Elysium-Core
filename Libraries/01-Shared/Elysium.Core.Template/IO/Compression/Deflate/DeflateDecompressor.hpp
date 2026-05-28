/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_DEFLATE_DEFLATEDECOMPRESSOR
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_DEFLATE_DEFLATEDECOMPRESSOR

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
	class DeflateDecompressor
	{
	private:
		using SymbolType = DeflateUtility::SymbolType;
	public:
		constexpr DeflateDecompressor() = delete;

		constexpr DeflateDecompressor(const DeflateDecompressor& Source) = delete;

		constexpr DeflateDecompressor(DeflateDecompressor&& Right) noexcept = delete;

		constexpr ~DeflateDecompressor() = delete;
	public:
		constexpr DeflateDecompressor& operator=(const DeflateDecompressor& Source) = delete;

		constexpr DeflateDecompressor& operator=(DeflateDecompressor&& Right) noexcept = delete;
	};
}
#endif
