/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_HUFFMANCODING_HUFFMANTABLEENTRY
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_HUFFMANCODING_HUFFMANTABLEENTRY

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
	class HuffmanTableEntry
	{
	public:
		/// <summary>
		/// Even with a legit value of 255, the huffman-tree is insanely deep, defeating the purpose of huffman-coding.
		/// </summary>
		using LengthType = Elysium::Core::Template::System::uint8_t;
	public:
		constexpr HuffmanTableEntry() = default;

		constexpr HuffmanTableEntry(const HuffmanTableEntry& Source) = default;

		constexpr HuffmanTableEntry(HuffmanTableEntry&& Right) noexcept = default;

		constexpr ~HuffmanTableEntry() = default;
	public:
		constexpr HuffmanTableEntry<S>& operator=(const HuffmanTableEntry& Source) = default;

		constexpr HuffmanTableEntry<S>& operator=(HuffmanTableEntry&& Right) noexcept = default;
	public:
		inline const bool GetIsLeaf()
		{
			return nullptr == _Subtable;
		}

		inline const bool GetIsValid()
		{
			return _Length > 0 && (0 <= _Symbol && 19 > _Symbol);
		}
	public:
		S _Symbol;
		LengthType _Length;

		HuffmanTableEntry* _Subtable;
		LengthType _SubTableLength;
	};
}
#endif