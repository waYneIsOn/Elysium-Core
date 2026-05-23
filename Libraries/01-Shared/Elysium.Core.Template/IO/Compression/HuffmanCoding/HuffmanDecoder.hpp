/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANDECODER
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANDECODER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_HUFFMANCODEABLE
#include "../../../Concepts/HuffmanCodeable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_UNSIGNEDINTEGER
#include "../../../Concepts/UnsignedInteger.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_QUEUE_VECTOR
#include "../../../Container/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANCODE
#include "HuffmanCode.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANNODE
#include "HuffmanNode.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANTREE
#include "HuffmanTree.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANUTILITY
#include "HuffmanUtility.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_MAX
#include "../../../Math/Max.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::HuffmanCoding
{
	template<Elysium::Core::Template::Concepts::HuffmanCodeable S, Elysium::Core::Template::Concepts::UnsignedInteger F>
	class HuffmanDecoder
	{
	public:
		using SymbolCodeMap = HuffmanUtility<S>::SymbolCodeMap;
	private:
		using SymbolCodeMapFIterator = SymbolCodeMap::FIterator;

		using PackedCodeSymbolMap = Elysium::Core::Template::Container::UnorderedMap<Elysium::Core::Template::System::uint64_t, S>;
	public:
		constexpr HuffmanDecoder() = default;

		constexpr HuffmanDecoder(const HuffmanDecoder& Source) = delete;

		constexpr HuffmanDecoder(HuffmanDecoder&& Right) noexcept = delete;

		constexpr ~HuffmanDecoder() = default;
	public:
		constexpr HuffmanDecoder& operator=(const HuffmanDecoder& Source) = delete;

		constexpr HuffmanDecoder& operator=(HuffmanDecoder&& Right) noexcept = delete;
	public:
		inline const Elysium::Core::Template::Container::Vector<S> Decompress(const Elysium::Core::Template::System::byte* CompressedData, const Elysium::Core::Template::System::size Length,
			const Elysium::Core::Template::System::size UncompressedLength, SymbolCodeMap& SymbolCodes, const Elysium::Core::Template::System::uint8_t LookupTableSize = 15)
		{
			// @Note: most algorithms either store "UncompressedLength" or some other way of "termination logic" (like EOB - end of block) in the header.
			// For now I will implement the approach of having access to the uncompressed length, I will need to implement other methods as well though!
			Elysium::Core::Template::Container::Vector<S> Result = Elysium::Core::Template::Container::Vector<S>(UncompressedLength + sizeof(S));
			Result.Clear();

			// @ToDo: the following code certainly can be optimized by using "actual" lookup tables

			// prepare "lookup table"
			PackedCodeSymbolMap PackedCodeSymbols = PackedCodeSymbolMap();
			Elysium::Core::Template::System::uint8_t MaxCodeLength = 0;
			for (SymbolCodeMapFIterator Iterator = SymbolCodes.GetBegin(); Iterator != SymbolCodes.GetEnd(); ++Iterator)
			{
				const Elysium::Core::Template::Container::LinkedListNode<Elysium::Core::Template::Container::KeyValuePair<S, HuffmanCode>>* Node = *Iterator;
				const Elysium::Core::Template::Container::KeyValuePair<S, HuffmanCode>& Item = Node->GetItem();
				
				const S& CurrentSymbol = Item.GetKey();
				const HuffmanCode& CurrentCode = Item.GetValue();

				MaxCodeLength = Elysium::Core::Template::Math::Max(MaxCodeLength, CurrentCode._Length);

				const Elysium::Core::Template::System::uint64_t PackedKey = HuffmanUtility<S>::GetPackedKey(CurrentCode._Bits, CurrentCode._Length);

				PackedCodeSymbols.Set(PackedKey, CurrentSymbol);
			}

			// ...
			Elysium::Core::Template::System::size InputPosition = 0;

			Elysium::Core::Template::System::uint64_t Buffer = 0;
			Elysium::Core::Template::System::uint8_t BitCount = 0;

			for (Elysium::Core::Template::System::size i = 0; i < UncompressedLength; ++i)
			{
				// Once there are 56 bits in an uint64_t another shift by eight bits is still possible. Afterwards it would result in an overflow.
				// Obviously if there is no more data available, stopping the buffer-population is logical as well.
				while (BitCount <= 56 && InputPosition < Length)
				{
					Buffer = (Buffer << 8) | CompressedData[InputPosition++];
					BitCount += 8;
				}

				bool Found = false;

				// @ToDo: this incrementally looks for the PackedKey to retrieve a symbol on a bit-by-bit basis -> horseshit -> improve!!!
				for (Elysium::Core::Template::System::uint8_t TryCodeLength = 1; TryCodeLength <= MaxCodeLength; ++TryCodeLength)
				{
					Elysium::Core::Template::System::uint32_t CurrentCode = (Buffer >> (BitCount - TryCodeLength)) & ((1_ui32 << TryCodeLength) - 1);
					const Elysium::Core::Template::System::uint64_t PackedKey = HuffmanUtility<S>::GetPackedKey(CurrentCode, TryCodeLength);

					try
					{
						const S& CurrentSymbol = PackedCodeSymbols[PackedKey];

						BitCount -= TryCodeLength;
						Found = true;
						Result.PushBack(CurrentSymbol);
						break;
					}
					catch(...)
					{ }
				}

				if (!Found)
				{	// @ToDo: throw a specific exception
					throw 1;
				}
			}

			return Result;
		}

		inline const Elysium::Core::Template::Container::Vector<S> Decompress(const Elysium::Core::Template::System::byte* CompressedData, const Elysium::Core::Template::System::size Length,
			const Elysium::Core::Template::System::size UncompressedLength, const Elysium::Core::Template::Container::Vector<HuffmanSymbolCodeLengthPair<S>>& SymbolCodeLengths,
			const Elysium::Core::Template::System::uint8_t LookupTableSize = 15)
		{
			SymbolCodeMap SymbolCodes = HuffmanUtility<S>::CreateFromSymbolCodeLengths(SymbolCodeLengths);

			return Decompress(CompressedData, Length, UncompressedLength, SymbolCodes, LookupTableSize);
		}
	};
}
#endif
