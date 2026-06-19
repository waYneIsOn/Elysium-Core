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
		constexpr HuffmanTableEntry() = default;

		constexpr HuffmanTableEntry(const HuffmanTableEntry& Source) = delete;

		constexpr HuffmanTableEntry(HuffmanTableEntry&& Right) noexcept = delete;

		constexpr ~HuffmanTableEntry() = default;
	public:
		constexpr HuffmanTableEntry<S>& operator=(const HuffmanTableEntry& Source) = delete;

		constexpr HuffmanTableEntry<S>& operator=(HuffmanTableEntry&& Right) noexcept = delete;
	private:
		S _Symbol{};
		Elysium::Core::Template::System::uint8_t _Length{};
		//bool _IsLeaf;	// not necessary, can just check "nullptr == _Subtable"

		HuffmanTableEntry* _Subtable{};
		Elysium::Core::Template::System::uint8_t _SubTableLength{};
	};
}
#endif