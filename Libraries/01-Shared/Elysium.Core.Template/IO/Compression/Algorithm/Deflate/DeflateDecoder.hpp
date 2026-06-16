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
				case  Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::ReadingDynamicCodeLengthAlphabet:
				{
					const Elysium::Core::Template::IO::ReadResult Result = ReadDynamicHuffmanCodeLengthAlphabet(SourceSpans, BytesFullyProcessed);
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

			_State = Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::ReadingDynamicCodeLengthAlphabet;

			return Elysium::Core::Template::IO::ReadResult::HasData;
		}

		inline const Elysium::Core::Template::IO::ReadResult ReadDynamicHuffmanCodeLengthAlphabet(const Elysium::Core::Template::Container::View::MultiSpan<Elysium::Core::Template::System::byte, 1024, 2> SourceSpans,
			Elysium::Core::Template::System::size& BytesLoadedIntoBitReader)
		{
			static constexpr const Elysium::Core::Template::System::uint8_t FixedPermutations[19] =
			{
				16, 17, 18,
				0, 8, 7, 9, 6, 10, 5,
				11, 4, 12, 3, 13, 2, 14, 1, 15
			};
			static constexpr const Elysium::Core::Template::System::size BitsRequiredPerEntry = 3;

			const Elysium::Core::Template::System::size BitsRequiredInTotal = BitsRequiredPerEntry * _DynamicHuffmanHeader.HCLEN;
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

			bool AllValuesAreZero = true;
			Elysium::Core::Template::System::uint8_t CodeLengths[19]{};
			for (int i = 0; i < _DynamicHuffmanHeader.HCLEN; ++i)
			{
				Elysium::Core::Template::System::uint64_t CurrentValue = _BitReader.Read(3);
			
				// 3 bits -> maximum 0b111 = 7 BUT BitReader returns a 64bit integer so if the implementation is not correct, this might still result in a bug!!!
				if (CurrentValue > 7)
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








			return Elysium::Core::Template::IO::ReadResult::HasData;
		}
	private:
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

			// length alphabet - doesn't need to be stored, only the tree created from it!

			// code-length huffman tree
			//HuffmanTable _CodeLengthTable;

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
