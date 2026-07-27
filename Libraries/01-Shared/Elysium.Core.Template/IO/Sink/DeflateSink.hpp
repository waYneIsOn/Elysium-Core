/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_SINK_DEFLATESINK
#define ELYSIUM_CORE_TEMPLATE_IO_SINK_DEFLATESINK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_BITBUFFER
#include "../../Container/BitBuffer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_FIXEDSIZEBUFFER
#include "../../Container/FixedSizeBuffer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_ALGORITHM_DEFLATE_DEFLATECOMPRESSIONLEVEL
#include "../../IO/Compression/Algorithm/Deflate/DeflateCompressionLevel.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_ALGORITHM_DEFLATE_DEFLATEUTILITY
#include "../../IO/Compression/Algorithm/Deflate/DeflateUtility.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_ALGORITHM_DEFLATE_DEFLATEUTILITY
#include "../../IO/Compression/Algorithm/Deflate/DeflateUtility.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_ALGORITHM_HUFFMANCODING_HUFFMANFREQUENCYTABLE
#include "../../IO/Compression/Algorithm/HuffmanCoding/HuffmanFrequencyTable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_ALGORITHM_LEMPELZIV_LZ77TOKEN
#include "../../IO/Compression/Algorithm/LempelZiv/LZ77Token.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_ALGORITHM_LEMPELZIV_LZ77UTILITY
#include "../../IO/Compression/Algorithm/LempelZiv/LZ77Utility.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_DEFLATE_DEFLATEBLOCKTYPE
#include "../../IO/Compression/Format/Deflate/DeflateBlockType.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_HUFFMANCODING_HUFFMANTABLE
#include "../../IO/Compression/Format/HuffmanCoding/HuffmanTable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_MIN
#include "../../Math/Min.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMCPY
#include "../../Memory/MemCpy.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Sink
{
	// @ToDo: concept for sinks!
	template <class InnerSink>
	class DeflateSink
	{
	public:
		using DeviceType = InnerSink::DeviceType;
	private:
		using SymbolType = Elysium::Core::Template::System::byte;

		using LZ77TokenType = Elysium::Core::Template::IO::Compression::Algorithm::LempelZiv::LZ77Utility<SymbolType>::TokenType;
	public:
		inline constexpr DeflateSink(InnerSink& InnerSink, const Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateCompressionLevel CompressionLevel) noexcept
			: _InnerSink(InnerSink), _CompressionLevel(CompressionLevel),
			_BlockBuffer(Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::MaximumUncompressedBlockLength), _BlockWritePosition{}, _BitBuffer()//, _LZ77HistoryBuffer(DeflateUtility::LZ77HistoryBufferSize)
		{ }

		constexpr DeflateSink(const DeflateSink& Source) = delete;

		constexpr DeflateSink(DeflateSink&& Right) noexcept = delete;

		inline ~DeflateSink()
		{
			Finish();
		}
	public:
		constexpr DeflateSink& operator=(const DeflateSink& Source) = delete;

		constexpr DeflateSink& operator=(DeflateSink&& Right) noexcept = delete;
	public:
		inline constexpr const Elysium::Core::Template::System::size GetLength() const
		{
			return _InnerSink.GetLength();
		}

		inline constexpr const Elysium::Core::Template::System::uint64_t GetPosition() const
		{
			return _InnerSink.GetPosition();
		}

		inline DeviceType& GetDevice()
		{
			return _InnerSink.GetDevice();
		}

		inline constexpr const DeviceType& GetDevice() const
		{
			return _InnerSink.GetDevice();
		}
	public:
		inline void SetPosition(const Elysium::Core::Template::System::uint64_t Position)
		{
			_InnerSink.SetPosition(Position);
		}
	public:
		inline void Write(const Elysium::Core::Template::System::byte* Buffer, Elysium::Core::Template::System::size Count)
		{
			//constexpr Elysium::Core::Template::System::size Limit = 32 * 1024;
			//constexpr Elysium::Core::Template::System::size Limit = 4 * 1024;
			//constexpr Elysium::Core::Template::System::size Limit = 123;
			constexpr Elysium::Core::Template::System::size Limit = Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::MaximumUncompressedBlockLength;

			while (Count > 0)
			{
				assert(_BlockWritePosition <= Limit);
				Elysium::Core::Template::System::size BytesToCopy = Elysium::Core::Template::Math::Min(Count, Limit - _BlockWritePosition);
				assert(BytesToCopy > 0);
				assert(BytesToCopy <= Count);
				assert(BytesToCopy <= Limit - _BlockWritePosition);

				Elysium::Core::Template::Memory::MemCpy(&_BlockBuffer[_BlockWritePosition], Buffer, BytesToCopy);
				Buffer += BytesToCopy;
				Count -= BytesToCopy;

				_BlockWritePosition += BytesToCopy;

				if (_BlockWritePosition == Limit)
				{
					WriteBufferedBlock(false);
				}
			}
		}

		inline void Finish()
		{
			WriteBufferedBlock(true);
			Flush();

			if constexpr (requires { _InnerSink.Finish(); })
			{
				_InnerSink.Finish();
			}
		}

		inline void Flush()
		{
			if constexpr (requires { _InnerSink.Flush(); })
			{
				_InnerSink.Flush();
			}
		}
	private:
		inline void WriteBufferedBlock(const bool IsFinalBlock)
		{
			if ((0 == _BlockWritePosition && !IsFinalBlock) || _HasWrittenFinalBlock)
			{
				return;
			}

			switch (_CompressionLevel)
			{
			case Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateCompressionLevel::Stored:
				WriteUncompressedBlock(IsFinalBlock);
				break;
			case Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateCompressionLevel::StaticOnly:
				WriteStaticBlock(IsFinalBlock);
				break;
			case Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateCompressionLevel::DynamicOnly:
				WriteDynamicBlock(IsFinalBlock);
				break;
			case Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateCompressionLevel::SelectOptimal:
				WriteBlock(IsFinalBlock);
				break;
			default:
				// @ToDo
				throw 1;
			}

			if (IsFinalBlock)
			{
				_HasWrittenFinalBlock = true;
			}
		}

		inline void WriteUncompressedBlock(const bool IsFinalBlock)
		{
			const Elysium::Core::Template::System::uint16_t ComplementLength = ~_BlockWritePosition;

			Elysium::Core::Template::System::byte DeflateHeader = 0x00;
			DeflateHeader |= IsFinalBlock;
			DeflateHeader |= static_cast<Elysium::Core::Template::System::byte>(Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockType::Uncompressed) << 1;

			_InnerSink.Write(&DeflateHeader, 1);
			_InnerSink.Write(reinterpret_cast<const Elysium::Core::Template::System::byte*>(&_BlockWritePosition), sizeof(Elysium::Core::Template::System::uint16_t));
			_InnerSink.Write(reinterpret_cast<const Elysium::Core::Template::System::byte*>(&ComplementLength), sizeof(Elysium::Core::Template::System::uint16_t));
			_InnerSink.Write(&_BlockBuffer[0], _BlockWritePosition);

			_BlockWritePosition = 0;
		}

		inline void WriteStaticBlock(const bool IsFinalBlock)
		{
			static constexpr Elysium::Core::Template::System::uint16_t EOBCanonicalCode =
				Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::StaticLiteralTree._CanonicalCodes[256];
			static constexpr Elysium::Core::Template::System::uint8_t EOBLength =
				Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::StaticLiteralTree._CodeLengths[256];

			Elysium::Core::Template::System::byte DeflateHeader = 0x00;
			DeflateHeader |= IsFinalBlock;
			DeflateHeader |= static_cast<Elysium::Core::Template::System::byte>(Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockType::FixedHuffman) << 1;
			
			WriteBits(DeflateHeader, 3);

			// @ToDo: sliding windows in deflate afaik can "persist" over multiple blocks.
			// If that is in fact the case, the LZ77Utility instance obviously can be a member of DeflateSink and doesn't need to be "recreated" every block.
			// It would certainly improve compression rate.
			Elysium::Core::Template::IO::Compression::Algorithm::LempelZiv::LZ77Utility<SymbolType> LZ77Utility;
			Elysium::Core::Template::Container::Vector<LZ77TokenType> Tokens = LZ77Utility.Decode(&_BlockBuffer[0], _BlockWritePosition);

			for (Elysium::Core::Template::System::size i = 0; i < Tokens.GetLength(); ++i)
			{
				const LZ77TokenType& CurrentToken = Tokens[i];
				if (0 < CurrentToken._Length)
				{
					const Elysium::Core::Template::System::uint8_t LengthIndex = 
						Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::LZ77LengthToSymbol[CurrentToken._Length];

					const Elysium::Core::Template::System::uint16_t LengthSymbol = 257 + LengthIndex;
					const Elysium::Core::Template::System::uint16_t LengthCanonicalCode =
						Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::StaticLiteralTree._CanonicalCodes[LengthSymbol];
					const Elysium::Core::Template::System::uint8_t LengthLength =
						Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::StaticLiteralTree._CodeLengths[LengthSymbol];

					WriteBits(LengthCanonicalCode, LengthLength);

					const Elysium::Core::Template::System::uint16_t LengthBase =
						Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::LZ77LengthBase[LengthIndex];
					const Elysium::Core::Template::System::uint16_t LengthExtra =
						Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::LZ77LengthExtra[LengthIndex];

					WriteBits(CurrentToken._Length - LengthBase, LengthExtra);

					// @ToDo: optimize the linear lookup (a table like "LZ77LengthToSymbol" would allocate 32kb of static data!)
					Elysium::Core::Template::System::uint8_t DistanceIndex = 0;
					while (DistanceIndex < 29 && CurrentToken._Distance >= Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::LZ77DistanceBase[DistanceIndex + 1])
					{
						++DistanceIndex;
					}
					const Elysium::Core::Template::System::uint16_t DistanceCanonicalCode =
						Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::StaticDistanceTree._CanonicalCodes[DistanceIndex];
					const Elysium::Core::Template::System::uint8_t DistanceLength =
						Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::StaticDistanceTree._CodeLengths[DistanceIndex];

					WriteBits(DistanceCanonicalCode, DistanceLength);

					const Elysium::Core::Template::System::uint16_t DistanceBase =
						Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::LZ77DistanceBase[DistanceIndex];
					const Elysium::Core::Template::System::uint16_t DistanceExtra =
						Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::LZ77DistanceExtra[DistanceIndex];

					WriteBits(CurrentToken._Distance - DistanceBase, DistanceExtra);
				}
				else
				{
					const Elysium::Core::Template::System::uint16_t CanonicalCode = 
						Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::StaticLiteralTree._CanonicalCodes[CurrentToken._Literal];
					const Elysium::Core::Template::System::uint8_t Length =
						Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::StaticLiteralTree._CodeLengths[CurrentToken._Literal];
					
					WriteBits(CanonicalCode, Length);
				}
			}

			WriteBits(EOBCanonicalCode, EOBLength);
			
			if (IsFinalBlock)
			{
				FlushFinalBits();
			}

			_BlockWritePosition = 0;
		}

		inline void WriteDynamicBlock(const bool IsFinalBlock)
		{
			// 1.) produce LZ77 tokens
			Elysium::Core::Template::IO::Compression::Algorithm::LempelZiv::LZ77Utility<SymbolType> LZ77Utility;
			Elysium::Core::Template::Container::Vector<LZ77TokenType> Tokens = LZ77Utility.Decode(&_BlockBuffer[0], _BlockWritePosition);

			// 2.) count frequencies (of literals AND distances)
			Elysium::Core::Template::IO::Compression::Algorithm::HuffmanCoding::HuffmanFrequencyTable<SymbolType, Elysium::Core::Template::System::size, 256> LiteralFrequencies{};
			Elysium::Core::Template::IO::Compression::Algorithm::HuffmanCoding::HuffmanFrequencyTable<SymbolType, Elysium::Core::Template::System::size, 32> DistanceFrequencies{};
			for (Elysium::Core::Template::System::size i = 0; i < Tokens.GetLength(); ++i)
			{
				const LZ77TokenType& CurrentToken = Tokens[i];
				if (0 == CurrentToken._Length)
				{
					LiteralFrequencies.Increment(CurrentToken._Literal);
				}
				else
				{
					DistanceFrequencies.Increment(CurrentToken._Distance);
				}
			}
			
			// 3.) build literal- and distance-tables
			Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::LiteralTreeType LiteralTree{};
			Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::DistanceTreeType DistanceTree{};

			//LiteralTree._CodeLengths = 

			// 4.) convert tables into canonical code lengths

			// 5.) compress code lengths using run-length encoding

			// 6.) build code-length lengths table
			Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::CodeLengthTreeType CodeLengthTree{};

			// 7.) write block header and all three table descriptors
			Elysium::Core::Template::System::byte DeflateHeader = 0x00;
			DeflateHeader |= IsFinalBlock;
			DeflateHeader |= static_cast<Elysium::Core::Template::System::byte>(Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockType::DynamicHuffman) << 1;

			WriteBits(DeflateHeader, 3);

			// 8.) encode lz77-tokens using the first two tables
			
			throw 1;
		}

		inline void WriteBlock(const bool IsFinalBlock)
		{
			throw 1;
		}
	private:
		inline void WriteBits(const Elysium::Core::Template::System::uint64_t Bits, const Elysium::Core::Template::System::uint8_t Length)
		{
			if (0 == Length)
			{	// can happen with length and distance lengths!
				return;
			}

			const Elysium::Core::Template::System::uint8_t AvailableBits = _BitBuffer.GetLength();
			if (AvailableBits + Length > _BitBuffer.Capacity)
			{
				const Elysium::Core::Template::System::uint8_t BitsToCopy = AvailableBits & ~7;
				const Elysium::Core::Template::System::uint64_t Value = _BitBuffer.Read(BitsToCopy);

				const Elysium::Core::Template::System::size BytesToCopy = BitsToCopy / 8;
				_InnerSink.Write(reinterpret_cast<const Elysium::Core::Template::System::byte*>(&Value), BytesToCopy);
			}

			_BitBuffer.Push(Bits, Length);
		}

		inline void FlushFinalBits()
		{
			const Elysium::Core::Template::System::uint8_t AvailableBits = _BitBuffer.GetLength();
			if (0 == AvailableBits)
			{
				return;
			}

			const Elysium::Core::Template::System::uint64_t Value = _BitBuffer.Read(AvailableBits);

			const Elysium::Core::Template::System::size BytesToCopy = (AvailableBits + 7) / 8;
			_InnerSink.Write(reinterpret_cast<const Elysium::Core::Template::System::byte*>(&Value), BytesToCopy);
		}
	private:
		InnerSink& _InnerSink;

		Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateCompressionLevel _CompressionLevel;

		Elysium::Core::Template::Container::FixedSizeBuffer<Elysium::Core::Template::System::byte> _BlockBuffer;
		Elysium::Core::Template::System::size _BlockWritePosition;

		Elysium::Core::Template::Container::BitBuffer<> _BitBuffer;

		bool _HasWrittenFinalBlock = false;
	};
}
#endif
