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

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_GZIP_GZIPFOOTER
#include "../Compression/Format/GZip/GZipFooter.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_GZIP_GZIPHEADER
#include "../Compression/Format/GZip/GZipHeader.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_CHECKSUM_CRC32
#include "../../Security/Cryptography/Checksum/Crc32.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Sink
{
	// @ToDo: concept for "finishable sinks"!
	// @ToDo: GZip atm only allows deflate-compression so I could even specifically limit to DeflateSink here!
	template <class InnerSink>
	class GZipSink
	{
	public:
		using DeviceType = InnerSink::DeviceType;
	public:
		inline constexpr GZipSink(InnerSink& InnerSink) noexcept
			: _InnerSink(InnerSink), _Crc32(0xFFFFFFFF), _UncompressedSize{}, _Header{}, _HasWrittenHeader {}, _HasWrittenFooter{}
		{ }

		constexpr GZipSink(const GZipSink& Source) = delete;

		constexpr GZipSink(GZipSink&& Right) noexcept = delete;

		inline ~GZipSink()
		{
			Finish();
		}
	public:
		constexpr GZipSink& operator=(const GZipSink& Source) = delete;

		constexpr GZipSink& operator=(GZipSink&& Right) noexcept = delete;
	public:
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
			if constexpr (requires { _InnerSink.SetPosition(Position); })
			{
				_InnerSink.SetPosition();
			}
		}
	public:
		inline void SetExtra(const Elysium::Core::Template::System::byte* Data, const Elysium::Core::Template::System::size Length)
		{
			_Header.SetExtra(Data, Length);
		}

		inline void SetComment(const Elysium::Core::Template::Text::String<char8_t>& Comment)
		{
			_Header.SetComment(Comment);
		}

		inline void SetName(const Elysium::Core::Template::Text::String<char8_t>& Name)
		{
			_Header.SetName(Name);
		}

		inline void SetCrc(const Elysium::Core::Template::System::uint16_t Crc)
		{
			_Header.SetCrc(Crc);
		}
	public:
		inline void Write(const Elysium::Core::Template::System::byte* Buffer, const Elysium::Core::Template::System::size Count)
		{
			if (nullptr == Buffer || 0 == Count)
			{
				return;
			}

			WriteHeader();

			_Crc32 = Elysium::Core::Template::Security::Cryptography::Checksum::Crc32::CalculateBytewise(_Crc32, Buffer, Count);
			_InnerSink.Write(Buffer, Count);
			_UncompressedSize += Count;
		}

		inline void Finish()
		{
			// GZipSink requires _InnerSink to finish before it can write it's footer.
			// So in this case I enforce a compile-time error if _InnerSink doesn't have a Finish()-method!
			// @ToDo: enforce this by having a FinishableSink-concept!
			_InnerSink.Finish();
			/*
			if constexpr (requires { _InnerSink.Finish(); })
			{
				_InnerSink.Finish();
			}
			*/

			WriteFooter();
			Flush();
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

			DeviceType& Device = _InnerSink.GetDevice();

			Device.Write(&Elysium::Core::Template::IO::Compression::Format::GZip::GZipHeader::MagicValue0, 1);
			Device.Write(&Elysium::Core::Template::IO::Compression::Format::GZip::GZipHeader::MagicValue1, 1);
			Device.Write(&Elysium::Core::Template::IO::Compression::Format::GZip::GZipHeader::CompressionMethodDeflate, 1);
			Device.Write(&_Header._Flags, 1);
			Device.Write(reinterpret_cast<const Elysium::Core::Template::System::byte*>(&_Header._ModificationTime), sizeof(Elysium::Core::Template::System::uint32_t));
			Device.Write(&_Header._ExtraFlags, 1);
			Device.Write(&_Header._OperatingSystem, 1);

			if (_Header.GetExtraExists())
			{
				Device.Write(&_Header._ExtraBuffer[0], _Header._ExtraLength);
			}
			if (_Header.GetNameExists())
			{
				Device.Write(&_Header._NameBuffer[0], _Header._NameBuffer.GetLength());
			}
			if (_Header.GetCommentExists())
			{
				Device.Write(&_Header._CommentBuffer[0], _Header._CommentBuffer.GetLength());
			}
			if (_Header.GetHeaderCrcExists())
			{
				constexpr const Elysium::Core::Template::System::size CrcSize = sizeof(_Header._Crc);
				Device.Write(reinterpret_cast<const Elysium::Core::Template::System::byte*>(&_Header._Crc), CrcSize);
			}
			
			_HasWrittenHeader = true;
		}

		inline void WriteFooter()
		{
			if (_HasWrittenFooter)
			{
				return;
			}

			DeviceType& Device = _InnerSink.GetDevice();

			_Crc32 = ~_Crc32;
			Device.Write(reinterpret_cast<const Elysium::Core::Template::System::byte*>(&_Crc32), sizeof(Elysium::Core::Template::System::uint32_t));
			Device.Write(reinterpret_cast<const Elysium::Core::Template::System::byte*>(&_UncompressedSize), sizeof(Elysium::Core::Template::System::uint32_t));

			_HasWrittenFooter = true;
		}
	private:
		InnerSink& _InnerSink;
		Elysium::Core::Template::System::uint32_t _Crc32;
		Elysium::Core::Template::System::uint32_t _UncompressedSize;

		Elysium::Core::Template::IO::Compression::Format::GZip::GZipHeader _Header;

		bool _HasWrittenHeader;
		bool _HasWrittenFooter;
	};
}
#endif
