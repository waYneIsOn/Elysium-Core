/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_SOURCE_GZIPSINK
#define ELYSIUM_CORE_TEMPLATE_IO_SOURCE_GZIPSINK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../Container/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_BITREADER
#include "../BitWriter.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_ALGORITHM_DEFLATE_DEFLATEENCODER
#include "../Compression/Algorithm/Deflate/DeflateEncoder.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_GZIP_GZIPHEADER
#include "../Compression/Format/GZip/GZipHeader.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_CHECKSUM_CRC32
#include "../../Security/Cryptography/Checksum/Crc32.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif








#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_DEFLATE_DEFLATEBLOCKTYPE
#include "../Compression/Format/Deflate/DeflateBlockType.hpp"
#endif




namespace Elysium::Core::Template::IO::Sink
{
	// @ToDo: concept for sinks!
	template <class InnerSink>
	class GZipSink
	{
	public:
		using DeviceType = InnerSink::DeviceType;
	public:
		inline constexpr GZipSink(InnerSink& InnerSink) noexcept
			: _InnerSink(InnerSink), _CurrentBlockBuffer(4096), _Crc32(0xFFFFFFFF), _UncompressedSize{},
			_DecompressedOutputDataBuffer(4096), _HasWrittenHeader{}, _HasWrittenFooter{}
		{ 
			_CurrentBlockBuffer.Clear();
		}

		constexpr GZipSink(const GZipSink& Source) = delete;

		constexpr GZipSink(GZipSink&& Right) noexcept = delete;

		inline ~GZipSink()
		{
			Flush();
			Close();
		}
	public:
		constexpr GZipSink& operator=(const GZipSink& Source) = delete;

		constexpr GZipSink& operator=(GZipSink&& Right) noexcept = delete;
	public:
		inline constexpr const DeviceType& GetDevice() const
		{
			return _InnerSink.GetDevice();
		}
	public:
		inline void SetPosition(const Elysium::Core::Template::System::uint64_t Position)
		{
			if constexpr (requires { _InnerSink.SetPosition(Position); })
			{
				_InnerSink.SetPosition();
			}
		}
	public:
		void Close()
		{
			WriteBufferedBlock(true);
			WriteFooter();
			Flush();

			if constexpr (requires { _InnerSink.Close(); })
			{
				_InnerSink.Close();
			}
		}
	public:
		inline void Write(const Elysium::Core::Template::System::byte* Buffer, const Elysium::Core::Template::System::size Count)
		{
			if (nullptr == Buffer || 0 == Count)
			{
				return;
			}

			WriteHeader();
			WriteBufferedBlock();
			BufferBlock(Buffer, Count);
		}

		inline void Flush()
		{
			if constexpr (requires { _InnerSink.Flush(); })
			{
				_InnerSink.Flush();
			}
		}
	private:
		inline void WriteHeader()
		{
			if (_HasWrittenHeader)
			{
				return;
			}
			constexpr Elysium::Core::Template::System::byte Flags = 0;
			constexpr Elysium::Core::Template::System::uint32_t ModificationTime = 0;
			constexpr Elysium::Core::Template::System::byte ExtraFlags = 0;
#ifdef ELYSIUM_CORE_OS_WINDOWS
			constexpr Elysium::Core::Template::System::byte OperatingSystem = 0;
#endif

			_InnerSink.Write(&Elysium::Core::Template::IO::Compression::Format::GZip::GZipHeader::MagicValue0, 1);
			_InnerSink.Write(&Elysium::Core::Template::IO::Compression::Format::GZip::GZipHeader::MagicValue1, 1);
			_InnerSink.Write(&Elysium::Core::Template::IO::Compression::Format::GZip::GZipHeader::CompressionMethodDeflate, 1);
			_InnerSink.Write(&Flags, 1);
			_InnerSink.Write(reinterpret_cast<const Elysium::Core::Template::System::byte*>(&ModificationTime), sizeof(Elysium::Core::Template::System::uint32_t));
			_InnerSink.Write(&ExtraFlags, 1);
			_InnerSink.Write(&OperatingSystem, 1);
			/*
			if (Flags)
			{
				constexpr Elysium::Core::Template::System::uint16_t ExtraLength = 0;
				_InnerSink.Write(reinterpret_cast<const Elysium::Core::Template::System::byte*>(&ExtraLength), sizeof(Elysium::Core::Template::System::uint16_t));
			}
			*/
			_HasWrittenHeader = true;
		}

		inline void WriteFooter()
		{
			if (_HasWrittenFooter)
			{
				return;
			}

			_Crc32 = ~_Crc32;
			_InnerSink.Write(reinterpret_cast<const Elysium::Core::Template::System::byte*>(&_Crc32), sizeof(Elysium::Core::Template::System::uint32_t));
			_InnerSink.Write(reinterpret_cast<const Elysium::Core::Template::System::byte*>(&_UncompressedSize), sizeof(Elysium::Core::Template::System::uint32_t));

			_HasWrittenFooter = true;
		}

		inline void BufferBlock(const Elysium::Core::Template::System::byte* Buffer, const Elysium::Core::Template::System::size Count)
		{
			_Crc32 = Elysium::Core::Template::Security::Cryptography::Checksum::Crc32::CalculateBytewise(_Crc32, Buffer, Count);

			_CurrentBlockBuffer.PushBackRange(Buffer, Count);
			_UncompressedSize += Count;
		}

		inline void WriteBufferedBlock(bool IsFinalBlock = false)
		{
			if (0 == _CurrentBlockBuffer.GetLength())
			{
				return;
			}

			constexpr Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockType Type = 
				Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockType::Uncompressed;

			const Elysium::Core::Template::System::uint16_t BlockSize = _CurrentBlockBuffer.GetLength();
			const Elysium::Core::Template::System::uint16_t ComplementLength = ~BlockSize;

			Elysium::Core::Template::System::byte DeflateHeader = 0x00;
			DeflateHeader |= IsFinalBlock;
			DeflateHeader |= static_cast<Elysium::Core::Template::System::byte>(Type) << 1;

			_InnerSink.Write(&DeflateHeader, 1);
			_InnerSink.Write(reinterpret_cast<const Elysium::Core::Template::System::byte*>(&BlockSize), sizeof(Elysium::Core::Template::System::uint16_t));
			_InnerSink.Write(reinterpret_cast<const Elysium::Core::Template::System::byte*>(&ComplementLength), sizeof(Elysium::Core::Template::System::uint16_t));
			_InnerSink.Write(&_CurrentBlockBuffer[0], BlockSize);

			_CurrentBlockBuffer.Clear();
		}
	private:
		InnerSink& _InnerSink;
		Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> _CurrentBlockBuffer;
		Elysium::Core::Template::System::uint32_t _Crc32;
		Elysium::Core::Template::System::uint32_t _UncompressedSize;

		Elysium::Core::Template::Container::FixedSizeBuffer<Elysium::Core::Template::System::byte> _DecompressedOutputDataBuffer;

		bool _HasWrittenHeader;
		bool _HasWrittenFooter;
	};
}
#endif
