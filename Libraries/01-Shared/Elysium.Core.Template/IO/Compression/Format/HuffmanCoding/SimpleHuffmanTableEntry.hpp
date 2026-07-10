/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_HUFFMANCODING_SIMPLEHUFFMANTABLEENTRY
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_HUFFMANCODING_SIMPLEHUFFMANTABLEENTRY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_HUFFMANCODEABLE
#include "../../../../Concepts/HuffmanCodeable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::Format::HuffmanCoding
{
	template <Elysium::Core::Template::Concepts::HuffmanCodeable S>
	class SimpleHuffmanTableEntry
	{
	public:
		using LengthType = Elysium::Core::Template::System::uint8_t;
	public:
		constexpr SimpleHuffmanTableEntry() = default;

		inline constexpr SimpleHuffmanTableEntry(S Symbol, LengthType Length)
			: _Symbol(Symbol), _Length(Length)
		{}

		constexpr SimpleHuffmanTableEntry(const SimpleHuffmanTableEntry& Source) = default;

		constexpr SimpleHuffmanTableEntry(SimpleHuffmanTableEntry&& Right) noexcept = default;

		constexpr ~SimpleHuffmanTableEntry() = default;
	public:
		constexpr SimpleHuffmanTableEntry<S>& operator=(const SimpleHuffmanTableEntry& Source) = default;

		constexpr SimpleHuffmanTableEntry<S>& operator=(SimpleHuffmanTableEntry&& Right) noexcept = default;
	public:
		inline constexpr bool operator==(const SimpleHuffmanTableEntry& Other) const noexcept
		{
			return _Symbol == Other._Symbol && _Length == Other._Length;
		}

		inline constexpr bool operator!=(const SimpleHuffmanTableEntry& Other) const noexcept
		{
			return _Symbol != Other._Symbol || _Length != Other._Length;
		}
	public:
		inline constexpr bool GetIsValid()
		{
			return _Length > 0;
		}
	public:
		S _Symbol;
		LengthType _Length;
	};
}
#endif