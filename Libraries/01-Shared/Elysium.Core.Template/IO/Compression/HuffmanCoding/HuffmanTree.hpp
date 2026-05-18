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
	class HuffmanTreeBase
	{
		friend class HuffmanEncoder<S, F>;
		friend class HuffmanDecoder<S, F>;
	public:
		using Node = HuffmanNode<S, F>;

		using Symbol = S;
		using ConstSymbolPointer = const S*;

		using Frequency = F;

		using CodeLengthsMap = Elysium::Core::Template::Container::UnorderedMap<S, F>;

		using SymbolCodeMap = Elysium::Core::Template::Container::UnorderedMap<S, Elysium::Core::Template::Text::String<char>>;
	protected:
		constexpr HuffmanTreeBase() = default;
	public:
		constexpr HuffmanTreeBase(const HuffmanTreeBase& Source) = delete;

		constexpr HuffmanTreeBase(HuffmanTreeBase&& Right) noexcept = delete;

		constexpr virtual ~HuffmanTreeBase() = default;
	public:
		constexpr HuffmanTreeBase& operator=(const HuffmanTreeBase& Source) = delete;

		constexpr HuffmanTreeBase& operator=(HuffmanTreeBase&& Right) noexcept = delete;
	public:
		struct SymbolCodeLengthPair
		{
			S Symbol;
			Elysium::Core::Template::System::uint8_t CodeLength;

			friend bool operator<(const SymbolCodeLengthPair& Left, const SymbolCodeLengthPair& Right)
			{
				if (Left.CodeLength == Right.CodeLength)
				{
					return Left.Symbol > Right.Symbol;
				}

				return Left.CodeLength > Right.CodeLength;
			}
		};

		struct SymbolCodePair
		{
			S Symbol;
			Elysium::Core::Template::Text::String<char> LeBlangth;
		};
	};

	/// <summary>
	/// Specialization used for when compression is based on bytes allowing for using an array.
	/// </summary>
	template<>
	class HuffmanTree<Elysium::Core::Template::System::byte, Elysium::Core::Template::System::size>
		: public HuffmanTreeBase<Elysium::Core::Template::System::byte, Elysium::Core::Template::System::size>
	{
		friend class HuffmanEncoder<Elysium::Core::Template::System::byte, Elysium::Core::Template::System::size>;
		friend class HuffmanDecoder<Elysium::Core::Template::System::byte, Elysium::Core::Template::System::size>;
	public:
		constexpr HuffmanTree() = default;
	private:
		inline constexpr HuffmanTree(const Elysium::Core::Template::System::size NumberOfLeafNodes, Node* Root)
			: _NumberOfLeafNodes(NumberOfLeafNodes), _Root(Root)
		{ }
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




	public:
		inline SymbolCodeMap GenerateCanonicalCodes(const Elysium::Core::Template::Container::Vector<SymbolCodeLengthPair>& SymbolCodeLengths)
		{
			SymbolCodeMap Result = SymbolCodeMap();
			Elysium::Core::Template::System::size CurrentCode = 0;
			Elysium::Core::Template::System::size PreviousLength = 0;
			for (Elysium::Core::Template::System::size i = 0; i < SymbolCodeLengths.GetLength(); ++i)
			{
				const char Symbol = SymbolCodeLengths[i].Symbol;

				CurrentCode <<= (SymbolCodeLengths[i].CodeLength - PreviousLength);
				PreviousLength = SymbolCodeLengths[i].CodeLength;

				Elysium::Core::Template::System::size Temp = CurrentCode;

				Elysium::Core::Template::Text::String<char> CodeResult = Elysium::Core::Template::Text::String<char>('0', SymbolCodeLengths[i].CodeLength);
				for (int l = SymbolCodeLengths[i].CodeLength - 1; l >= 0; --l)	// highest bit first
				//for(int l = 0; l < SymbolCodeLengths[i].CodeLength; ++l)	// lowest bit first
				{
					CodeResult[l] = (Temp & 1) ? '1' : '0';
					Temp >>= 1;
				}

				Result.Set(SymbolCodeLengths[i].Symbol, CodeResult);

				CurrentCode++;
			}

			return Result;
		}
	//private:
	public:
		Elysium::Core::Template::System::uint8_t _NumberOfLeafNodes;	// used to precalculate size of CodeLengthsMap
		Node* _Root;
	};
}
#endif
