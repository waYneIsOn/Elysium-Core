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

#ifndef ELYSIUM_CORE_TEMPLATE_IO_BITBUFFER
#include "../../../BitBuffer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_ALGORITHM_DEFLATE_DEFLATEUTILITY
#include "DeflateUtility.hpp"
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
			: _State{}, _BlockHeader{}, _BitBuffer{}, _UncompressedHuffmanHeader{}, _DynamicHuffmanHeader {}, _CurrentLiteralEntry(_InvalidLiteralEntry), _CurrentLength{},
			_CurrentDistance{}, _LZ77HistoryBuffer(DeflateUtility::LZ77HistoryBufferSize), _LZ77HistoryBufferReadPosition{}, _Distance{}, _Length{}
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
			Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte>& TargetSpan, Elysium::Core::Template::System::size& OutputBytesWritten,
			Elysium::Core::Template::System::size& BytesFullyProcessed)
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
				case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::ReadingUncompressedHeaderFields:
				{
					const Elysium::Core::Template::IO::ReadResult Result = ReadUncompressedHeaderFields(SourceSpans, BytesFullyProcessed);
					if (Elysium::Core::Template::IO::ReadResult::Pending == Result)
					{
						return Result;
					}
				}
					break;
				case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::ReadingUncompressedData:
				{
					const Elysium::Core::Template::IO::ReadResult Result = ReadUncompressedData(SourceSpans, TargetSpan, OutputBytesWritten, BytesFullyProcessed);
					if (Elysium::Core::Template::IO::ReadResult::Pending == Result ||
						Elysium::Core::Template::IO::ReadResult::HasData == Result)
					{
						return Result;
					}
				}
					break;
				case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::DecompressingStaticHuffman:
				{
					const Elysium::Core::Template::IO::ReadResult Result = DecompressStaticHuffman(SourceSpans, TargetSpan, OutputBytesWritten, BytesFullyProcessed);
					if (Elysium::Core::Template::IO::ReadResult::Pending == Result ||
						Elysium::Core::Template::IO::ReadResult::HasData == Result)
					{
						return Result;
					}
				}
				break;
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
					const Elysium::Core::Template::IO::ReadResult Result = DecompressDynamicHuffman(SourceSpans, TargetSpan, OutputBytesWritten, BytesFullyProcessed);
					if (Elysium::Core::Template::IO::ReadResult::Pending == Result ||
						Elysium::Core::Template::IO::ReadResult::HasData == Result)
					{
						return Result;
					}
				}
					break;
				case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::Done:
					return Elysium::Core::Template::IO::ReadResult::EndOfStream;
				default:
					// @ToDo
					throw 1;
				}
			}
		}
	private:
		inline const Elysium::Core::Template::IO::ReadResult ReadBlockHeader(const Elysium::Core::Template::Container::View::MultiSpan<Elysium::Core::Template::System::byte, 1024, 2> SourceSpans,
			Elysium::Core::Template::System::size& BytesLoadedIntoBitReader)
		{
			static constexpr const Elysium::Core::Template::System::size HeaderSize = Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockHeader::Size;

			const Elysium::Core::Template::IO::ReadResult BufferPopulationResult = EnsureAvailableBit(3, SourceSpans, BytesLoadedIntoBitReader);
			if (Elysium::Core::Template::IO::ReadResult::Pending == BufferPopulationResult)
			{
				return BufferPopulationResult;
			}

			_BlockHeader._Data = static_cast<Elysium::Core::Template::System::byte>(_BitBuffer.Read(3));

			const Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockType BlockType = _BlockHeader.GetCompressionMethod();
			switch (BlockType)
			{
			case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockType::Uncompressed:
				_State = Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::ReadingUncompressedHeaderFields;
				break;
			case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockType::FixedHuffman:
				_State = Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::DecompressingStaticHuffman;
				break;
			case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockType::DynamicHuffman:
				_State = Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::ReadingDynamicHuffmanHeaderFields;
				break;
			case Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockType::Invalid:
				// @ToDo
				throw 1;
			default:
				throw 1;
			}

			return Elysium::Core::Template::IO::ReadResult::HasData;
		}

		inline const Elysium::Core::Template::IO::ReadResult ReadUncompressedHeaderFields(const Elysium::Core::Template::Container::View::MultiSpan<Elysium::Core::Template::System::byte, 1024, 2> SourceSpans,
			Elysium::Core::Template::System::size& BytesLoadedIntoBitReader)
		{
			if (0 == _UncompressedHuffmanHeader._Length)
			{
				const Elysium::Core::Template::IO::ReadResult BufferPopulationResult = EnsureAvailableBit(sizeof(Elysium::Core::Template::System::uint16_t) * 8, SourceSpans, 
					BytesLoadedIntoBitReader);
				if (Elysium::Core::Template::IO::ReadResult::Pending == BufferPopulationResult)
				{
					return BufferPopulationResult;
				}

				_BitBuffer.AlignToByteBoundary();
				
				Elysium::Core::Template::System::uint64_t LEN = _BitBuffer.Read(sizeof(Elysium::Core::Template::System::uint16_t) * 8);

				_UncompressedHuffmanHeader._Length = static_cast<Elysium::Core::Template::System::uint16_t>(LEN);
			}

			// @ToDo: since NLEN is the complement of LEN, 0 would be wrong in the case of LEN being MAX uint16_t
			if (0 == _UncompressedHuffmanHeader._ComplementaryLength)
			{
				const Elysium::Core::Template::IO::ReadResult BufferPopulationResult = EnsureAvailableBit(sizeof(Elysium::Core::Template::System::uint16_t) * 8, SourceSpans, 
					BytesLoadedIntoBitReader);
				if (Elysium::Core::Template::IO::ReadResult::Pending == BufferPopulationResult)
				{
					return BufferPopulationResult;
				}

				Elysium::Core::Template::System::uint64_t NLEN = _BitBuffer.Read(sizeof(Elysium::Core::Template::System::uint16_t) * 8);

				_UncompressedHuffmanHeader._ComplementaryLength = static_cast<Elysium::Core::Template::System::uint16_t>(NLEN);
			}

			const Elysium::Core::Template::System::uint16_t CalculatedComplementaryLength = ~_UncompressedHuffmanHeader._Length;
			if (CalculatedComplementaryLength != _UncompressedHuffmanHeader._ComplementaryLength)
			{	// @ToDo:
				throw 1;
			}
			
			// Deflate allows for no data in an uncompressed block
			_State = 0 == _UncompressedHuffmanHeader._Length ? Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::ReadingBlockHeader :
				Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::ReadingUncompressedData;

			return Elysium::Core::Template::IO::ReadResult::HasData;
		}

		inline const Elysium::Core::Template::IO::ReadResult ReadUncompressedData(const Elysium::Core::Template::Container::View::MultiSpan<Elysium::Core::Template::System::byte, 1024, 2> SourceSpans,
			Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte>& TargetSpan, Elysium::Core::Template::System::size& OutputBytesWritten,
			Elysium::Core::Template::System::size& BytesConsumed)
		{
			const Elysium::Core::Template::System::uint8_t AvailableBits = _BitBuffer.GetLength();
			if(0 != AvailableBits % 8)
			{	// not correctly aligned -> implementation bug
				throw 1;
			}

			// Drain _BitReader first
			if (0 < AvailableBits)
			{
				const Elysium::Core::Template::System::uint8_t AvailableBytes = AvailableBits / 8;
				/*
				// this check shouldn't be necessary at this point
				if (BytesConsumed + AvailableBytes > TargetSpan.GetLength())
				{
					return 0 == BytesConsumed ? Elysium::Core::Template::IO::ReadResult::Pending : Elysium::Core::Template::IO::ReadResult::HasData;
				}
				*/
				Elysium::Core::Template::System::uint16_t BytesToCopy = Elysium::Core::Template::Math::Min(static_cast<Elysium::Core::Template::System::uint16_t>(AvailableBytes),
					static_cast<Elysium::Core::Template::System::uint16_t>(_UncompressedHuffmanHeader._Length - _UncompressedHuffmanHeader._TotalBytesCopied));

				Elysium::Core::Template::System::byte* TargetData = TargetSpan.GetData();

				Elysium::Core::Template::System::uint64_t Bytes = _BitBuffer.Read(BytesToCopy * 8);
				//Elysium::Core::Template::Memory::MemCpy(&TargetData[BytesConsumed], &Bytes, BytesToCopy);
				//Elysium::Core::Template::Memory::MemCpy(TargetData, &Bytes, BytesToCopy);
				Elysium::Core::Template::Memory::MemCpy(&TargetData[OutputBytesWritten], &Bytes, BytesToCopy);
				OutputBytesWritten += BytesToCopy;
				//BytesConsumed += BytesToCopy;	// these bytes already were in _BitReader!
				_UncompressedHuffmanHeader._TotalBytesCopied += BytesToCopy;
				/*
				// ...
				if (0 < BytesConsumed)
				{
					return Elysium::Core::Template::IO::ReadResult::HasData;
				}
				*/
			}

			// From now on copy directly from SourceSpans
			const Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> ReadableSpan0 = SourceSpans.GetFirst();
			const Elysium::Core::Template::System::size ReadableSpan0Length = ReadableSpan0.GetLength();

			const Elysium::Core::Template::System::size Offset0 = BytesConsumed;
			if (BytesConsumed < ReadableSpan0Length)
			{
				const Elysium::Core::Template::System::byte* Data0 = &ReadableSpan0.GetData()[Offset0];
				const Elysium::Core::Template::System::size AvailableBytes0 = Elysium::Core::Template::Math::Min(
					static_cast<Elysium::Core::Template::System::size>(_UncompressedHuffmanHeader._Length - _UncompressedHuffmanHeader._TotalBytesCopied),
					ReadableSpan0Length - Offset0);
				const Elysium::Core::Template::System::size BytesToCopy0 = Elysium::Core::Template::Math::Min(AvailableBytes0, TargetSpan.GetLength());

				Elysium::Core::Template::System::byte* TargetData = &TargetSpan.GetData()[OutputBytesWritten];
				Elysium::Core::Template::Memory::MemCpy(TargetData, Data0, BytesToCopy0);
				OutputBytesWritten += BytesToCopy0;
				BytesConsumed += BytesToCopy0;
				_UncompressedHuffmanHeader._TotalBytesCopied += BytesToCopy0;
			}

			if(BytesConsumed == ReadableSpan0Length)
			{
				const Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> ReadableSpan1 = SourceSpans.GetSecond();
				const Elysium::Core::Template::System::size ReadableSpan1Length = ReadableSpan1.GetLength();

				const Elysium::Core::Template::System::byte* Data1 = ReadableSpan1.GetData();
				const Elysium::Core::Template::System::size AvailableBytes1 = Elysium::Core::Template::Math::Min(
					static_cast<Elysium::Core::Template::System::size>(_UncompressedHuffmanHeader._Length - _UncompressedHuffmanHeader._TotalBytesCopied),
					ReadableSpan1Length);
				const Elysium::Core::Template::System::size BytesToCopy1 = Elysium::Core::Template::Math::Min(AvailableBytes1, TargetSpan.GetLength());

				Elysium::Core::Template::System::byte* TargetData = &TargetSpan.GetData()[OutputBytesWritten];
				Elysium::Core::Template::Memory::MemCpy(TargetData, Data1, BytesToCopy1);
				OutputBytesWritten += BytesToCopy1;
				BytesConsumed += BytesToCopy1;
				_UncompressedHuffmanHeader._TotalBytesCopied += BytesToCopy1;
			}

			if (_UncompressedHuffmanHeader._TotalBytesCopied == _UncompressedHuffmanHeader._Length)
			{
				_State = _BlockHeader.GetIsFinalBlock() ? Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::Done :
					Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::ReadingBlockHeader;
				_UncompressedHuffmanHeader._Length = 0;
				_UncompressedHuffmanHeader._ComplementaryLength = 0;
				_UncompressedHuffmanHeader._TotalBytesCopied = 0;
			}

			return 0 == OutputBytesWritten ? Elysium::Core::Template::IO::ReadResult::Pending : Elysium::Core::Template::IO::ReadResult::HasData;
		}

		inline const Elysium::Core::Template::IO::ReadResult DecompressStaticHuffman(const Elysium::Core::Template::Container::View::MultiSpan<Elysium::Core::Template::System::byte, 1024, 2> SourceSpans,
			Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte>& TargetSpan, Elysium::Core::Template::System::size& OutputBytesWritten,
			Elysium::Core::Template::System::size& BytesLoadedIntoBitReader)
		{

			Elysium::Core::Template::System::uint16_t CanonicalCode =
				Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::StaticLiteralTree._CanonicalCodes[0];

			throw 1;
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

			_DynamicHuffmanHeader.HLIT = _BitBuffer.Read(5);
			if (_DynamicHuffmanHeader.HLIT > DeflateUtility::HLITMaximum)
			{	// @ToDo: this violate rfc 1951 (some kind of OutOfRangeException?)
				throw 1;
			}

			_DynamicHuffmanHeader.HDIST = _BitBuffer.Read(5);
			if (_DynamicHuffmanHeader.HDIST > DeflateUtility::HDISTMaximum)
			{	// @ToDo: this violate rfc 1951 (some kind of OutOfRangeException?)
				throw 1;
			}

			_DynamicHuffmanHeader.HCLEN = _BitBuffer.Read(4);
			if (_DynamicHuffmanHeader.HCLEN > DeflateUtility::HCLENMaximum)
			{	// @ToDo: this violate rfc 1951 (some kind of OutOfRangeException?)
				throw 1;
			}

			_State = Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::BuildingCodeLengthTable;

			return Elysium::Core::Template::IO::ReadResult::HasData;
		}

		inline const Elysium::Core::Template::IO::ReadResult BuildCodeLengthTable(const Elysium::Core::Template::Container::View::MultiSpan<Elysium::Core::Template::System::byte, 1024, 2> SourceSpans,
			Elysium::Core::Template::System::size& BytesLoadedIntoBitReader)
		{
			const Elysium::Core::Template::System::size AmountOfCodeLengths = _DynamicHuffmanHeader.HCLEN + DeflateUtility::HCLENAddition;
			const Elysium::Core::Template::System::size BitsRequiredInTotal = DeflateUtility::BitsRequiredPerCodeLengthEntry * AmountOfCodeLengths;
			if (BitsRequiredInTotal > BitBuffer<true>::Capacity)
			{	// @Todo: Code-length codes maximum is 19: 19 * 3 = 57 so an overflow should never happen!
				// if this error occurres, something in the implementation is entirely incorrect!
				throw 1;
			}

			const Elysium::Core::Template::IO::ReadResult BufferPopulationResult = EnsureAvailableBit(BitsRequiredInTotal, SourceSpans, BytesLoadedIntoBitReader);
			if (Elysium::Core::Template::IO::ReadResult::Pending == BufferPopulationResult)
			{
				return BufferPopulationResult;
			}

			// Read code length alphabet
			constexpr Elysium::Core::Template::System::uint8_t MaximumCodeLength = _DynamicHuffmanHeader._CodeLengthTree._MaximumCodeLength;
			Elysium::Core::Template::System::uint64_t KraftSum = 0;
			Elysium::Core::Template::System::size NonZeroCodeLengthCount = 0;
			for (Elysium::Core::Template::System::size i = 0; i < AmountOfCodeLengths; ++i)
			{
				Elysium::Core::Template::System::uint64_t CurrentValue = _BitBuffer.Read(3);

				// 3 bits -> maximum 0b111 = 7 BUT BitReader returns a 64bit integer so if the implementation is not correct, this might still result in a bug!!!
				if (CurrentValue > MaximumCodeLength)
				{	// @ToDo: this violate rfc 1951
					throw 1;
				}
				
				Elysium::Core::Template::System::uint8_t Symbol = DeflateUtility::FixedCodeLengthPermutations[i];
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

			const Elysium::Core::Template::System::uint16_t LiteralLength = _DynamicHuffmanHeader.HLIT + DeflateUtility::HLITAddition;
			const Elysium::Core::Template::System::uint16_t DistanceLength = _DynamicHuffmanHeader.HDIST + DeflateUtility::HDISTAddition;

			for (Elysium::Core::Template::System::uint16_t i = _DynamicHuffmanHeader._CurrentLiteralAndDistanceTreeIndex; i < LiteralLength + DistanceLength; ++i)
			{
				const Elysium::Core::Template::IO::ReadResult BufferPopulationResult = EnsureAvailableBit(14, SourceSpans, BytesLoadedIntoBitReader);
				if (Elysium::Core::Template::IO::ReadResult::Pending == BufferPopulationResult)
				{
					_DynamicHuffmanHeader._CurrentLiteralAndDistanceTreeIndex = i;
					_DynamicHuffmanHeader._CurrentLiteralAndDistanceTreePreviousLength = PreviousLength;
					return Elysium::Core::Template::IO::ReadResult::Pending;
				}

				Elysium::Core::Template::System::uint64_t CodeLengthSymbolIndex = _BitBuffer.Peek(7);

				// BitReader returns a 64bit integer so if the implementation is not correct, this might still result in a bug!!!
				if (CodeLengthSymbolIndex > _DynamicHuffmanHeader._CodeLengthTree.FastTableLength)
				{
					throw 1;
				}
				
				DeflateUtility::CodeLengthTreeEntryReference CodeLengthEntry = _DynamicHuffmanHeader._CodeLengthTree[CodeLengthSymbolIndex];
				DeflateUtility::CodeLengthTreeSymbolType CurrentSymbol = CodeLengthEntry._Symbol;
				Elysium::Core::Template::System::uint8_t CurrentLength = CodeLengthEntry._Length;
				if (0 == CurrentLength)
				{	// 7 bit read, code-length tree/table is build with 7 bit in mind - this fallback should never happen!
					throw 1;
				}

				_BitBuffer.Consume(CodeLengthEntry._Length);

				if (15 >= CurrentSymbol)
				{
					if (i < LiteralLength)
					{
						_DynamicHuffmanHeader._LiteralTree._CodeLengths[i] = CurrentSymbol;
					}
					else
					{
						_DynamicHuffmanHeader._DistanceTree._CodeLengths[i - LiteralLength] = CurrentSymbol;
					}

					PreviousLength = CurrentSymbol;
				}
				else if (16 == CurrentSymbol)
				{
					if (0 == i)
					{	// @ToDo: this is invalid!
						throw 1;
					}

					Elysium::Core::Template::System::uint64_t Repeat = _BitBuffer.Read(2) + 3;
					if (6 < Repeat)
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
					Elysium::Core::Template::System::uint64_t Repeat = _BitBuffer.Read(3) + 3;
					if (10 < Repeat)
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

					PreviousLength = 0;
				}
				else if (18 == CurrentSymbol)
				{
					Elysium::Core::Template::System::uint64_t Repeat = _BitBuffer.Read(7) + 11;
					if (138 < Repeat)
					{	// @ToDo:
						throw 1;
					}

					// It's valid to truncate symbol 18!
					Elysium::Core::Template::System::uint64_t Remaining = LiteralLength + DistanceLength - i;
					Elysium::Core::Template::System::uint64_t ActualRepeat = Elysium::Core::Template::Math::Min(Repeat, Remaining);

					if (i + ActualRepeat > LiteralLength + DistanceLength)
					{	// @ToDo: overflow as a result of corrupted source data
						throw 1;
					}

					for (Elysium::Core::Template::System::uint16_t r = 0; r < ActualRepeat; ++r)
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

					PreviousLength = 0;
				}
				else
				{
					// @ToDo:
					throw 1;
				}
			}

			_DynamicHuffmanHeader._CurrentLiteralAndDistanceTreePreviousLength = 0;
			_DynamicHuffmanHeader._CurrentLiteralAndDistanceTreeIndex = 0;

			_DynamicHuffmanHeader._LiteralTree.BuildTable();
			_DynamicHuffmanHeader._DistanceTree.BuildTable();

			_State = Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::DecompressingDynamicHuffman;

			return Elysium::Core::Template::IO::ReadResult::HasData;
		}

		inline const Elysium::Core::Template::IO::ReadResult DecompressDynamicHuffman(const Elysium::Core::Template::Container::View::MultiSpan<Elysium::Core::Template::System::byte, 1024, 2> SourceSpans,
			Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte>& TargetSpan, Elysium::Core::Template::System::size& OutputBytesWritten,
			Elysium::Core::Template::System::size& BytesLoadedIntoBitReader)
		{
			Elysium::Core::Template::System::size TargetSpanReadPosition = 0;

			while (true)
			{
				if (OutputBytesWritten == TargetSpan.GetLength())
				{
					CopyIntoHistoryBuffer(&TargetSpan.GetData()[TargetSpanReadPosition], OutputBytesWritten - TargetSpanReadPosition);

					return Elysium::Core::Template::IO::ReadResult::HasData;
				}

				const Elysium::Core::Template::IO::ReadResult BufferPopulationSymbolResult = EnsureAvailableBit(_DynamicHuffmanHeader._LiteralTree._FastTableBits, SourceSpans,
					BytesLoadedIntoBitReader);
				if (Elysium::Core::Template::IO::ReadResult::Pending == BufferPopulationSymbolResult)
				{
					if (0 < OutputBytesWritten)
					{
						CopyIntoHistoryBuffer(&TargetSpan.GetData()[TargetSpanReadPosition], OutputBytesWritten - TargetSpanReadPosition);

						return Elysium::Core::Template::IO::ReadResult::HasData;
					}

					return Elysium::Core::Template::IO::ReadResult::Pending;
				}

				if (_InvalidLiteralEntry == _CurrentLiteralEntry)
				{
					Elysium::Core::Template::System::uint64_t LiteralSymbolIndex = _BitBuffer.Peek(_DynamicHuffmanHeader._LiteralTree._FastTableBits);

					// BitReader returns a 64bit integer so if the implementation is not correct, this might still result in a bug!!!
					if (LiteralSymbolIndex > (_DynamicHuffmanHeader._LiteralTree.FastTableLength + _DynamicHuffmanHeader._DistanceTree.FastTableLength))
					{
						throw 1;
					}

					_CurrentLiteralEntry = _DynamicHuffmanHeader._LiteralTree[LiteralSymbolIndex];
					Elysium::Core::Template::System::uint16_t CurrentLength = _CurrentLiteralEntry._Length;
					if (0 == CurrentLength)
					{	// @ToDo
						throw 1;
					}

					_BitBuffer.Consume(_CurrentLiteralEntry._Length);
				}

				DeflateUtility::LiteralTreeSymbolType CurrentSymbol = _CurrentLiteralEntry._Symbol;
				if (256 > CurrentSymbol)
				{
					TargetSpan.GetData()[OutputBytesWritten++] = CurrentSymbol;

					_CurrentLiteralEntry = _InvalidLiteralEntry;
					_CurrentLength = 0;
					_CurrentDistance = 0;
				}
				else if (256 == CurrentSymbol)
				{	// EOB
					if(_BlockHeader.GetIsFinalBlock())
					{
						_State = Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::Done;
					}
					else
					{
						_State = Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::ReadingBlockHeader;
					}

					_CurrentLiteralEntry = _InvalidLiteralEntry;
					_CurrentLength = 0;
					_CurrentDistance = 0;

					return 0 == OutputBytesWritten ? Elysium::Core::Template::IO::ReadResult::Pending : Elysium::Core::Template::IO::ReadResult::HasData;
				}
				else if(_InvalidLiteralEntry._Symbol > CurrentSymbol)
				{	// LZ77
					if (0 == _CurrentLength && 0 == _CurrentDistance)
					{
						const Elysium::Core::Template::System::size LengthIndex = CurrentSymbol - 257;
						const Elysium::Core::Template::System::uint16_t LengthBase = _LZ77LengthBase[LengthIndex];
						const Elysium::Core::Template::System::uint16_t LengthExtraBits = _LZ77LengthExtra[LengthIndex];

						_CurrentLength = LengthBase;
						if (0 < LengthExtraBits)
						{
							const Elysium::Core::Template::IO::ReadResult BufferPopulationResult = EnsureAvailableBit(LengthExtraBits, SourceSpans, BytesLoadedIntoBitReader);
							if (Elysium::Core::Template::IO::ReadResult::Pending == BufferPopulationResult)
							{
								if (0 < OutputBytesWritten)
								{
									CopyIntoHistoryBuffer(&TargetSpan.GetData()[TargetSpanReadPosition], OutputBytesWritten - TargetSpanReadPosition);

									return Elysium::Core::Template::IO::ReadResult::HasData;
								}

								return Elysium::Core::Template::IO::ReadResult::Pending;
							}

							_CurrentLength += _BitBuffer.Read(LengthExtraBits);
						}

						if (3 > _CurrentLength || 258 < _CurrentLength)
						{	// @ToDo: length "overflow" -> invalid
							throw 1;
						}

						const Elysium::Core::Template::IO::ReadResult BufferPopulationResult = EnsureAvailableBit(_DynamicHuffmanHeader._DistanceTree._FastTableBits, SourceSpans, BytesLoadedIntoBitReader);
						if (Elysium::Core::Template::IO::ReadResult::Pending == BufferPopulationResult)
						{
							if (0 < OutputBytesWritten)
							{
								CopyIntoHistoryBuffer(&TargetSpan.GetData()[TargetSpanReadPosition], OutputBytesWritten - TargetSpanReadPosition);

								return Elysium::Core::Template::IO::ReadResult::HasData;
							}

							return Elysium::Core::Template::IO::ReadResult::Pending;
						}

						Elysium::Core::Template::System::uint64_t DistanceSymbolIndex = _BitBuffer.Peek(DeflateUtility::DistanceTreeType::_FastTableBits);
						DeflateUtility::DistanceTreeEntryType CurrentDistanceEntry = _DynamicHuffmanHeader._DistanceTree[DistanceSymbolIndex];

						const Elysium::Core::Template::System::size DistanceIndex = CurrentDistanceEntry._Symbol;
						const Elysium::Core::Template::System::uint16_t DistanceBase = _LZ77DistanceBase[DistanceIndex];
						const Elysium::Core::Template::System::uint16_t DistanceExtraBits = _LZ77DistanceExtra[DistanceIndex];

						_BitBuffer.Consume(CurrentDistanceEntry._Length);

						_CurrentDistance = DistanceBase;
						if (0 < DistanceExtraBits)
						{
							const Elysium::Core::Template::IO::ReadResult BufferPopulationResult = EnsureAvailableBit(DistanceExtraBits, SourceSpans, BytesLoadedIntoBitReader);
							if (Elysium::Core::Template::IO::ReadResult::Pending == BufferPopulationResult)
							{
								if (0 < OutputBytesWritten)
								{
									CopyIntoHistoryBuffer(&TargetSpan.GetData()[TargetSpanReadPosition], OutputBytesWritten - TargetSpanReadPosition);

									return Elysium::Core::Template::IO::ReadResult::HasData;
								}

								return Elysium::Core::Template::IO::ReadResult::Pending;
							}

							_CurrentDistance += _BitBuffer.Read(DistanceExtraBits);
						}

						if (1 > _CurrentDistance || 258 < _CurrentDistance)
						{	// @ToDo: distance "overflow" -> invalid
							throw 1;
						}
					}

					TargetSpanReadPosition += CopyIntoHistoryBuffer(&TargetSpan.GetData()[TargetSpanReadPosition], OutputBytesWritten - TargetSpanReadPosition);

					// early exit -> keep states alive
					if (TargetSpan.GetLength() <= OutputBytesWritten + _CurrentLength)
					{
						const Elysium::Core::Template::System::size Length = OutputBytesWritten - TargetSpanReadPosition;
						CopyIntoHistoryBuffer(&TargetSpan.GetData()[TargetSpanReadPosition], Length);

						return 0 == Length ? Elysium::Core::Template::IO::ReadResult::Pending : Elysium::Core::Template::IO::ReadResult::HasData;
					}

					// @ToDo: optimize byte-by-byte copy
					Elysium::Core::Template::System::byte CopiedSymbol;
					Elysium::Core::Template::System::size Start = _LZ77HistoryBuffer.GetTail() - _CurrentDistance;
					for (Elysium::Core::Template::System::uint16_t i = 0; i < _CurrentLength; ++i)
					{
						CopiedSymbol = _LZ77HistoryBuffer[(Start + i) % _LZ77HistoryBuffer.GetCapacity()];

						_LZ77HistoryBuffer.Push(&CopiedSymbol, 1);
						TargetSpan.GetData()[OutputBytesWritten++] = CopiedSymbol;
						++TargetSpanReadPosition;
					}

					_CurrentLiteralEntry = _InvalidLiteralEntry;
					_CurrentLength = 0;
					_CurrentDistance = 0;
				}
				else
				{	// @ToDo: illegal symbol
					throw 1;
				}
			}

			return Elysium::Core::Template::IO::ReadResult::HasData;
		}
	private:
		inline const Elysium::Core::Template::IO::ReadResult EnsureAvailableBit(const Elysium::Core::Template::System::size Bits,
			const Elysium::Core::Template::Container::View::MultiSpan<Elysium::Core::Template::System::byte, 1024, 2> SourceSpans,
			Elysium::Core::Template::System::size& BytesLoadedIntoBitReader)
		{
			if (_BitBuffer.HasBits(Bits))
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
				const Elysium::Core::Template::System::size AvailableBytes0 = (BitBuffer<true>::Capacity - _BitBuffer.GetLength()) / 8;
				const Elysium::Core::Template::System::size BytesToCopy0 = Elysium::Core::Template::Math::Min(Length0, AvailableBytes0);

				// @ToDo: can I optimize a byte-by-byte push? (for instance: if there are 32 bit left, I could push one single 32 bit integer and possibly make it faster?)
				for (Elysium::Core::Template::System::size i = 0; i < BytesToCopy0; ++i)
				{
					_BitBuffer.Push(Data0[i]);
				}
				BytesLoadedIntoBitReader += BytesToCopy0;
			}

			if (!_BitBuffer.GetIsFull() && BytesLoadedIntoBitReader >= ReadableSpan0Length)
			{
				const Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> ReadableSpan1 = SourceSpans.GetSecond();
				const Elysium::Core::Template::System::size ReadableSpan1Length = ReadableSpan1.GetLength();

				const Elysium::Core::Template::System::size Offset1 = BytesLoadedIntoBitReader - ReadableSpan0Length;

				if (Offset1 < ReadableSpan1Length)
				{
					const Elysium::Core::Template::System::byte* Data1 = &ReadableSpan1.GetData()[Offset1];
					const Elysium::Core::Template::System::size Length1 = Elysium::Core::Template::Math::Min(8_ui64, ReadableSpan1.GetLength() - Offset1);

					// @ToDo: same possible optimization of byte-by-byte push
					const Elysium::Core::Template::System::size AvailableBytes1 = (BitBuffer<true>::Capacity - _BitBuffer.GetLength()) / 8;
					const Elysium::Core::Template::System::size BytesToCopy1 = Elysium::Core::Template::Math::Min(Length1, AvailableBytes1);
					for (Elysium::Core::Template::System::size i = 0; i < BytesToCopy1; ++i)
					{
						_BitBuffer.Push(Data1[i]);
					}
					BytesLoadedIntoBitReader += BytesToCopy1;
				}
			}

			if (!_BitBuffer.HasBits(Bits))
			{
				return Elysium::Core::Template::IO::ReadResult::Pending;
			}

			return Elysium::Core::Template::IO::ReadResult::HasData;
		}

		inline Elysium::Core::Template::System::size CopyIntoHistoryBuffer(Elysium::Core::Template::System::byte* Data, Elysium::Core::Template::System::size Length)
		{
			if (0 == Length)
			{	// @ToDo: if possible (ie. move the check only to where necessary) , make sure this doesn't happen
				return 0;
			}

			_LZ77HistoryBuffer.Push(Data, Length);

			return Length;
		}
	private:
		struct UncompressedBlockInfo
		{
			Elysium::Core::Template::System::uint16_t _Length;
			Elysium::Core::Template::System::uint16_t _ComplementaryLength;

			Elysium::Core::Template::System::uint16_t _TotalBytesCopied;
		};

		struct FixedHuffmanInfo
		{
			/*
			LiteralTreeType _LiteralTree;
			DistanceTreeType _DistanceTree;
			*/
		};

		struct DynamicHuffmanInfo
		{
			// header
			Elysium::Core::Template::System::uint64_t HLIT;
			Elysium::Core::Template::System::uint64_t HDIST;
			Elysium::Core::Template::System::uint64_t HCLEN;

			// code length tree
			DeflateUtility::CodeLengthTreeType _CodeLengthTree;

			// literal and distance trees as well as their current "reading" states
			Elysium::Core::Template::System::uint16_t _CurrentLiteralAndDistanceTreeIndex = 0;
			Elysium::Core::Template::System::uint8_t _CurrentLiteralAndDistanceTreePreviousLength{ };

			DeflateUtility::LiteralTreeType _LiteralTree;
			DeflateUtility::DistanceTreeType _DistanceTree;
		};
		/*
		union BlockInfo
		{
			UncompressedBlockInfo Stored;
			FixedHuffmanInfo Fixed;
			DynamicHuffmanInfo Dynamic;
		};
		*/
	private:
		//inline static constexpr LiteralTreeEntryType _IllegalEntry = LiteralTreeEntryType(286, 0_ui8);	// is this a vs bug?
		inline static DeflateUtility::LiteralTreeEntryType _InvalidLiteralEntry{ 286_ui16, 0_ui8 };

		inline static constexpr Elysium::Core::Template::System::uint16_t _LZ77LengthBase[29] =
		{
			3, 4, 5, 6, 7, 8, 9, 10,
			11, 13, 15, 17,
			19, 23, 27, 31,
			35, 43, 51, 59,
			67, 83, 99, 115,
			131, 163, 195, 227,
			258
		};

		inline static constexpr Elysium::Core::Template::System::uint16_t _LZ77LengthExtra[29] =
		{
			0, 0, 0, 0, 0, 0, 0, 0,
			1, 1, 1, 1,
			2, 2, 2, 2,
			3, 3, 3, 3,
			4, 4, 4, 4,
			5, 5, 5, 5,
			0
		};

		inline static constexpr Elysium::Core::Template::System::uint16_t _LZ77DistanceBase[30] =
		{
			1,     2,     3,     4,
			5,     7,     9,     13,
			17,    25,    33,    49,
			65,    97,    129,   193,
			257,   385,   513,   769,
			1025,  1537,  2049,  3073,
			4097,  6145,  8193,  12289,
			16385, 24577
		};

		inline static constexpr Elysium::Core::Template::System::uint16_t _LZ77DistanceExtra[30] =
		{
			0, 0, 0, 0,
			1, 1,
			2, 2,
			3, 3,
			4, 4,
			5, 5,
			6, 6,
			7, 7,
			8, 8,
			9, 9,
			10, 10,
			11, 11,
			12, 12,
			13, 13
		};
	private:
		Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState _State;

		Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockHeader _BlockHeader;

		Elysium::Core::Template::IO::BitBuffer<true> _BitBuffer;

		UncompressedBlockInfo _UncompressedHuffmanHeader;
		DynamicHuffmanInfo _DynamicHuffmanHeader;

		DeflateUtility::LiteralTreeEntryType _CurrentLiteralEntry;
		Elysium::Core::Template::System::uint16_t _CurrentLength;
		Elysium::Core::Template::System::uint16_t _CurrentDistance;

		Elysium::Core::Template::Container::SlidingWindow<Elysium::Core::Template::System::byte> _LZ77HistoryBuffer;
		Elysium::Core::Template::System::size _LZ77HistoryBufferReadPosition;
		Elysium::Core::Template::System::uint16_t _Distance;
		Elysium::Core::Template::System::uint16_t _Length;
	};
}
#endif
