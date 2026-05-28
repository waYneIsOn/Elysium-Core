/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_DEFLATE_DEFLATEUTILITY
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_DEFLATE_DEFLATEUTILITY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::HuffmanCoding
{
	class DeflateUtility
	{
		friend class DeflateCompressor;
		friend class DeflateDecompressor;
	private:
		using SymbolType = Elysium::Core::Template::System::uint16_t;
	public:
		constexpr DeflateUtility() = delete;

		constexpr DeflateUtility(const DeflateUtility& Source) = delete;

		constexpr DeflateUtility(DeflateUtility&& Right) noexcept = delete;

		constexpr ~DeflateUtility() = delete;
	public:
		constexpr DeflateUtility& operator=(const DeflateUtility& Source) = delete;

		constexpr DeflateUtility& operator=(DeflateUtility&& Right) noexcept = delete;
	private:
		inline static constexpr SymbolType LiteralAlphabetSize = 288;	// literals [0-255], EOB [256] and length-codes [257-285] (two are actually unused but used for padding/alignment!)
		inline static constexpr SymbolType DistanceAlphabetSize = 32;	// 32 distances, fixed 5 bits, additional bits (two are actually unused but used for padding/alignment!)

		inline static constexpr SymbolType InvalidSymbol = 0xFFFF;
	};
}
#endif
