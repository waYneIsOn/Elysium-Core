/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_SOURCE_GZIPSOURCE
#define ELYSIUM_CORE_TEMPLATE_IO_SOURCE_GZIPSOURCE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../Container/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_READRESULT
#include "../ReadResult.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_GZIP_GZIPFOOTER
#include "../Compression/Format/GZip/GZipFooter.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_GZIP_GZIPHEADER
#include "../Compression/Format/GZip/GZipHeader.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_GZIP_GZIPSTATE
#include "../Compression/Format/GZip/GZipState.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_MIN
#include "../../Math/Min.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMCHR
#include "../../Memory/MemChr.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_CHECKSUM_CRC32
#include "../../Security/Cryptography/Checksum/Crc32.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

#include <cassert>

namespace Elysium::Core::Template::IO::Source
{
	// @ToDo: concept for sources!
	template <class InnerSource>
	class GZipSource
	{
	public:
		using DeviceType = InnerSource::DeviceType;

		using MostInnerSourceType = InnerSource::MostInnerSourceType;
	public:
		inline constexpr GZipSource(InnerSource& InnerSource) noexcept
			: _State(Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingFixedHeader), _Header{}, _Footer{}, _Crc32(0xFFFFFFFF), _UncompressedSize{},
			_InnerSource(InnerSource), _MostInnerSource(_InnerSource.GetMostInnerSource())
		{ }

		constexpr GZipSource(const GZipSource& Source) = delete;

		constexpr GZipSource(GZipSource&& Right) noexcept = delete;

		constexpr ~GZipSource() = default;
	public:
		constexpr GZipSource& operator=(const GZipSource& Source) = delete;

		constexpr GZipSource& operator=(GZipSource&& Right) noexcept = delete;
	public:
		inline MostInnerSourceType& GetMostInnerSource()
		{
			return _InnerSource.GetMostInnerSource();
		}

		inline DeviceType& GetDevice()
		{
			return _InnerSource.GetDevice();
		}

		inline constexpr DeviceType& GetDevice() const
		{
			return _InnerSource.GetDevice();
		}
	public:
		inline constexpr Elysium::Core::Template::System::size GetLength() const
		{
			return _InnerSource.GetLength();
		}

		inline constexpr Elysium::Core::Template::System::uint64_t GetPosition() const
		{
			return _InnerSource.GetPosition();
		}
	public:
		inline void SetPosition(const Elysium::Core::Template::System::uint64_t Position)
		{
			_InnerSource.SetPosition(Position);
		}
	public:
		inline const Elysium::Core::Template::IO::ReadResult ReadBlock(Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte>& TargetView)
		{
			// @ToDo: this is nice for debugging but probably unnecessary
			{
				TargetView.SetData(nullptr);
				TargetView.SetLength(0);
			}
			
			while (true)
			{
				switch (_State)
				{
				case Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingFixedHeader:
				{
					const Elysium::Core::Template::IO::ReadResult Result = ReadHeader();
					if (Elysium::Core::Template::IO::ReadResult::Pending == Result)
					{
						return Result;
					}
				}
					break;
				case Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingOptionalHeaderExtra:
				{
					const Elysium::Core::Template::IO::ReadResult Result = ReadExtra();
					if (Elysium::Core::Template::IO::ReadResult::Pending == Result)
					{
						return Result;
					}
				}
					break;
				case Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingOptionalHeaderName:
				{
					const Elysium::Core::Template::IO::ReadResult Result = ReadName();
					if (Elysium::Core::Template::IO::ReadResult::Pending == Result)
					{
						return Result;
					}
				}
					break;
				case Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingOptionalHeaderComment:
				{
					const Elysium::Core::Template::IO::ReadResult Result = ReadComment();
					if (Elysium::Core::Template::IO::ReadResult::Pending == Result)
					{
						return Result;
					}
				}
					break;
				case Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingOptionalHeaderCrc:
				{
					const Elysium::Core::Template::IO::ReadResult Result = ReadCrc();
					if (Elysium::Core::Template::IO::ReadResult::Pending == Result)
					{
						return Result;
					}
				}
					break;
				case Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::DecodingBlock:
				{
					const Elysium::Core::Template::IO::ReadResult Result = _InnerSource.ReadBlock(TargetView);
					switch (Result)
					{
					case Elysium::Core::Template::IO::ReadResult::HasData:
					{
						const Elysium::Core::Template::System::byte* Data = TargetView.GetData();
						const Elysium::Core::Template::System::size Length = TargetView.GetLength();
						if (nullptr != Data && 0 != Length)
						{
							_Crc32 = Elysium::Core::Template::Security::Cryptography::Checksum::Crc32::CalculateBytewise(_Crc32, Data, Length);
							_UncompressedSize += Length;
						}
					}
						return Result;
					case Elysium::Core::Template::IO::ReadResult::Pending:
						return Result;
					case Elysium::Core::Template::IO::ReadResult::EndOfStream:
						_State = Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingFooter;
						break;
					default:
						// @ToDo: throw specific exception
						throw 1;
					}
				}
					break;
				case Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingFooter:
				{
					const Elysium::Core::Template::IO::ReadResult Result = ReadFooter();
					if (Elysium::Core::Template::IO::ReadResult::Pending == Result)
					{
						return Result;
					}
					_State = Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::Done;
				}
					break;
				case Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::Done:
					return Elysium::Core::Template::IO::ReadResult::EndOfStream;
				default:
					// @ToDo: throw specific exception
					throw 1;
				}
			}

			return Elysium::Core::Template::IO::ReadResult::HasData;
		}

		inline void AdvanceReadingBlock(const Elysium::Core::Template::System::size Length)
		{
			_InnerSource.AdvanceReadingBlock(Length);
		}
	private:
		inline const Elysium::Core::Template::IO::ReadResult ReadHeader()
		{
			static constexpr const Elysium::Core::Template::System::size HeaderSize = Elysium::Core::Template::IO::Compression::Format::GZip::GZipHeader::Size;

			Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> SourceSpan{};
			const Elysium::Core::Template::IO::ReadResult Result = _MostInnerSource.ReadBlock(SourceSpan);
			switch (Result)
			{
			case Elysium::Core::Template::IO::ReadResult::HasData:
			{
				if (SourceSpan.GetLength() < HeaderSize)
				{
					return Elysium::Core::Template::IO::ReadResult::Pending;
				}

				Elysium::Core::Template::IO::Compression::Format::GZip::GZipHeader* AddressOfHeader = 
					reinterpret_cast<Elysium::Core::Template::IO::Compression::Format::GZip::GZipHeader*>(SourceSpan.GetData());

				// this wouldn't work due to the optional fields having none-sense memory values
				//_Header = *AddressOfHeader;

				// ergo simply do a memcpy here
				Elysium::Core::Template::System::byte* TargetData = reinterpret_cast<Elysium::Core::Template::System::byte*>(&_Header);
				Elysium::Core::Template::Memory::MemCpy(TargetData, AddressOfHeader, HeaderSize);
			}
				break;
			case Elysium::Core::Template::IO::ReadResult::Pending:
				return Result;
			case Elysium::Core::Template::IO::ReadResult::EndOfStream:
				// @ToDo
				throw 1;
			default:
				throw 1;
			}

			if (!_Header.ValidateIds())
			{	// @ToDo: magic number incorrect -> not a gzip file
				throw 1;
			}

			if (!_Header.ValidateCompressionMethod())
			{	// @ToDo: must be deflate (8)
				throw 1;
			}

			_MostInnerSource.AdvanceReadingBlock(HeaderSize);

			_State = _Header.GetExtraExists() ? Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingOptionalHeaderExtra :
				_Header.GetNameExists() ? Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingOptionalHeaderName :
				_Header.GetCommentExists() ? Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingOptionalHeaderComment :
				_Header.GetHeaderCrcExists() ? Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingOptionalHeaderCrc :
				Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::DecodingBlock;

			return Elysium::Core::Template::IO::ReadResult::HasData;
		}

		inline const Elysium::Core::Template::IO::ReadResult ReadExtra()
		{
			// @ToDo: haven't encountered this yet, need to ensure the implementation is correct!
			if (0 == _Header._ExtraLength)
			{	// this does seem like something's off with the file though, does it not???
				throw 1;
			}

			const Elysium::Core::Template::IO::ReadResult ReadBytesResult = ReadBytes(_Header._ExtraLength - _Header._ExtraBuffer.GetLength(), _Header._ExtraBuffer);
			if (Elysium::Core::Template::IO::ReadResult::Pending == ReadBytesResult)
			{
				return ReadBytesResult;
			}

			_State = _Header.GetNameExists() ? Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingOptionalHeaderName :
				_Header.GetCommentExists() ? Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingOptionalHeaderComment :
				_Header.GetHeaderCrcExists() ? Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingOptionalHeaderCrc :
				Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::DecodingBlock;

			return Elysium::Core::Template::IO::ReadResult::HasData;
		}

		inline const Elysium::Core::Template::IO::ReadResult ReadName()
		{
			const Elysium::Core::Template::IO::ReadResult ReadNullTerminatedStringResult = ReadNullTerminatedString(_Header._NameBuffer);
			if (Elysium::Core::Template::IO::ReadResult::Pending == ReadNullTerminatedStringResult)
			{
				return ReadNullTerminatedStringResult;
			}

			_State = _Header.GetCommentExists() ? Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingOptionalHeaderComment :
				_Header.GetHeaderCrcExists() ? Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingOptionalHeaderCrc :
				Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::DecodingBlock;

			return Elysium::Core::Template::IO::ReadResult::HasData;
		}

		inline const Elysium::Core::Template::IO::ReadResult ReadComment()
		{
			// @ToDo: haven't encountered this yet, need to ensure the implementation is correct!
			const Elysium::Core::Template::IO::ReadResult ReadNullTerminatedStringResult = ReadNullTerminatedString(_Header._CommentBuffer);
			if (Elysium::Core::Template::IO::ReadResult::Pending == ReadNullTerminatedStringResult)
			{
				return ReadNullTerminatedStringResult;
			}

			_State = _Header.GetHeaderCrcExists() ? Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingOptionalHeaderCrc :
				Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::DecodingBlock;

			return Elysium::Core::Template::IO::ReadResult::HasData;
		}

		inline const Elysium::Core::Template::IO::ReadResult ReadCrc()
		{
			// @ToDo: haven't encountered this yet, need to ensure the implementation is correct!
			static constexpr const Elysium::Core::Template::System::size CrcSize = sizeof(_Header._Crc);

			Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> SourceSpan{};
			const Elysium::Core::Template::IO::ReadResult Result = _MostInnerSource.ReadBlock(SourceSpan);
			switch (Result)
			{
			case Elysium::Core::Template::IO::ReadResult::HasData:
			{
				if (SourceSpan.GetLength() < CrcSize)
				{
					return Elysium::Core::Template::IO::ReadResult::Pending;
				}

				Elysium::Core::Template::System::uint16_t* AddressOfCrc =
					reinterpret_cast<Elysium::Core::Template::System::uint16_t*>(SourceSpan.GetData());
				if (nullptr == AddressOfCrc)
				{
					throw 1;
				}

				_Header._Crc = *AddressOfCrc;
				_MostInnerSource.AdvanceReadingBlock(CrcSize);

				_State = Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::DecodingBlock;

				return Result;
			}
			break;
			case Elysium::Core::Template::IO::ReadResult::Pending:
				return Result;
			case Elysium::Core::Template::IO::ReadResult::EndOfStream:
				// @ToDo
				throw 1;
			default:
				throw 1;
			}
		}

		inline const Elysium::Core::Template::IO::ReadResult ReadFooter()
		{
			static constexpr const Elysium::Core::Template::System::size FooterSize = Elysium::Core::Template::IO::Compression::Format::GZip::GZipFooter::Size;

			Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> SourceSpan{};
			const Elysium::Core::Template::IO::ReadResult Result = _InnerSource.ReadBlock(SourceSpan);
			switch (Result)
			{
			case Elysium::Core::Template::IO::ReadResult::HasData:
			{
				if (SourceSpan.GetLength() < FooterSize)
				{
					return Elysium::Core::Template::IO::ReadResult::Pending;
				}

				Elysium::Core::Template::IO::Compression::Format::GZip::GZipFooter* AddressOfFooter =
					reinterpret_cast<Elysium::Core::Template::IO::Compression::Format::GZip::GZipFooter*>(SourceSpan.GetData());
				if (nullptr == AddressOfFooter)
				{
					throw 1;
				}

				_Footer = *AddressOfFooter;
				_InnerSource.AdvanceReadingBlock(FooterSize);
				
				_Crc32 = ~_Crc32;
				if (_Crc32 != _Footer._Crc32)
				{	// @ToDo
					throw 1;
				}

				if (_UncompressedSize != _Footer._UncompressedSize)
				{	// @ToDo
					throw 1;
				}
				
				return Elysium::Core::Template::IO::ReadResult::EndOfStream;
			}
			case Elysium::Core::Template::IO::ReadResult::EndOfStream:
			{	// @ToDo
				throw 1;
			}
			case Elysium::Core::Template::IO::ReadResult::Pending:
				return Result;
			default:
				throw 1;
			}
		}
	private:
		inline const Elysium::Core::Template::IO::ReadResult ReadBytes(const Elysium::Core::Template::System::size Length, 
			Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte>& TargetBuffer)
		{
			Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> SourceSpan{};
			const Elysium::Core::Template::IO::ReadResult Result = _MostInnerSource.ReadBlock(SourceSpan);
			switch (Result)
			{
			case Elysium::Core::Template::IO::ReadResult::HasData:
			{
				Elysium::Core::Template::System::byte* AddressOfData = SourceSpan.GetData();
				if (nullptr == AddressOfData)
				{	// @ToDo
					throw 1;
				}

				const Elysium::Core::Template::System::size ActualLength = Elysium::Core::Template::Math::Min(Length, SourceSpan.GetLength());
				TargetBuffer.PushBackRange(AddressOfData, ActualLength);
				_MostInnerSource.AdvanceReadingBlock(ActualLength);

				return ActualLength == Length ? Result : Elysium::Core::Template::IO::ReadResult::Pending;
			}
			break;
			case Elysium::Core::Template::IO::ReadResult::Pending:
				return Result;
			case Elysium::Core::Template::IO::ReadResult::EndOfStream:
				// @ToDo
				throw 1;
			default:
				throw 1;
			}
		}

		inline const Elysium::Core::Template::IO::ReadResult ReadNullTerminatedString(Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte>& StringBuffer)
		{
			Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> SourceSpan{};
			const Elysium::Core::Template::IO::ReadResult Result = _MostInnerSource.ReadBlock(SourceSpan);
			switch (Result)
			{
			case Elysium::Core::Template::IO::ReadResult::HasData:
			{
				// there is no hot-path in this case, I simply have to "scan" through the span
				const Elysium::Core::Template::System::byte* Data = SourceSpan.GetData();
				const Elysium::Core::Template::System::size Length = SourceSpan.GetLength();

				const Elysium::Core::Template::System::byte* Found =
					reinterpret_cast<const Elysium::Core::Template::System::byte*>(Elysium::Core::Template::Memory::MemChr(Data, 0x00, Length));
				if (nullptr != Found) ELYSIUM_CORE_PATH_LIKELY
				{
					const Elysium::Core::Template::System::size StringLength = Found - Data;
					StringBuffer.PushBackRange(Data, StringLength);
					_MostInnerSource.AdvanceReadingBlock(StringLength + 1);// musn't forget '\0'!

					return Elysium::Core::Template::IO::ReadResult::HasData;
				}
				else
				{
					StringBuffer.PushBackRange(Data, Length);
					_MostInnerSource.AdvanceReadingBlock(Length);

					return Elysium::Core::Template::IO::ReadResult::Pending;
				}
			}
			break;
			case Elysium::Core::Template::IO::ReadResult::Pending:
				return Result;
			case Elysium::Core::Template::IO::ReadResult::EndOfStream:
				// @ToDo
				throw 1;
			default:
				throw 1;
			}
		}
	private:
		Elysium::Core::Template::IO::Compression::Format::GZip::GZipState _State;

		Elysium::Core::Template::IO::Compression::Format::GZip::GZipHeader _Header;
		Elysium::Core::Template::IO::Compression::Format::GZip::GZipFooter _Footer;

		Elysium::Core::Template::System::uint32_t _Crc32;
		Elysium::Core::Template::System::size _UncompressedSize;

		InnerSource& _InnerSource;
		MostInnerSourceType& _MostInnerSource;
	};
}
#endif
