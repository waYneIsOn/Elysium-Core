/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANTREE
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANTREE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_HUFFMANCODEABLE
#include "../../../Concepts/HuffmanCodeable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANNODE
#include "HuffmanNode.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_UNSIGNEDINTEGER
#include "../../../UnsignedInteger.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_QUEUE_PRIORITYQUEUE
#include "../../../Container/PriorityQueue.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_UNORDEREDMAP
#include "../../../Container/UnorderedMap.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_NUMERICTRAITS
#include "../../../Numeric/NumericTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_COMPILER
#include "../../../System/Compiler.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "../../../Text/String.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::HuffmanCoding
{
	template<Elysium::Core::Template::Concepts::HuffmanCodeable S, Elysium::Core::Template::Concepts::UnsignedInteger F>
	class HuffmanEncoder;

	template<Elysium::Core::Template::Concepts::HuffmanCodeable S, Elysium::Core::Template::Concepts::UnsignedInteger F>
	class HuffmanDecoder;
	
	template<Elysium::Core::Template::Concepts::HuffmanCodeable S, Elysium::Core::Template::Concepts::UnsignedInteger F>
	class HuffmanTree
	{
		friend class HuffmanEncoder<Elysium::Core::Template::System::byte, Elysium::Core::Template::System::size>;
		friend class HuffmanDecoder<Elysium::Core::Template::System::byte, Elysium::Core::Template::System::size>;
	public:
		using Node = HuffmanNode<S, F>;

		using Symbol = S;
		using ConstSymbolPointer = const S*;

		using Frequency = F;

		using CodeLengthsMap = Elysium::Core::Template::Container::UnorderedMap<S, F>;

		using SymbolCodeMap = Elysium::Core::Template::Container::UnorderedMap<S, Elysium::Core::Template::Text::String<char>>;
	public:
		constexpr HuffmanTree() = default;
	public:
		inline constexpr virtual ~HuffmanTree()
		{
			Clear();
		}
	public:
		inline constexpr void Clear()
		{
			if (nullptr != _Root)
			{
				delete _Root;
				_Root = nullptr;
			}
		}
	private:
		Node* _Root;
	};
}
#endif
