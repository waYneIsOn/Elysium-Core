/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANSYMBOLCODELENGTHPAIR
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANSYMBOLCODELENGTHPAIR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_HUFFMANCODEABLE
#include "../../../Concepts/HuffmanCodeable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::HuffmanCoding
{
	template<Elysium::Core::Template::Concepts::HuffmanCodeable S>
	class HuffmanSymbolCodeLengthPair
	{
	public:
		constexpr HuffmanSymbolCodeLengthPair() = default;

		inline constexpr HuffmanSymbolCodeLengthPair(const S& Symbol, const Elysium::Core::Template::System::uint8_t CodeLength)
			: _Symbol(Symbol), _CodeLength(CodeLength)
		{ }

		constexpr HuffmanSymbolCodeLengthPair(const HuffmanSymbolCodeLengthPair& Source) = delete;

		constexpr HuffmanSymbolCodeLengthPair(HuffmanSymbolCodeLengthPair&& Right) noexcept = default;

		constexpr ~HuffmanSymbolCodeLengthPair() = default;
	public:
		constexpr HuffmanSymbolCodeLengthPair& operator=(const HuffmanSymbolCodeLengthPair& Source) = delete;

		constexpr HuffmanSymbolCodeLengthPair& operator=(HuffmanSymbolCodeLengthPair&& Right) noexcept = default;
	public:
		inline bool operator<(const HuffmanSymbolCodeLengthPair& Other) const
		{
			if (_CodeLength == Other._CodeLength)
			{
				return _Symbol > Other._Symbol;
			}

			return _CodeLength > Other._CodeLength;
		}
	public:
		S _Symbol{};
		Elysium::Core::Template::System::uint8_t _CodeLength{};
	};
}
#endif
