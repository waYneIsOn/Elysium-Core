/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANSYMBOLTRAITS
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANSYMBOLTRAITS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_HUFFMANCODEABLE
#include "../../../Concepts/HuffmanCodeable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_NUMERICTRAITS
#include "../Numeric/NumericTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::HuffmanCoding
{
	template<Elysium::Core::Template::Concepts::HuffmanCodeable S>
	struct HuffmanSymbolTraits
	{
		struct FallbackHuffmanSymbol
		{
			S _Value;
			bool _IsEOB;
		};

		using Symbol = FallbackHuffmanSymbol;
	};

	template<>
	struct HuffmanSymbolTraits<Elysium::Core::Template::System::byte>
	{
		using Symbol = Elysium::Core::Template::System::uint16_t;
		inline static constexpr Symbol EOBSymbol = Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::Template::System::byte>::Maximum + 1;
	};

	template<>
	struct HuffmanSymbolTraits<Elysium::Core::Template::System::uint16_t>
	{
		using Symbol = Elysium::Core::Template::System::uint32_t;
		inline static constexpr Symbol EOBSymbol = Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::Template::System::uint16_t>::Maximum + 1;
	};

	template<>
	struct HuffmanSymbolTraits<Elysium::Core::Template::System::uint32_t>
	{
		using Symbol = Elysium::Core::Template::System::uint64_t;
		inline static constexpr Symbol EOBSymbol = Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::Template::System::uint32_t>::Maximum + 1;
	};
	/*
	template<>
	struct HuffmanSymbolTraits<Elysium::Core::Template::System::uint64_t>
	{
		//using Symbol = Elysium::Core::Template::System::uint64_t;
		//inline static constexpr Symbol EOBSymbol = Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::Template::System::uint128_t>::Maximum + 1;
	};
	*/
}
#endif
