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

#ifndef ELYSIUM_CORE_TEMPLATE_ALGORITHMS_SORTING_SORT
#include "../../Algorithms/Sorting/Sort.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_DEFLATE_DEFLATEBLOCKTYPE
#include "../../IO/Compression/Format/Deflate/DeflateBlockType.hpp"
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
			_BlockBuffer(Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::MaximumUncompressedBlockLength), _BlockWritePosition{}, _LZ77Utility{}, _BitBuffer()
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
			constexpr Elysium::Core::Template::System::size Limit = 32 * 1024 - 2;
			//constexpr Elysium::Core::Template::System::size Limit = 4 * 1024;
			//constexpr Elysium::Core::Template::System::size Limit = 123;
			//constexpr Elysium::Core::Template::System::size Limit = Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::MaximumUncompressedBlockLength;
			//constexpr Elysium::Core::Template::System::size Limit = Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::MaximumUncompressedBlockLength - 10;

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
		struct Node 
		{
			Elysium::Core::Template::System::uint16_t _Symbol;
			Elysium::Core::Template::System::size _Frequency;

			Elysium::Core::Template::System::int32_t _ParentIndex;
		};

		struct NodeComparison
		{
			inline constexpr bool operator()(const Node& Left, const Node& Right) const
			{
				if (Left._Frequency == Right._Frequency)
				{
					return Left._Symbol > Right._Symbol;
				}

				return Left._Frequency > Right._Frequency;
			}
		};
	private:
		inline void WriteBufferedBlock(const bool IsFinalBlock)
		{
			if ((0 == _BlockWritePosition && !IsFinalBlock) || _HasWrittenFinalBlock)
			{
				return;
			}

#ifdef _DEBUG
			++_BlockCount;
#endif
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

			Elysium::Core::Template::Container::Vector<LZ77TokenType> Tokens = _LZ77Utility.Encode(&_BlockBuffer[0], _BlockWritePosition);

			Elysium::Core::Template::System::byte DeflateHeader = 0x00;
			DeflateHeader |= IsFinalBlock;
			DeflateHeader |= static_cast<Elysium::Core::Template::System::byte>(Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockType::FixedHuffman) << 1;
			
			WriteBits(DeflateHeader, 3);
			
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

					const Elysium::Core::Template::System::uint8_t DistanceIndex = 
						Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::LZ77DistanceToSymbol[CurrentToken._Distance];
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
			Elysium::Core::Template::Container::Vector<LZ77TokenType> Tokens = _LZ77Utility.Encode(&_BlockBuffer[0], _BlockWritePosition);

			// ...
			bool HasIncrementedDistances = false;
			Elysium::Core::Template::IO::Compression::Algorithm::HuffmanCoding::HuffmanFrequencyTable<Elysium::Core::Template::System::uint16_t,
				Elysium::Core::Template::System::size, 288> LiteralLengthFrequencies{};
			Elysium::Core::Template::IO::Compression::Algorithm::HuffmanCoding::HuffmanFrequencyTable<SymbolType, Elysium::Core::Template::System::size, 32> DistanceFrequencies{};
			for (Elysium::Core::Template::System::size i = 0; i < Tokens.GetLength(); ++i)
			{
				const LZ77TokenType& CurrentToken = Tokens[i];
				if (0 == CurrentToken._Length)
				{
					LiteralLengthFrequencies.Increment(CurrentToken._Literal);
				}
				else
				{
					const Elysium::Core::Template::System::uint8_t LengthIndex =
						Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::LZ77LengthToSymbol[CurrentToken._Length];
					const Elysium::Core::Template::System::uint16_t LengthSymbol = 257 + LengthIndex;
					LiteralLengthFrequencies.Increment(LengthSymbol);
					
					const Elysium::Core::Template::System::uint8_t DistanceIndex = 
						Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::LZ77DistanceToSymbol[CurrentToken._Distance];
					const SymbolType DistanceSymbol = DistanceIndex;
					DistanceFrequencies.Increment(DistanceSymbol);
					
					HasIncrementedDistances = true;
				}
			}
			LiteralLengthFrequencies.Increment(256);	// EOB is required
			if (!HasIncrementedDistances)
			{
				DistanceFrequencies.Increment(0);	// at least one distance is required by DEFLATE
			}

			if (0 < LiteralLengthFrequencies[286] || 0 < LiteralLengthFrequencies[287] || 0 < DistanceFrequencies[30] || 0 < DistanceFrequencies[31])
			{	// ToDo: throw specific exception. these are unused in deflate!!!
				throw 1;
			}

			// ...
			Elysium::Core::Template::Container::Vector<Node> LiteralLengthNodes(LiteralLengthFrequencies.GetAlphabetLength() / 2);
			LiteralLengthNodes.Clear();
			for (Elysium::Core::Template::System::size i = 0; i < LiteralLengthFrequencies.GetAlphabetLength(); ++i)
			{
				const Elysium::Core::Template::System::size Frequency = LiteralLengthFrequencies[i];
				if (0 < Frequency)
				{
					LiteralLengthNodes.PushBack({ static_cast<Elysium::Core::Template::System::uint16_t>(i), Frequency, -1 });
				}
			}
			const Elysium::Core::Template::System::size LiteralLength = LiteralLengthNodes.GetLength();

			Elysium::Core::Template::Container::Vector<Node> DistanceNodes(DistanceFrequencies.GetAlphabetLength() / 2);
			DistanceNodes.Clear();
			for (Elysium::Core::Template::System::size i = 0; i < DistanceFrequencies.GetAlphabetLength(); ++i)
			{
				const Elysium::Core::Template::System::size Frequency = DistanceFrequencies[i];
				if (0 < Frequency)
				{
					DistanceNodes.PushBack({ static_cast<SymbolType>(i), Frequency, -1 });
				}
			}
			const Elysium::Core::Template::System::size DistanceLength = DistanceNodes.GetLength();

			// ...
			BuildNodeTree(LiteralLengthNodes);
			BuildNodeTree(DistanceNodes);

			// ...
			Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::LiteralTreeType LiteralLengthTree{};
			for (Elysium::Core::Template::System::size i = 0; i < LiteralLength; ++i)
			{
				Elysium::Core::Template::System::uint8_t Depth = 0;
				Elysium::Core::Template::System::size CurrentIndex = i;

				while (LiteralLengthNodes[CurrentIndex]._ParentIndex != -1)
				{
					++Depth;
					CurrentIndex = LiteralLengthNodes[CurrentIndex]._ParentIndex;
				}

				if (LiteralLengthTree._MaximumCodeLength < Depth)
				{	// @ToDo: package merge
					throw 1;
				}

				LiteralLengthTree._CodeLengths[LiteralLengthNodes[i]._Symbol] = Depth;
			}

			if (1 == LiteralLength)
			{
				LiteralLengthTree._CodeLengths[LiteralLengthNodes[0]._Symbol] = 1;
			}

			Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::DistanceTreeType DistanceTree{};
			for (Elysium::Core::Template::System::size i = 0; i < DistanceLength; ++i)
			{
				Elysium::Core::Template::System::uint8_t Depth = 0;
				Elysium::Core::Template::System::size CurrentIndex = i;

				while (DistanceNodes[CurrentIndex]._ParentIndex != -1)
				{
					++Depth;
					CurrentIndex = DistanceNodes[CurrentIndex]._ParentIndex;
				}

				if (DistanceTree._MaximumCodeLength < Depth)
				{	// @ToDo: package merge
					throw 1;
				}

				DistanceTree._CodeLengths[DistanceNodes[i]._Symbol] = Depth;
			}

			if (1 == DistanceLength)
			{
				DistanceTree._CodeLengths[DistanceNodes[0]._Symbol] = 1;
			}

			LiteralLengthTree.BuildCanonicalCodes(); 
			DistanceTree.BuildCanonicalCodes();

			// ...
			Elysium::Core::Template::System::size LiteralLengthWithoutTrailingZeroes = 286;
			while (257 < LiteralLengthWithoutTrailingZeroes && 0 == LiteralLengthTree._CodeLengths[LiteralLengthWithoutTrailingZeroes - 1])
			{
				--LiteralLengthWithoutTrailingZeroes;
			}

			Elysium::Core::Template::System::uint8_t DistanceLengthWithoutTrailingZeroes = 30;
			while (1 < DistanceLengthWithoutTrailingZeroes && 0 == DistanceTree._CodeLengths[DistanceLengthWithoutTrailingZeroes - 1])
			{
				--DistanceLengthWithoutTrailingZeroes;
			}

			Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::uint8_t> Lengths(LiteralLengthWithoutTrailingZeroes + DistanceLengthWithoutTrailingZeroes);
			for (Elysium::Core::Template::System::size i = 0; i < LiteralLengthWithoutTrailingZeroes; ++i)
			{
				Lengths[i] = LiteralLengthTree._CodeLengths[i];
			}
			for (Elysium::Core::Template::System::size i = 0; i < DistanceLengthWithoutTrailingZeroes; ++i)
			{
				Lengths[LiteralLengthWithoutTrailingZeroes + i] = DistanceTree._CodeLengths[i];
			}

			const Elysium::Core::Template::System::uint8_t HLIT = static_cast<Elysium::Core::Template::System::uint8_t>(LiteralLengthWithoutTrailingZeroes - 
				Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::HLITAddition);
			const Elysium::Core::Template::System::uint8_t HDIST = DistanceLengthWithoutTrailingZeroes - 
				Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::HDISTAddition;

			// RLE encoding
			Elysium::Core::Template::IO::Compression::Algorithm::HuffmanCoding::HuffmanFrequencyTable<SymbolType, Elysium::Core::Template::System::size, 19> CodeLengthFrequencies{};
			Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::uint8_t> CodeLengthSymbols{};
			Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::uint8_t> CodeLengthExtraValues{};
			const Elysium::Core::Template::System::size LengthsLength = Lengths.GetLength();
			Elysium::Core::Template::System::size i = 0;
			while (i < LengthsLength)
			{
				Elysium::Core::Template::System::uint8_t CurrentLength = Lengths[i];

				Elysium::Core::Template::System::size RunLength = 1;
				while (i + RunLength < LengthsLength && CurrentLength == Lengths[i + RunLength])
				{
					++RunLength;
				}

				const Elysium::Core::Template::System::size OriginalRunLength = RunLength;

				if (0 == CurrentLength)
				{	// Special case: unused symbol! -> 0, 17 or 18
					while (RunLength >= 11)
					{
						Elysium::Core::Template::System::size RepeatCount = (RunLength > 138) ? 138 : RunLength;

						CodeLengthFrequencies.Increment(18);
						CodeLengthSymbols.PushBack(18);

						CodeLengthExtraValues.PushBack(static_cast<uint8_t>(RepeatCount - 11));

						RunLength -= RepeatCount;
					}

					if (RunLength >= 3)
					{
						CodeLengthFrequencies.Increment(17);
						CodeLengthSymbols.PushBack(17);

						CodeLengthExtraValues.PushBack(static_cast<uint8_t>(RunLength - 3));

						RunLength = 0;
					}

					while (RunLength > 0)
					{
						CodeLengthFrequencies.Increment(0);
						CodeLengthSymbols.PushBack(0);

						--RunLength;
					}
				}
				else
				{	// 0 - 15 and sometimes 16
					CodeLengthFrequencies.Increment(CurrentLength);
					CodeLengthSymbols.PushBack(CurrentLength);

					--RunLength;

					if (0 == CurrentLength)
					{
						throw 1;
					}

					while (RunLength >= 3)
					{
						Elysium::Core::Template::System::size RepeatCount = (RunLength > 6) ? 6 : RunLength;

						CodeLengthFrequencies.Increment(16);
						CodeLengthSymbols.PushBack(16);

						CodeLengthExtraValues.PushBack(static_cast<Elysium::Core::Template::System::uint8_t>(RepeatCount - 3));

						RunLength -= RepeatCount;
					}

					while (RunLength > 0)
					{	// remaninig 0-2
						CodeLengthFrequencies.Increment(CurrentLength);
						CodeLengthSymbols.PushBack(CurrentLength);

						--RunLength;
					}
				}

				i += OriginalRunLength;
			}
			
			// ...
			Elysium::Core::Template::Container::Vector<Node> CodeLengthNodes(CodeLengthFrequencies.GetAlphabetLength() / 2);
			CodeLengthNodes.Clear();
			for (Elysium::Core::Template::System::size i = 0; i < CodeLengthFrequencies.GetAlphabetLength(); ++i)
			{
				const Elysium::Core::Template::System::size Frequency = CodeLengthFrequencies[i];
				if (0 < Frequency)
				{
					CodeLengthNodes.PushBack({ static_cast<Elysium::Core::Template::System::uint16_t>(i), Frequency, -1 });
				}
			}
			const Elysium::Core::Template::System::size CodeLengthLength = CodeLengthNodes.GetLength();

			BuildNodeTree(CodeLengthNodes);

			Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::CodeLengthTreeType CodeLengthsTree{};
			for (Elysium::Core::Template::System::size i = 0; i < CodeLengthLength; ++i)
			{
				Elysium::Core::Template::System::uint8_t Depth = 0;
				Elysium::Core::Template::System::size CurrentIndex = i;

				while (CodeLengthNodes[CurrentIndex]._ParentIndex != -1)
				{
					++Depth;
					CurrentIndex = CodeLengthNodes[CurrentIndex]._ParentIndex;
				}

				if (CodeLengthsTree._MaximumCodeLength < Depth)
				{	// @ToDo: package merge
					throw 1;
				}

				CodeLengthsTree._CodeLengths[CodeLengthNodes[i]._Symbol] = Depth;
			}

			if (1 == CodeLengthLength)
			{
				CodeLengthsTree._CodeLengths[CodeLengthNodes[0]._Symbol] = 1;
			}

			CodeLengthsTree.BuildCanonicalCodes();

			Elysium::Core::Template::System::uint8_t CodeLengthsLengthWithoutTrailingZeroes = 19;
			while (4 < CodeLengthsLengthWithoutTrailingZeroes && 0 == CodeLengthsTree._CodeLengths[
				Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::FixedCodeLengthPermutations[CodeLengthsLengthWithoutTrailingZeroes - 1]])
			{
				--CodeLengthsLengthWithoutTrailingZeroes;
			}

			const Elysium::Core::Template::System::uint8_t HCLEN = CodeLengthsLengthWithoutTrailingZeroes - 
				Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::HCLENAddition;
			
			// ...
			Elysium::Core::Template::System::byte DeflateHeader = 0x00;
			DeflateHeader |= IsFinalBlock;
			DeflateHeader |= static_cast<Elysium::Core::Template::System::byte>(Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockType::DynamicHuffman) << 1;

			WriteBits(DeflateHeader, 3);

			// ...
			WriteBits(HLIT, 5);
			WriteBits(HDIST, 5);
			WriteBits(HCLEN, 4);

			// ...
			for (Elysium::Core::Template::System::size i = 0; i < HCLEN + 4; ++i)
			{
				WriteBits(CodeLengthsTree._CodeLengths[Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::FixedCodeLengthPermutations[i]], 3);
			}

			// ...
			Elysium::Core::Template::System::size ExtraIndex = 0;
			size ExpandedCount = 0;
			for (Elysium::Core::Template::System::size i = 0; i < CodeLengthSymbols.GetLength(); ++i)
			{
				Elysium::Core::Template::System::uint8_t Symbol = CodeLengthSymbols[i];
				Elysium::Core::Template::System::uint16_t CanonicalCode = CodeLengthsTree._CanonicalCodes[Symbol];
				Elysium::Core::Template::System::uint8_t CodeLength = CodeLengthsTree._CodeLengths[Symbol];
				WriteBits(CanonicalCode, CodeLength);

				if (Symbol <= 15)
				{
					++ExpandedCount;
				}

				if (Symbol == 16)
				{
					ExpandedCount += CodeLengthExtraValues[ExtraIndex] + 3;

					WriteBits(CodeLengthExtraValues[ExtraIndex++], 2);
				}
				else if (Symbol == 17)
				{
					ExpandedCount += CodeLengthExtraValues[ExtraIndex] + 3;

					WriteBits(CodeLengthExtraValues[ExtraIndex++], 3);
				}
				else if (Symbol == 18)
				{
					ExpandedCount += CodeLengthExtraValues[ExtraIndex] + 11;

					WriteBits(CodeLengthExtraValues[ExtraIndex++], 7);
				}
			}

			if (ExpandedCount != LiteralLengthWithoutTrailingZeroes + DistanceLengthWithoutTrailingZeroes)
			{
				throw 1;
			}

			if (ExtraIndex != CodeLengthExtraValues.GetLength())
			{
				throw 1;
			}

			// ...
			for (Elysium::Core::Template::System::size i = 0; i < Tokens.GetLength(); ++i)
			{
				const LZ77TokenType& CurrentToken = Tokens[i];
				if (0 == CurrentToken._Length)
				{
					SymbolType Symbol = CurrentToken._Literal;
					WriteBits(LiteralLengthTree._CanonicalCodes[Symbol], LiteralLengthTree._CodeLengths[Symbol]);
				}
				else
				{	// length symbol
					Elysium::Core::Template::System::uint8_t LengthIndex = 
						Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::LZ77LengthToSymbol[CurrentToken._Length];
					Elysium::Core::Template::System::uint16_t LengthSymbol = 257 + LengthIndex;
					WriteBits(LiteralLengthTree._CanonicalCodes[LengthSymbol], LiteralLengthTree._CodeLengths[LengthSymbol]);

					// length extra bits
					Elysium::Core::Template::System::uint8_t LengthExtraBits = Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::LZ77LengthExtra[LengthIndex];
					if (LengthExtraBits != 0)
					{
						Elysium::Core::Template::System::uint16_t LengthExtraValue = CurrentToken._Length -
							Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::LZ77LengthBase[LengthIndex];
						WriteBits(LengthExtraValue, LengthExtraBits);
					}

					// distance symbol
					Elysium::Core::Template::System::uint8_t DistanceSymbol = 
						Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::LZ77DistanceToSymbol[CurrentToken._Distance];
					WriteBits(DistanceTree._CanonicalCodes[DistanceSymbol], DistanceTree._CodeLengths[DistanceSymbol]);

					// distance extra bits
					Elysium::Core::Template::System::uint8_t DistanceExtraBits = 
						Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::LZ77DistanceExtra[DistanceSymbol];
					if (DistanceExtraBits != 0)
					{
						Elysium::Core::Template::System::uint16_t DistanceExtraValue = CurrentToken._Distance -
							Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::LZ77DistanceBase[DistanceSymbol];
						WriteBits(DistanceExtraValue, DistanceExtraBits);
					}
				}
			}

			Elysium::Core::Template::System::uint16_t EOBCanonicalCode = LiteralLengthTree._CanonicalCodes[256];
			Elysium::Core::Template::System::uint8_t EOBCodeLength = LiteralLengthTree._CodeLengths[256];
			WriteBits(EOBCanonicalCode, EOBCodeLength);

			// ...
			if (IsFinalBlock)
			{
				FlushFinalBits();
			}

			_BlockWritePosition = 0;
		}

		inline void WriteBlock(const bool IsFinalBlock)
		{
			throw 1;
		}
	private:
		inline void BuildNodeTree(Elysium::Core::Template::Container::Vector<Node>& Nodes)
		{
			const Elysium::Core::Template::System::size NodesLength = Nodes.GetLength();

			// Through previous calculations all trees hold at least one entry because:
			//	- literal/length tree has EOB
			//	- distance tree has one entry if none was added
			//	- code-lengths tree based on these trees therefore cannot be empty either
			// Therefore this check is actually unnecessary! IF it happens, something else is wrong in the implementation!
			if (0 == NodesLength)
			{
				throw 1;
			}

			Nodes.Reserve(2 * NodesLength - 1);

			// sort by frequency ASCENDING!!!
			NodeComparison Comparer{};
			//Elysium::Core::Template::Algorithms::Sorting::Sort(&Nodes[0], NodesLength, Comparer);
			Elysium::Core::Template::Algorithms::Sorting::QuickSort(&Nodes[0], NodesLength, Comparer);
			
			{
				for (Elysium::Core::Template::System::size i = 1; i < NodesLength; ++i)
				{
					assert(Nodes[i - 1]._Frequency <= Nodes[i]._Frequency);
					if (Nodes[i - 1]._Frequency == Nodes[i]._Frequency)
					{
						assert(Nodes[i - 1]._Symbol <= Nodes[i]._Symbol);
					}
				}

				bool sdf = false;
			}
			
			Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::size> Queue1(NodesLength);
			Queue1.Clear();

			Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::size> Queue2(NodesLength - 1);
			Queue2.Clear();

			for (Elysium::Core::Template::System::size i = 0; i < NodesLength; ++i)
			{
				Queue1.PushBack(i);
			}

			Elysium::Core::Template::System::size Header1 = 0;
			Elysium::Core::Template::System::size Header2 = 0;

			auto PopSmallest = [&]() -> Elysium::Core::Template::System::size
				{
					if (Header1 == Queue1.GetLength())
					{
						return Queue2[Header2++];
					}

					if (Header2 == Queue2.GetLength())
					{
						return Queue1[Header1++];
					}

					Elysium::Core::Template::System::size Queue1Element = Queue1[Header1];
					Elysium::Core::Template::System::size Queue2Element = Queue2[Header2];

					if (Nodes[Queue1Element]._Frequency <= Nodes[Queue2Element]._Frequency)
					{
						return Queue1[Header1++];
					}

					return Queue2[Header2++];
				};

			for (Elysium::Core::Template::System::size i = 0; i < NodesLength - 1; ++i)
			{
				Elysium::Core::Template::System::size FirstIndex = PopSmallest();
				Elysium::Core::Template::System::size SecondIndex = PopSmallest();

				Node Parent{ 0, Nodes[FirstIndex]._Frequency + Nodes[SecondIndex]._Frequency , -1};
				Nodes.PushBack(Parent);

				Elysium::Core::Template::System::size ParentIndex = Nodes.GetLength() - 1;
				Nodes[FirstIndex]._ParentIndex = ParentIndex;
				Nodes[SecondIndex]._ParentIndex = ParentIndex;

				Queue2.PushBack(ParentIndex);
			}
		}

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

		Elysium::Core::Template::IO::Compression::Algorithm::LempelZiv::LZ77Utility<SymbolType> _LZ77Utility;

		bool _HasWrittenFinalBlock = false;

#ifdef _DEBUG
		Elysium::Core::Template::System::size _BlockCount = 0;
#endif
	};
}
#endif
