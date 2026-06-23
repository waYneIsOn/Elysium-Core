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

				case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::DecompressingDynamicHuffman:
				{
					const Elysium::Core::Template::IO::ReadResult Result = DecompresDynamicHuffman(SourceSpans, BytesFullyProcessed);
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
			/*
			* RFC 1951 describes:
			* 5 Bits: HLIT, # of Literal/Length codes - 257 (257 - 286)
			* 5 Bits: HDIST, # of Distance codes - 1        (1 - 32)
			* 4 Bits: HCLEN, # of Code Length codes - 4     (4 - 19)
			* 
			* ergo need 14 bit
			*/
			const Elysium::Core::Template::IO::ReadResult BufferPopulationResult = EnsureAvailableBit(14, SourceSpans, BytesLoadedIntoBitReader);
			if (Elysium::Core::Template::IO::ReadResult::Pending == BufferPopulationResult)
			{
				return BufferPopulationResult;
			}

			_DynamicHuffmanHeader.HLIT = _BitReader.Read(5);
			if (_DynamicHuffmanHeader.HLIT > 29)
			{	// @ToDo: this violate rfc 1951 (some kind of OutOfRangeException?)
				throw 1;
			}

			_DynamicHuffmanHeader.HDIST = _BitReader.Read(5);
			if (_DynamicHuffmanHeader.HDIST > 31)
			{	// @ToDo: this violate rfc 1951 (some kind of OutOfRangeException?)
				throw 1;
			}

			_DynamicHuffmanHeader.HCLEN = _BitReader.Read(4);
			if (_DynamicHuffmanHeader.HCLEN > 15)
			{	// @ToDo: this violate rfc 1951 (some kind of OutOfRangeException?)
				throw 1;
			}

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

			const Elysium::Core::Template::System::size AmountOfCodeLengths = _DynamicHuffmanHeader.HCLEN + 4;
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

			// Read code length alphabet
			constexpr Elysium::Core::Template::System::uint8_t MaximumCodeLength = _DynamicHuffmanHeader._CodeLengthTree._MaximumCodeLength;
			Elysium::Core::Template::System::uint64_t KraftSum = 0;
			Elysium::Core::Template::System::size NonZeroCodeLengthCount = 0;
			for (Elysium::Core::Template::System::size i = 0; i < AmountOfCodeLengths; ++i)
			{
				Elysium::Core::Template::System::uint64_t CurrentValue = _BitReader.Read(3);

				// 3 bits -> maximum 0b111 = 7 BUT BitReader returns a 64bit integer so if the implementation is not correct, this might still result in a bug!!!
				if (CurrentValue > MaximumCodeLength)
				{	// @ToDo: this violate rfc 1951
					throw 1;
				}
				
				Elysium::Core::Template::System::uint8_t Symbol = FixedPermutations[i];
				_DynamicHuffmanHeader._CodeLengthTree._CodeLengths[Symbol] = static_cast<Elysium::Core::Template::System::uint8_t>(CurrentValue);

				if (_DynamicHuffmanHeader._CodeLengthTree._CodeLengths[Symbol] > 0)
				{
					KraftSum += (1_ui64 << (7 - _DynamicHuffmanHeader._CodeLengthTree._CodeLengths[Symbol]));
					++NonZeroCodeLengthCount;
				}
			}

			// KraftSum per RFC 1951 does not need to be exactly equal to the length of the table.
			// If it is smaller, the code-length tree simply is imcomplete which is allowed for code-length tree but not for literal- or distance-tree.
			// If it is larger, the code length alphabet is oversubscriped which is invalid!
			if (KraftSum > (1 << _DynamicHuffmanHeader._CodeLengthTree._MaximumCodeLength))
			{	// @ToDo: invalid kraft sum
				throw 1;
			}

			if (0 == NonZeroCodeLengthCount)
			{	// @ToDo: all values are zero
				throw 1;
			}

			// ...
			_DynamicHuffmanHeader._CodeLengthTree.BuildTable();

			_State = Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::BuildingLiteralAndDistanceTables;

			return Elysium::Core::Template::IO::ReadResult::HasData;
		}

		inline const Elysium::Core::Template::IO::ReadResult BuildLiteralAndDistanceTables(const Elysium::Core::Template::Container::View::MultiSpan<Elysium::Core::Template::System::byte, 1024, 2> SourceSpans,
			Elysium::Core::Template::System::size& BytesLoadedIntoBitReader)
		{
			Elysium::Core::Template::System::uint8_t PreviousLength = _DynamicHuffmanHeader._CurrentLiteralAndDistanceTreePreviousLength;

			const Elysium::Core::Template::System::uint16_t LiteralLength = _DynamicHuffmanHeader.HLIT + 257;
			const Elysium::Core::Template::System::uint16_t DistanceLength = _DynamicHuffmanHeader.HDIST + 1;

			for (Elysium::Core::Template::System::uint16_t i = _DynamicHuffmanHeader._CurrentLiteralAndDistanceTreeIndex; i < LiteralLength + DistanceLength; ++i)
			{
				const Elysium::Core::Template::IO::ReadResult BufferPopulationResult = EnsureAvailableBit(14, SourceSpans, BytesLoadedIntoBitReader);
				if (Elysium::Core::Template::IO::ReadResult::Pending == BufferPopulationResult)
				{
					_DynamicHuffmanHeader._CurrentLiteralAndDistanceTreeIndex = i;
					_DynamicHuffmanHeader._CurrentLiteralAndDistanceTreePreviousLength = PreviousLength;
					return Elysium::Core::Template::IO::ReadResult::Pending;
				}

				//Elysium::Core::Template::System::uint64_t CurrentSymbolIndex = _BitReader.Peek(7);
				Elysium::Core::Template::System::uint64_t CurrentSymbolIndex = ReverseBits(_BitReader.Peek(7), 7);

				// BitReader returns a 64bit integer so if the implementation is not correct, this might still result in a bug!!!
				if (CurrentSymbolIndex > _DynamicHuffmanHeader._CodeLengthTree.FastTableLength)
				{
					throw 1;
				}
				
				Elysium::Core::Template::IO::Compression::Format::HuffmanCoding::HuffmanTableEntry<Elysium::Core::Template::System::uint8_t>& Entry = 
					_DynamicHuffmanHeader._CodeLengthTree[CurrentSymbolIndex];
				Elysium::Core::Template::System::uint8_t CurrentSymbol = Entry._Symbol;
				Elysium::Core::Template::System::uint8_t CurrentLength = Entry._Length;
				if (0 == CurrentLength)
				{	// 7 bit read, code-length tree/table is build with 7 bit in mind - this fallback should never happen!
					throw 1;
				}

				_BitReader.Consume(Entry._Length);

				if (15 >= CurrentSymbol)
				{
					Elysium::Core::Template::System::uint8_t Length = CurrentSymbol;

					if (i < LiteralLength)
					{
						_DynamicHuffmanHeader._LiteralTree._CodeLengths[i] = Length;
					}
					else
					{
						_DynamicHuffmanHeader._DistanceTree._CodeLengths[i - LiteralLength] = Length;
					}

					PreviousLength = Length;
				}
				else if (16 == CurrentSymbol)
				{
					if (0 == i)
					{	// @ToDo: this is invalid!
						throw 1;
					}

					Elysium::Core::Template::System::uint64_t Repeat = _BitReader.Read(2) + 3;
					if (Repeat > 6)
					{	// @ToDo:
						throw 1;
					}

					if (i + Repeat > LiteralLength + DistanceLength)
					{	// @ToDo: overflow as a result of corrupted source data
						throw 1;
					}

					for (Elysium::Core::Template::System::uint16_t r = 0; r < Repeat; ++r)
					{
						if (i < LiteralLength)
						{
							_DynamicHuffmanHeader._LiteralTree._CodeLengths[i] = PreviousLength;
						}
						else
						{
							_DynamicHuffmanHeader._DistanceTree._CodeLengths[i - LiteralLength] = PreviousLength;
						}

						++i;
					}
					--i;
				}
				else if (17 == CurrentSymbol)
				{
					Elysium::Core::Template::System::uint64_t Repeat = _BitReader.Read(3) + 3;
					if (Repeat > 10)
					{	// @ToDo:
						throw 1;
					}

					if (i + Repeat > LiteralLength + DistanceLength)
					{	// @ToDo: overflow as a result of corrupted source data
						throw 1;
					}

					for (Elysium::Core::Template::System::uint16_t r = 0; r < Repeat; ++r)
					{
						if (i < LiteralLength)
						{
							_DynamicHuffmanHeader._LiteralTree._CodeLengths[i] = 0;
						}
						else
						{
							_DynamicHuffmanHeader._DistanceTree._CodeLengths[i - LiteralLength] = 0;
						}

						++i;
					}
					--i;
				}
				else if (18 == CurrentSymbol)
				{
					Elysium::Core::Template::System::uint64_t Repeat = _BitReader.Read(7) + 11;
					if (Repeat > 138)
					{	// @ToDo:
						throw 1;
					}

					if (i + Repeat > LiteralLength + DistanceLength)
					{	// @ToDo: overflow as a result of corrupted source data
						throw 1;
					}

					for (Elysium::Core::Template::System::uint16_t r = 0; r < Repeat; ++r)
					{
						if (i < LiteralLength)
						{
							_DynamicHuffmanHeader._LiteralTree._CodeLengths[i] = 0;
						}
						else
						{
							_DynamicHuffmanHeader._DistanceTree._CodeLengths[i - LiteralLength] = 0;
						}

						++i;
					}
					--i;
				}
				else
				{
					// @ToDo:
					throw 1;
				}
			}

			// ...
			_DynamicHuffmanHeader._LiteralTree.BuildTable();
			_DynamicHuffmanHeader._DistanceTree.BuildTable();

			_State = Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::DecompressingDynamicHuffman;

			return Elysium::Core::Template::IO::ReadResult::HasData;
		}

		inline const Elysium::Core::Template::IO::ReadResult DecompresDynamicHuffman(const Elysium::Core::Template::Container::View::MultiSpan<Elysium::Core::Template::System::byte, 1024, 2> SourceSpans,
			Elysium::Core::Template::System::size& BytesLoadedIntoBitReader)
		{
			while (true)
			{
				const Elysium::Core::Template::IO::ReadResult BufferPopulationResult = EnsureAvailableBit(_DynamicHuffmanHeader._LiteralTree._FastTableBits, SourceSpans, BytesLoadedIntoBitReader);
				if (Elysium::Core::Template::IO::ReadResult::Pending == BufferPopulationResult)
				{
					return Elysium::Core::Template::IO::ReadResult::Pending;
				}

				//Elysium::Core::Template::System::uint64_t CurrentSymbolIndex = _BitReader.Peek(_DynamicHuffmanHeader._LiteralTree._FastTableBits);
				Elysium::Core::Template::System::uint64_t CurrentSymbolIndex = ReverseBits(_BitReader.Peek(_DynamicHuffmanHeader._LiteralTree._FastTableBits), _DynamicHuffmanHeader._LiteralTree._FastTableBits);

				// BitReader returns a 64bit integer so if the implementation is not correct, this might still result in a bug!!!
				if (CurrentSymbolIndex > (_DynamicHuffmanHeader._LiteralTree.FastTableLength + _DynamicHuffmanHeader._DistanceTree.FastTableLength))
				{
					throw 1;
				}

				Elysium::Core::Template::IO::Compression::Format::HuffmanCoding::HuffmanTableEntry<Elysium::Core::Template::System::uint16_t>& Entry =
					_DynamicHuffmanHeader._LiteralTree[CurrentSymbolIndex];
				Elysium::Core::Template::System::uint8_t CurrentSymbol = Entry._Symbol;
				Elysium::Core::Template::System::uint8_t CurrentLength = Entry._Length;
				if (0 == CurrentLength)
				{	// @ToDo: fallback!
					throw 1;
				}

				if (nullptr == Entry._Subtable)
				{
					const char xxxxxx = Entry._Symbol;

					if (Entry._Symbol < 256)
					{
						bool sdf = false;
					}
					else if (Entry._Symbol == 256)
					{	// EOB
						bool sdf = false;
					}
					else
					{	// lz77?
						bool sdf = false;
					}
				}
			}

			throw 1;


			return Elysium::Core::Template::IO::ReadResult::HasData;
		}
	private:
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
			Elysium::Core::Template::IO::Compression::Format::HuffmanCoding::HuffmanTable<Elysium::Core::Template::System::uint8_t, 7, 19, 7, 0> _CodeLengthTree;

			// literal and distance trees as well as their current "reading" states
			Elysium::Core::Template::System::uint16_t _CurrentLiteralAndDistanceTreeIndex = 0;
			Elysium::Core::Template::System::uint8_t _CurrentLiteralAndDistanceTreePreviousLength{ };

			Elysium::Core::Template::IO::Compression::Format::HuffmanCoding::HuffmanTable<Elysium::Core::Template::System::uint16_t, 15, 288, 9, 2048> _LiteralTree;
			Elysium::Core::Template::IO::Compression::Format::HuffmanCoding::HuffmanTable<Elysium::Core::Template::System::uint8_t, 15, 32, 5, 256> _DistanceTree;

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
