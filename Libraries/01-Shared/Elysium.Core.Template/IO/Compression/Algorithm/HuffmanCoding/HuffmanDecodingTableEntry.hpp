/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_ALGORITHM_HUFFMANCODING_HUFFMANDECODINGTABLEENTRY
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_ALGORITHM_HUFFMANCODING_HUFFMANDECODINGTABLEENTRY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_HUFFMANCODEABLE
#include "../../../../Concepts/HuffmanCodeable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::Algorithm::HuffmanCoding
{
	template <Elysium::Core::Template::Concepts::HuffmanCodeable S>
	struct HuffmanDecodingTableEntry
	{
	public:
		inline constexpr bool operator==(const HuffmanDecodingTableEntry<S>& Other) const noexcept
		{
			return _Operation == Other._Operation && _Length == Other._Length && _Value == Other._Value;
		}

		inline constexpr bool operator!=(const HuffmanDecodingTableEntry<S>& Other) const noexcept
		{
			return _Operation != Other._Operation || _Length != Other._Length || _Value != Other._Value;
		}
	public:
		inline constexpr S GetSymbol() const
		{
			if (0 != _Operation)
			{	// @ToDo
				throw 1;
			}

			return _Value;
		}
	public:
		Elysium::Core::Template::System::uint8_t _Operation;
		Elysium::Core::Template::System::uint8_t _Length;
		S _Value;
	};
}
#endif
