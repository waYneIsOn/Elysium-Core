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

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_FIXEDSIZEBUFFER
#include "../../Container/FixedSizeBuffer.hpp"
#endif
/*
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_SLIDINGWINDOW
#include "../../Container/SlidingWindow.hpp"
#endif
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_BITBUFFER
#include "../BitBuffer.hpp"
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
	public:
		inline constexpr DeflateSink(InnerSink& InnerSink, const Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateCompressionLevel CompressionLevel) noexcept
			: _InnerSink(InnerSink), _CompressionLevel(CompressionLevel), _BlockBuffer(Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::MaximumBlockLength),
			_BlockWritePosition{}, _BitBuffer()//, _LZ77HistoryBuffer(DeflateUtility::LZ77HistoryBufferSize)
		{ }

		constexpr DeflateSink(const DeflateSink& Source) = delete;

		constexpr DeflateSink(DeflateSink&& Right) noexcept = delete;

		inline ~DeflateSink()
		{
			Flush();
			Close();
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
		inline void Close()
		{
			if constexpr (requires { _InnerSink.Close(); })
			{
				_InnerSink.Close();
			}
		}

		inline void Flush()
		{
			WriteBufferedBlock(true);
			if constexpr (requires { _InnerSink.Flush(); })
			{
				_InnerSink.Flush();
			}
		}

		inline void Write(const Elysium::Core::Template::System::byte* Buffer, Elysium::Core::Template::System::size Count)
		{
			do
			{
				WriteBufferedBlock(false);

				_BlockWritePosition = Elysium::Core::Template::Math::Min(Count, Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::MaximumBlockLength);
				Elysium::Core::Template::Memory::MemCpy(&_BlockBuffer[0], Buffer, _BlockWritePosition);
				Buffer += _BlockWritePosition;
				Count -= _BlockWritePosition;
			} while (Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::MaximumBlockLength < Count);
		}
	private:
		inline void WriteBufferedBlock(const bool IsFinalBlock, const bool ForceWrite = false)
		{
			if (0 == _BlockWritePosition)
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

			for (Elysium::Core::Template::System::size i = 0; i < _BlockWritePosition; ++i)
			{
				Elysium::Core::Template::System::byte Symbol = _BlockBuffer[i];
				Elysium::Core::Template::System::uint16_t CanonicalCode =
					Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::StaticLiteralTree._CanonicalCodes[Symbol];
				Elysium::Core::Template::System::uint8_t Length =
					Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateUtility::StaticLiteralTree._CodeLengths[Symbol];

				WriteBits(CanonicalCode, Length);
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
			static constexpr Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockType Type =
				Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockType::DynamicHuffman;

			throw 1;
		}

		inline void WriteBlock(const bool IsFinalBlock)
		{
			throw 1;
		}
	private:
		inline void WriteBits(const Elysium::Core::Template::System::uint64_t Bits, const Elysium::Core::Template::System::uint8_t Length)
		{
			const Elysium::Core::Template::System::uint8_t AvailableBits = _BitBuffer.GetLength();
			if (AvailableBits + Length > Elysium::Core::Template::IO::BitBuffer<>::Capacity)
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

		Elysium::Core::Template::IO::BitBuffer<> _BitBuffer;
		//Elysium::Core::Template::Container::SlidingWindow<Elysium::Core::Template::System::byte> _LZ77HistoryBuffer;
	};
}
#endif
