/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_ALGORITHM_DEFLATE_DEFLATEDECODER
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_ALGORITHM_DEFLATE_DEFLATEDECODER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_SLIDINGWINDOW
#include "../../../../Container/SlidingWindow.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_BITREADER
#include "../../../BitReader.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_DEFLATE_DEFLATEBLOCKHEADER
#include "../../Format/Deflate/DeflateBlockHeader.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_DEFLATE_DEFLATEBLOCKTYPE
#include "../../Format/Deflate/DeflateBlockType.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_DEFLATE_DEFLATESTATE
#include "../../Format/Deflate/DeflateState.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_HUFFMANCODING_CODELENGTHTABLE
#include "../../Format/HuffmanCoding/CodeLengthTable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_HUFFMANCODING_HUFFMANTABLE
#include "../../Format/HuffmanCoding/HuffmanTable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_MIN
#include "../../../../Math/Min.hpp
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_LITERALS
#include "../../../../System/Literals.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::Algorithm::Deflate
{
	class DeflateDecoder final
	{
	public:
		inline constexpr DeflateDecoder() noexcept
			: _State(Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::ReadingBlockHeader), _BlockHeader{}, _HistoryBuffer(32768), _BitReader{}
		{ }

		constexpr DeflateDecoder(const DeflateDecoder& Source) = delete;

		constexpr DeflateDecoder(DeflateDecoder&& Right) noexcept = delete;

		~DeflateDecoder() = default;
	public:
		constexpr DeflateDecoder & operator=(const DeflateDecoder & Source) = delete;

		constexpr DeflateDecoder& operator=(DeflateDecoder&& Right) noexcept = delete;
	public:
		inline constexpr const Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState GetState() const noexcept
		{
			return _State;
		}
	public:
		inline const Elysium::Core::Template::IO::ReadResult Decode(const Elysium::Core::Template::Container::View::MultiSpan<Elysium::Core::Template::System::byte, 1024, 2> SourceSpans,
			Elysium::Core::Template::Container::View::MultiSpan<Elysium::Core::Template::System::byte, 1024, 2>& TargetSpan, Elysium::Core::Template::System::size& BytesFullyProcessed)
		{
			while (true)
			{
				switch (_State)
				{
				case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::ReadingBlockHeader:
				{
					const Elysium::Core::Template::IO::ReadResult Result = ReadBlockHeader(SourceSpans, BytesFullyProcessed);
					if (Elysium::Core::Template::IO::ReadResult::Pending == Result)
					{
						return Result;
					}
				}
					break;
					/*
				case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::Uncompressed:
					break;
				case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::ReadingFixedHuffman:
					break;
					*/
				case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::ReadingDynamicHuffmanHeaderFields:
				{
					const Elysium::Core::Template::IO::ReadResult Result = ReadDynamicHuffmanHeaderFields(SourceSpans, BytesFullyProcessed);
					if (Elysium::Core::Template::IO::ReadResult::Pending == Result)
					{
						return Result;
					}
				}
					break;
				case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::BuildingCodeLengthTable:
				{
					const Elysium::Core::Template::IO::ReadResult Result = BuildCodeLengthTable(SourceSpans, BytesFullyProcessed);
					if (Elysium::Core::Template::IO::ReadResult::Pending == Result)
					{
						return Result;
					}
				}
					break;
				case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::BuildingLiteralAndDistanceTables:
				{
					const Elysium::Core::Template::IO::ReadResult Result = BuildLiteralAndDistanceTables(SourceSpans, BytesFullyProcessed);
					if (Elysium::Core::Template::IO::ReadResult::Pending == Result)
					{
						return Result;
					}
					
				}
					break;





				case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::Done:
				{

				}
					return Elysium::Core::Template::IO::ReadResult::EndOfStream;
				default:
					// @ToDo
					throw 1;
				}
			}

			return Elysium::Core::Template::IO::ReadResult::EndOfStream;
		}
	private:
		inline const Elysium::Core::Template::IO::ReadResult ReadBlockHeader(const Elysium::Core::Template::Container::View::MultiSpan<Elysium::Core::Template::System::byte, 1024, 2> SourceSpans,
			Elysium::Core::Template::System::size& BytesLoadedIntoBitReader)
		{
			static constexpr const Elysium::Core::Template::System::size HeaderSize = Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockHeader::Size;
			/*
			// This check is incorrect with deflate as it works on bit-data. _BitReader could hold data from before making this check incorrect!
			// EnsureAvailableBit(...) is what really needs to work correctly!
			if (SourceSpans.GetLength() < HeaderSize)
			{
				return Elysium::Core::Template::IO::ReadResult::Pending;
			}
			*/
			const Elysium::Core::Template::IO::ReadResult BufferPopulationResult = EnsureAvailableBit(3, SourceSpans, BytesLoadedIntoBitReader);
			if (Elysium::Core::Template::IO::ReadResult::Pending == BufferPopulationResult)
			{
				return BufferPopulationResult;
			}

			_BlockHeader._Data = static_cast<Elysium::Core::Template::System::byte>(_BitReader.Read(3));

			const Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockType BlockType = _BlockHeader.GetCompressionMethod();
			switch (BlockType)
			{
			case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockType::Uncompressed:
				break;
			case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockType::FixedHuffman:
				break;
			case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockType::DynamicHuffman:
				_State = Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::ReadingDynamicHuffmanHeaderFields;
				break;
			case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockType::Invalid:
				throw 1;
			default:
				throw 1;
			}

			return Elysium::Core::Template::IO::ReadResult::HasData;
		}

		inline const Elysium::Core::Template::IO::ReadResult ReadDynamicHuffmanHeaderFields(const Elysium::Core::Template::Container::View::MultiSpan<Elysium::Core::Template::System::byte, 1024, 2> SourceSpans,
			Elysium::Core::Template::System::size& BytesLoadedIntoBitReader)
		{
			// need 14 bit (HLIT = 5, HDIST = 5, HCLEN = 4), ergo 2 bytes
			static constexpr const Elysium::Core::Template::System::size BitsRequired = 14;
			static constexpr const Elysium::Core::Template::System::size BytesRequired = 2;

			const Elysium::Core::Template::IO::ReadResult BufferPopulationResult = EnsureAvailableBit(BitsRequired, SourceSpans, BytesLoadedIntoBitReader);
			if (Elysium::Core::Template::IO::ReadResult::Pending == BufferPopulationResult)
			{
				return BufferPopulationResult;
			}

			/*
			* RFC 1951 describes:
			* 5 Bits: HLIT, # of Literal/Length codes - 257 (257 - 286)
            * 5 Bits: HDIST, # of Distance codes - 1        (1 - 32)
            * 4 Bits: HCLEN, # of Code Length codes - 4     (4 - 19)
			*/
			_DynamicHuffmanHeader.HLIT = _BitReader.Peek(5) + 257;
			_DynamicHuffmanHeader.HDIST = _BitReader.Peek(5) + 1;
			_DynamicHuffmanHeader.HCLEN = _BitReader.Peek(4) + 4;

			if (_DynamicHuffmanHeader.HLIT < 257 || _DynamicHuffmanHeader.HLIT > 286)
			{	// @ToDo: this violate rfc 1951
				throw 1;
			}
			if (_DynamicHuffmanHeader.HDIST > 32)
			{	// @ToDo: this violate rfc 1951
				throw 1;
			}
			if (_DynamicHuffmanHeader.HCLEN < 4 || _DynamicHuffmanHeader.HCLEN > 19)
			{	// @ToDo: this violate rfc 1951
				throw 1;
			}

			_BitReader.Consume(5 + 5 + 4);

			_State = Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::BuildingCodeLengthTable;

			return Elysium::Core::Template::IO::ReadResult::HasData;
		}

		inline const Elysium::Core::Template::IO::ReadResult BuildCodeLengthTable(const Elysium::Core::Template::Container::View::MultiSpan<Elysium::Core::Template::System::byte, 1024, 2> SourceSpans,
			Elysium::Core::Template::System::size& BytesLoadedIntoBitReader)
		{
			// https://www.rfc-editor.org/info/rfc1951/#page-13
			// 3.2.7 Compression with dynamic Huffman codes (BTYPE=10)
			// (HCLEN + 4) x 3 bits: code lengths for the code length
			// 	alphabet given just above, in the order : 16, 17, 18,
			// 	0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15
			static constexpr const Elysium::Core::Template::System::uint8_t FixedPermutations[19] =
			{
				// repeat instructions
				16, 17, 18,

				// low-ish lengths
				0, 8, 7, 9, 6, 10, 5,

				// remaining lengths
				11, 4, 12, 3, 13, 2, 14, 1, 15
			};
			static constexpr const Elysium::Core::Template::System::size BitsRequiredPerEntry = 3;

			const Elysium::Core::Template::System::size AmountOfCodeLengths = _DynamicHuffmanHeader.HCLEN;
			const Elysium::Core::Template::System::size BitsRequiredInTotal = BitsRequiredPerEntry * AmountOfCodeLengths;
			if (BitsRequiredInTotal > BitReader<true>::Capacity)
			{	// @Todo: Code-length codes maximum is 19: 19 * 3 = 57 so an overflow should never happen!
				// if this error occurres, something in the implementation is entirely incorrect!
				throw 1;
			}

			const Elysium::Core::Template::IO::ReadResult BufferPopulationResult = EnsureAvailableBit(BitsRequiredInTotal, SourceSpans, BytesLoadedIntoBitReader);
			if (Elysium::Core::Template::IO::ReadResult::Pending == BufferPopulationResult)
			{	// @ToDo: this would be an actual error here!
				throw 1;
			}

			// 1.) Read code length alphabet
			constexpr Elysium::Core::Template::System::uint8_t FastTableBits = Elysium::Core::Template::IO::Compression::Format::HuffmanCoding::CodeLengthTable::FastTableBits;
			bool AllValuesAreZero = true;
			Elysium::Core::Template::System::uint8_t CodeLengths[19]{};
			for (int i = 0; i < AmountOfCodeLengths; ++i)
			{
				Elysium::Core::Template::System::uint64_t CurrentValue = _BitReader.Read(3);
			
				// 3 bits -> maximum 0b111 = 7 BUT BitReader returns a 64bit integer so if the implementation is not correct, this might still result in a bug!!!
				if (CurrentValue > FastTableBits)
				{	// @ToDo: this violate rfc 1951
					throw 1;
				}
				
				Elysium::Core::Template::System::uint8_t Symbol = FixedPermutations[i];
				CodeLengths[Symbol] = static_cast<Elysium::Core::Template::System::uint8_t>(CurrentValue);

				if (CurrentValue > 0)
				{
					AllValuesAreZero = false;
				}
			}

			if (AllValuesAreZero)
			{	// @ToDo:
				throw 1;
			}

			// 2.) Count bit-lengths
			// Code lengths are 3 bits in size, ergo have a range of 0 to 7 and therefore 8 different values.
			Elysium::Core::Template::System::uint8_t BitLengthCount[8] = { 0 };
			for (Elysium::Core::Template::System::uint8_t i = 0; i < 19; ++i)
			{
				if (CodeLengths[i] != 0)
				{
					BitLengthCount[CodeLengths[i]]++;
				}
			}

			Elysium::Core::Template::System::uint64_t KraftSum = 0;
			for (Elysium::Core::Template::System::uint8_t Length = 1; Length <= FastTableBits; ++Length)
			{
				KraftSum += BitLengthCount[Length] * (1 << (FastTableBits - Length));
			}

			if (KraftSum > Elysium::Core::Template::IO::Compression::Format::HuffmanCoding::CodeLengthTable::TableLength)
			{	// @ToDo: invalid kraft sum
				throw 1;
			}

			// 3.) Define canonical code ranges
			// Code range for each bit-length and therefore 8 as well.
			// Index 0 "unused"
			Elysium::Core::Template::System::uint16_t NextCode[8] = { 0 };
			Elysium::Core::Template::System::uint16_t Code = 0;
			for (Elysium::Core::Template::System::uint8_t Bits = 1; Bits <= 7; ++Bits)
			{
				Code = (Code + BitLengthCount[Bits - 1]) << 1;
				NextCode[Bits] = Code;
			}

			// 4.) Assign canonical Huffman codes to symbols using the precomputed NextCode ranges.
			//	(In my "old" HuffmanDecoder the sorting happens like so "Elysium::Core::Template::Algorithms::Sorting::BubbleSort(SymbolCodeLengths.GetBegin(), SymbolCodeLengths.GetEnd());"
			//  which basically is, what's being done here through the inner- and outer-loop.)
			// 19 responds to HCLEN having a max of 19 entries.
			Elysium::Core::Template::System::uint16_t Codes[19] = { 0 };
			for (Elysium::Core::Template::System::uint8_t Length = 1; Length <= 7; ++Length)
			{
				for (Elysium::Core::Template::System::uint8_t Symbol = 0; Symbol < 19; ++Symbol)
				{
					Elysium::Core::Template::System::uint8_t CodeLength = CodeLengths[Symbol];
					//if (CodeLength != 0)
					if(CodeLengths[Symbol] == Length)
					{
						Elysium::Core::Template::System::uint16_t MSBFirstCode = NextCode[Length]++;
						Elysium::Core::Template::System::uint16_t LSBFirstCode = ReverseBits(MSBFirstCode, Length);

						Codes[Symbol] = LSBFirstCode;
						//Codes[Symbol] = MSBFirstCode;	// step 5 needs MSB first in the implementation not fully populating code-lengths!
					}
				}
			}

			// 5.) build code-length huffman table
			/*
			// this version does not fully populate code-length table (depending on input)
			for (Elysium::Core::Template::System::uint8_t Symbol = 0; Symbol < 19; ++Symbol)
			{
				Elysium::Core::Template::System::uint8_t CodeLength = CodeLengths[Symbol];
				if (CodeLength == 0)
				{
					continue;
				}

				Elysium::Core::Template::System::uint16_t CurrentCode = Codes[Symbol];

				Elysium::Core::Template::System::uint16_t Fill = 1 << (FastTableBits - CodeLength);
				for (Elysium::Core::Template::System::uint16_t i = 0; i < Fill; ++i)
				{
					Elysium::Core::Template::System::uint16_t CurrentIndex = (CurrentCode << (FastTableBits - CodeLength)) | i;
					Elysium::Core::Template::IO::Compression::Format::HuffmanCoding::CodeLengthTableEntry& Entry = _DynamicHuffmanHeader._CodeLengthTable._Entries[CurrentIndex];

					if (Entry.GetIsValid())
					{	// @ToDo: if the entry is valid here, I am overwriting something!
						throw 1;
					}

					Entry = { Symbol, CodeLength };
				}
			}
			*/
			// this version fully populates code-length table - important in BuildLiteralAndDistanceTables(...) when always reading 7 bit!
			for (Elysium::Core::Template::System::uint8_t i = 0; i < Elysium::Core::Template::IO::Compression::Format::HuffmanCoding::CodeLengthTable::TableLength; ++i)
			{
				Elysium::Core::Template::System::uint8_t Bits = i;
				bool Found = false;

				// try all possible code lengths
				for (Elysium::Core::Template::System::uint8_t Length = 1; Length <= 7; ++Length)
				{
					Elysium::Core::Template::System::uint16_t Prefix = Bits >> (Elysium::Core::Template::IO::Compression::Format::HuffmanCoding::CodeLengthTable::FastTableBits - Length);

					for (Elysium::Core::Template::System::uint8_t Symbol = 0; Symbol < 19; ++Symbol)
					{
						if (CodeLengths[Symbol] != Length)
						{
							continue;
						}

						if (Codes[Symbol] == Prefix)
						{
							_DynamicHuffmanHeader._CodeLengthTable[i] = { Symbol, Length };
							Found = true;
							break;
						}
					}

					if (Found)
					{
						break;
					}
				}
				
				if (!Found)
				{
					_DynamicHuffmanHeader._CodeLengthTable[i] = { 0, 0 };
				}
			}
			/*
			// code-length huffman table actually can have "unused" entries - those aren't really invalid so the following check would be incorrect:
			for (Elysium::Core::Template::System::uint8_t i = 0; i < Elysium::Core::Template::IO::Compression::Format::HuffmanCoding::CodeLengthTable::TableSize; ++i)
			{
				if (!_DynamicHuffmanHeader._CodeLengthTable._Entries[i].GetIsValid())
				{	// @ToDo:
					throw 1;
				}
			}
			*/
			_State = Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::BuildingLiteralAndDistanceTables;

			return Elysium::Core::Template::IO::ReadResult::HasData;
		}

		inline const Elysium::Core::Template::IO::ReadResult BuildLiteralAndDistanceTables(const Elysium::Core::Template::Container::View::MultiSpan<Elysium::Core::Template::System::byte, 1024, 2> SourceSpans,
			Elysium::Core::Template::System::size& BytesLoadedIntoBitReader)
		{
			constexpr Elysium::Core::Template::System::uint8_t FastTableBits = Elysium::Core::Template::IO::Compression::Format::HuffmanCoding::CodeLengthTable::FastTableBits;

			Elysium::Core::Template::IO::Compression::Format::HuffmanCoding::CodeLengthTableEntry PreviousEntry = _DynamicHuffmanHeader._CurrentLiteralAndDistanceTreePreviousEntry;

			for (Elysium::Core::Template::System::uint16_t i = _DynamicHuffmanHeader._CurrentLiteralAndDistanceTreeIndex; i < _DynamicHuffmanHeader.HLIT + _DynamicHuffmanHeader.HDIST; ++i)
			{
				const Elysium::Core::Template::IO::ReadResult BufferPopulationResult = EnsureAvailableBit(14, SourceSpans, BytesLoadedIntoBitReader);
				if (Elysium::Core::Template::IO::ReadResult::Pending == BufferPopulationResult)
				{
					_DynamicHuffmanHeader._CurrentLiteralAndDistanceTreeIndex = i;
					_DynamicHuffmanHeader._CurrentLiteralAndDistanceTreePreviousEntry = PreviousEntry;
					return Elysium::Core::Template::IO::ReadResult::Pending;
				}

				Elysium::Core::Template::System::uint64_t CurrentSymbolIndex = _BitReader.Read(7);

				// BitReader returns a 64bit integer so if the implementation is not correct, this might still result in a bug!!!
				if (CurrentSymbolIndex > Elysium::Core::Template::IO::Compression::Format::HuffmanCoding::CodeLengthTable::TableLength)
				{
					throw 1;
				}

				Elysium::Core::Template::IO::Compression::Format::HuffmanCoding::CodeLengthTableEntry Entry = _DynamicHuffmanHeader._CodeLengthTable[CurrentSymbolIndex];
				Elysium::Core::Template::System::uint8_t CurrentSymbol = Entry._Symbol;
				Elysium::Core::Template::System::uint8_t CurrentLength = Entry._Length;

				if (CurrentSymbol <= 15)
				{
					if (i < _DynamicHuffmanHeader.HLIT)
					{
						_DynamicHuffmanHeader._LiteralLengths[i] = CurrentLength;
					}
					else
					{
						_DynamicHuffmanHeader._DistanceLengths[i - _DynamicHuffmanHeader.HLIT] = CurrentLength;
					}
				}
				else if (CurrentSymbol == 16)
				{
					if (0 == i)
					{	// @ToDo: this is invalid!
						throw 1;
					}

					Elysium::Core::Template::System::uint64_t Repeat = _BitReader.Read(2) + 3;
					if (i + Repeat > _DynamicHuffmanHeader.HLIT + _DynamicHuffmanHeader.HDIST)
					{	// @ToDo: overflow as a result of corrupted source data
						throw 1;
					}

					for (Elysium::Core::Template::System::uint16_t r = 0; r < Repeat; ++r)
					{
						if (i < _DynamicHuffmanHeader.HLIT)
						{
							_DynamicHuffmanHeader._LiteralLengths[i] = PreviousEntry._Length;
						}
						else
						{
							_DynamicHuffmanHeader._DistanceLengths[i - _DynamicHuffmanHeader.HLIT] = PreviousEntry._Length;
						}
						++i;
					}
				}
				else if (CurrentSymbol == 17)
				{
					Elysium::Core::Template::System::uint64_t Repeat = _BitReader.Read(3) + 3;
					if (i + Repeat > _DynamicHuffmanHeader.HLIT + _DynamicHuffmanHeader.HDIST)
					{	// @ToDo: overflow as a result of corrupted source data
						throw 1;
					}

					for (Elysium::Core::Template::System::uint16_t r = 0; r < Repeat; ++r)
					{
						if (i < _DynamicHuffmanHeader.HLIT)
						{
							_DynamicHuffmanHeader._LiteralLengths[i] = 0;
						}
						else
						{
							_DynamicHuffmanHeader._DistanceLengths[i - _DynamicHuffmanHeader.HLIT] = 0;
						}
						++i;
					}
				}
				else if (CurrentSymbol == 18)
				{
					Elysium::Core::Template::System::uint64_t Repeat = _BitReader.Read(7) + 11;
					if (i + Repeat > _DynamicHuffmanHeader.HLIT + _DynamicHuffmanHeader.HDIST)
					{	// @ToDo: overflow as a result of corrupted source data
						throw 1;
					}

					for (Elysium::Core::Template::System::uint16_t r = 0; r < Repeat; ++r)
					{
						if (i < _DynamicHuffmanHeader.HLIT)
						{
							_DynamicHuffmanHeader._LiteralLengths[i] = 0;
						}
						else
						{
							_DynamicHuffmanHeader._DistanceLengths[i - _DynamicHuffmanHeader.HLIT] = 0;
						}
						++i;
					}
				}
				else
				{
					// @ToDo:
					throw 1;
				}

				PreviousEntry = Entry;
			}

			// ...
			BuildCanonicalCodes(_DynamicHuffmanHeader._LiteralLengths, _DynamicHuffmanHeader.HLIT, &_DynamicHuffmanHeader._CanonicalLiteralCodes[0]);
			BuildCanonicalCodes(_DynamicHuffmanHeader._DistanceLengths, _DynamicHuffmanHeader.HDIST, &_DynamicHuffmanHeader._CanonicalDistanceCodes[0]);

			// ...




			return Elysium::Core::Template::IO::ReadResult::HasData;
		}
	private:
		inline void BuildCanonicalCodes(const Elysium::Core::Template::System::uint8_t* Lengths, const Elysium::Core::Template::System::uint8_t Length,
			Elysium::Core::Template::System::uint16_t* Codes)
		{
			Elysium::Core::Template::System::uint16_t BitLengthCount[16] = { 0 };
			Elysium::Core::Template::System::uint16_t NextCode[16] = { 0 };

			for (Elysium::Core::Template::System::uint16_t i = 0; i < Length; ++i)
			{
				BitLengthCount[Lengths[i]]++;
			}

			Elysium::Core::Template::System::uint16_t Code = 0;
			for (Elysium::Core::Template::System::uint8_t Bits = 1; Bits <= 15; ++Bits)
			{
				Code = (Code + BitLengthCount[Bits - 1]) << 1;
				NextCode[Bits] = Code;
			}

			for (Elysium::Core::Template::System::uint16_t i = 0; i < Length; ++i)
			{
				Elysium::Core::Template::System::uint8_t CurrentLength = Lengths[i];
				if (CurrentLength != 0)
				{
					Codes[i] = NextCode[CurrentLength]++;
				}
			}
		}

		inline Elysium::Core::Template::System::uint16_t ReverseBits(Elysium::Core::Template::System::uint16_t Code, Elysium::Core::Template::System::uint16_t Length)
		{
			Elysium::Core::Template::System::uint16_t Result = 0;
			for (int i = 0; i < Length; i++)
			{
				Result = (Result << 1) | (Code & 1);
				Code >>= 1;
			}

			return Result;
		}

		inline const Elysium::Core::Template::IO::ReadResult EnsureAvailableBit(const Elysium::Core::Template::System::size Bits,
			const Elysium::Core::Template::Container::View::MultiSpan<Elysium::Core::Template::System::byte, 1024, 2> SourceSpans,
			Elysium::Core::Template::System::size& BytesLoadedIntoBitReader)
		{
			if (_BitReader.HasBits(Bits))
			{
				return Elysium::Core::Template::IO::ReadResult::HasData;
			}
			/*
			// This is a private method. I am making sure this doesn't happen in my implementation so this check isn't necessary!
			if (Bits > (Elysium::Core::Template::IO::BitReader<true>::SafeShiftThreshold + 8))
			{	// @ToDo:
				throw 1;
			}
			*/
			const Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> ReadableSpan0 = SourceSpans.GetFirst();
			const Elysium::Core::Template::System::size ReadableSpan0Length = ReadableSpan0.GetLength();

			if (BytesLoadedIntoBitReader < ReadableSpan0Length)
			{
				const Elysium::Core::Template::System::size Offset0 = BytesLoadedIntoBitReader;
				const Elysium::Core::Template::System::byte* Data0 = &ReadableSpan0.GetData()[Offset0];
				const Elysium::Core::Template::System::size Length0 = Elysium::Core::Template::Math::Min(8_ui64, ReadableSpan0Length - Offset0);

				// @ToDo: can I optimize a byte-by-byte push? (for instance: if there are 32 bit left, I could push one single 32 bit integer and possibly make it faster?)
				const Elysium::Core::Template::System::size FreeBytes = (BitReader<true>::SafeShiftThreshold - _BitReader.GetLength()) / 8;
				const Elysium::Core::Template::System::size BytesToCopy0 = Elysium::Core::Template::Math::Min(Length0, FreeBytes);
				for (Elysium::Core::Template::System::size i = 0; i < BytesToCopy0; ++i)
				{
					_BitReader.Push(Data0[i]);
				}
				BytesLoadedIntoBitReader += BytesToCopy0;
			}


			if (!_BitReader.GetIsFull() && BytesLoadedIntoBitReader >= ReadableSpan0Length)
			{
				const Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> ReadableSpan1 = SourceSpans.GetSecond();
				const Elysium::Core::Template::System::size ReadableSpan1Length = ReadableSpan1.GetLength();

				const Elysium::Core::Template::System::size Offset1 = BytesLoadedIntoBitReader - ReadableSpan0Length;

				if (Offset1 < ReadableSpan1Length)
				{
					const Elysium::Core::Template::System::byte* Data1 = &ReadableSpan1.GetData()[Offset1];
					const Elysium::Core::Template::System::size Length1 = Elysium::Core::Template::Math::Min(8_ui64, ReadableSpan1.GetLength() - Offset1);

					// @ToDo: same possible optimization of byte-by-byte push
					const Elysium::Core::Template::System::size FreeBytes = (BitReader<true>::SafeShiftThreshold - _BitReader.GetLength()) / 8;
					const Elysium::Core::Template::System::size BytesToCopy1 = Elysium::Core::Template::Math::Min(Length1, FreeBytes);
					for (Elysium::Core::Template::System::size i = 0; i < BytesToCopy1; ++i)
					{
						_BitReader.Push(Data1[i]);
					}
					BytesLoadedIntoBitReader += BytesToCopy1;
				}
			}

			if (!_BitReader.HasBits(Bits))
			{
				return Elysium::Core::Template::IO::ReadResult::Pending;
			}

			return Elysium::Core::Template::IO::ReadResult::HasData;
		}
	private:
		Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState _State;
		Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockHeader _BlockHeader;

		Elysium::Core::Template::IO::BitReader<true> _BitReader;






		struct UncompressedBlockInfo
		{
			Elysium::Core::Template::System::uint16_t LEN;
			Elysium::Core::Template::System::uint16_t NLEN;

			Elysium::Core::Template::System::uint16_t BytesCopied;
		};

		struct FixedHuffmanInfo
		{

		};

		struct DynamicHuffmanInfo
		{
			// header
			Elysium::Core::Template::System::uint64_t HLIT;
			Elysium::Core::Template::System::uint64_t HDIST;
			Elysium::Core::Template::System::uint64_t HCLEN;

			// code length tree
			Elysium::Core::Template::IO::Compression::Format::HuffmanCoding::CodeLengthTable _CodeLengthTable;

			// literal and distance trees as well as their current "reading" states
			Elysium::Core::Template::System::uint16_t _CurrentLiteralAndDistanceTreeIndex = 0;
			Elysium::Core::Template::IO::Compression::Format::HuffmanCoding::CodeLengthTableEntry _CurrentLiteralAndDistanceTreePreviousEntry = { 0, 0 };

			Elysium::Core::Template::System::uint8_t _LiteralLengths[286]{};
			Elysium::Core::Template::System::uint8_t _DistanceLengths[32]{};

			Elysium::Core::Template::System::uint16_t _CanonicalLiteralCodes[286]{};
			Elysium::Core::Template::System::uint16_t _CanonicalDistanceCodes[32]{};

			Elysium::Core::Template::IO::Compression::Format::HuffmanCoding::HuffmanTable<Elysium::Core::Template::System::byte, 9, 2048> _LiteralTree;
			Elysium::Core::Template::IO::Compression::Format::HuffmanCoding::HuffmanTable<Elysium::Core::Template::System::byte, 5, 256> _DistanceTree;

			// ...

		};
		/*
		union
		{
			UncompressedBlockInfo Stored;
			FixedHuffmanInfo Fixed;
			DynamicHuffmanInfo Dynamic;
		};
		*/
		DynamicHuffmanInfo _DynamicHuffmanHeader;






		Elysium::Core::Template::Container::SlidingWindow<Elysium::Core::Template::System::byte> _HistoryBuffer;




		/*
		HuffmanTable _litLenTable;
		HuffmanTable _distTable;
		*/
	};
}
#endif
