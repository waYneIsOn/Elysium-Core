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
	class HuffmanTreeBase
	{
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
	public:
		constexpr HuffmanTree() = default;
	private:
		inline constexpr HuffmanTree(const Elysium::Core::Template::System::size NumberOfLeafNodes, Node* Root)
			: _NumberOfLeafNodes(NumberOfLeafNodes), _Root(Root)
		{ }
	public:
		inline constexpr virtual ~HuffmanTree()
		{
			if (nullptr != _Root)
			{
				delete _Root;
				_Root = nullptr;
			}
		}
	private:
		struct NodeComparison
		{
			bool operator()(Node* Left, Node* Right)
			{
				if (Left->_Frequency == Right->_Frequency)
				{
					return Left->_Symbol > Right->_Symbol;
				}
				
				return Left->_Frequency > Right->_Frequency;
			}
		};
	public:
		inline static const HuffmanTree Build(ConstSymbolPointer Input, const Elysium::Core::Template::System::size Length,
			bool SwapLeftAndRight = false)
		{
			// 1.) Simply count occurrences/frequency for each symbol
			constexpr const Frequency OccurrencesLength = 256;
			Frequency Occurrences[OccurrencesLength] = { 0 };
			for (Elysium::Core::Template::System::size i = 0; i < Length; i++)
			{
				++Occurrences[Input[i]];
			}

			// 2.) Create leaf nodes and then build the tree
			Elysium::Core::Template::System::uint8_t NumberOfLeafNodes = 0;
			Elysium::Core::Template::Container::PriorityQueue<Node*, Container::Vector<Node*>, NodeComparison> Heap{};
			for (Frequency i = 0; i < OccurrencesLength; ++i)
			{
				if (Occurrences[i] > 0)
				{
					++NumberOfLeafNodes;
					Heap.Push(new Node(i, Occurrences[i]));
				}
			}
			
			while (Heap.GetLength() > 1)
			{
				Node* Left = Heap.GetTop();
				Heap.Pop();

				Node* Right = Heap.GetTop();
				Heap.Pop();

				if (SwapLeftAndRight)
				{
					Heap.Push(new Node(Right, Left));
				}
				else
				{
					Heap.Push(new Node(Left, Right));
				}
			}

			Node* Root = Heap.GetTop();
			Heap.Pop();

			return HuffmanTree(NumberOfLeafNodes, Root);
		}
	public:
		inline CodeLengthsMap DeriveCodeLengths()
		{
			CodeLengthsMap Result = CodeLengthsMap(_NumberOfLeafNodes);

			GenerateCodeLengthsRecursively(_Root, 0, Result);

			return Result;
		}
		
		inline SymbolCodeMap GenerateNonCanonicalCodes()
		{
			SymbolCodeMap Result = SymbolCodeMap(_NumberOfLeafNodes);

			GenerateNonCanonicalCodesRecursively(_Root, "", Result);

			return Result;
		}
		
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
	private:
		inline static void GenerateCodeLengthsRecursively(const Node* Current, const Elysium::Core::Template::System::uint8_t Depth,
			CodeLengthsMap& CodeLengths)
		{
			if (nullptr == Current) ELYSIUM_CORE_PATH_UNLIKELY
			{
				return;
			}

			// we're only looking for leaf-nodes here obviously
			if (nullptr == Current->_Left && nullptr == Current->_Right)
			{
				CodeLengths.Set(Current->_Symbol, Depth);
				return;
			}

			GenerateCodeLengthsRecursively(Current->_Left, Depth + 1, CodeLengths);
			GenerateCodeLengthsRecursively(Current->_Right, Depth + 1, CodeLengths);
		}
		
		inline static void GenerateNonCanonicalCodesRecursively(const Node* Current, const Elysium::Core::Template::Text::String<char>& CurrentCode,
			SymbolCodeMap& Codes)
		{
			if (nullptr == Current) ELYSIUM_CORE_PATH_UNLIKELY
			{
				return;
			}

			// we're only looking for leaf-nodes here obviously
			if (nullptr == Current->_Left && nullptr == Current->_Right)
			{
				Codes.Set(Current->_Symbol, CurrentCode);
				return;
			}

			const Elysium::Core::Template::System::size CurrentCodeLength = CurrentCode.GetLength();

			Elysium::Core::Template::Text::String<char> LeftCode =
				Elysium::Core::Template::Text::String<char>(CurrentCodeLength + sizeof(char));
			for (Elysium::Core::Template::System::size i = 0; i < CurrentCodeLength; ++i)
			{
				LeftCode[i] = CurrentCode[i];
			}
			LeftCode[CurrentCodeLength] = u8'0';
			GenerateNonCanonicalCodesRecursively(Current->_Left, LeftCode, Codes);

			Elysium::Core::Template::Text::String<char> RightCode =
				Elysium::Core::Template::Text::String<char>(CurrentCodeLength + sizeof(char));
			for (Elysium::Core::Template::System::size i = 0; i < CurrentCodeLength; ++i)
			{
				RightCode[i] = CurrentCode[i];
			}
			RightCode[CurrentCodeLength] = u8'1';
			GenerateNonCanonicalCodesRecursively(Current->_Right, RightCode, Codes);
		}
	//private:
	public:
		Elysium::Core::Template::System::uint8_t _NumberOfLeafNodes;	// used to precalculate size of CodeLengthsMap
		Node* _Root;
	};
}
#endif
