/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_HUFFMANCODING_HUFFMANTABLE
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_HUFFMANCODING_HUFFMANTABLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_HUFFMANCODEABLE
#include "../../../../Concepts/HuffmanCodeable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_HUFFMANCODING_HUFFMANTABLEENTRY
#include "HuffmanTableEntry.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_SCOPED_ARENA
#include "../../../../Memory/Scoped/Arena.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::Format::HuffmanCoding
{
	template <Elysium::Core::Template::Concepts::HuffmanCodeable S, Elysium::Core::Template::System::size FastTableBits, Elysium::Core::Template::System::size ArenaPageLength>
	class HuffmanTable
	{
	public:
		inline constexpr HuffmanTable()
			: _Entries{}, _SubtableArena(Elysium::Core::Template::Memory::Scoped::ArenaOptions(sizeof(HuffmanTableEntry<S>)* ArenaPageLength, 1))
		{ }

		constexpr HuffmanTable(const HuffmanTable& Source) = delete;

		constexpr HuffmanTable(HuffmanTable&& Right) noexcept = delete;

		constexpr ~HuffmanTable() = default;
	public:
		constexpr HuffmanTable<S, FastTableBits, ArenaPageLength>& operator=(const HuffmanTable& Source) = delete;

		constexpr HuffmanTable<S, FastTableBits, ArenaPageLength>& operator=(HuffmanTable&& Right) noexcept = delete;
	public:
		inline static constexpr Elysium::Core::Template::System::size RootTableLength = 1 << FastTableBits;
	public:
		HuffmanTableEntry<S> _Entries[RootTableLength];
		Elysium::Core::Template::Memory::Scoped::Arena _SubtableArena;
	};
}
#endif