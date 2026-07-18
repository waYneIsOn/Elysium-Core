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
			: _InnerSource(InnerSource), _MostInnerSource(_InnerSource.GetMostInnerSource()), _State(Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingFixedHeader),
			_Header{}, _Footer{}, _Crc32(0xFFFFFFFF), _UncompressedSize{}
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
			return _InnerSource._Device;
		}

		inline constexpr DeviceType& GetDevice() const
		{
			return _InnerSource._Device;
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
		/*
		inline const Elysium::Core::Template::IO::ReadResult Decompress(Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte>& TargetView)
		{
			static constexpr const Elysium::Core::Template::System::size FooterSize = Elysium::Core::Template::IO::Compression::Format::GZip::GZipFooter::Size;

			// early exit if there's still data in the output buffer
			const Elysium::Core::Template::IO::ReadResult OutputResult = CopyOuputToUserView(TargetView);
			if (Elysium::Core::Template::IO::ReadResult::HasData == OutputResult)
			{
				return OutputResult;
			}

			Elysium::Core::Template::System::size BytesPopulated = 0;
			//const Elysium::Core::Template::IO::ReadResult BufferPopulationResult = EnsureAvailableData(FooterSize, BytesPopulated);
			const Elysium::Core::Template::IO::ReadResult BufferPopulationResult = EnsureAvailableData(_InnerSource, FooterSize + 1, BytesPopulated);
			if (Elysium::Core::Template::IO::ReadResult::Pending == BufferPopulationResult)
			{
				return BufferPopulationResult;
			}
			else if (Elysium::Core::Template::IO::ReadResult::EndOfStream == BufferPopulationResult)
			{
				if (_Buffer.GetLength() != FooterSize)
				{	// @ToDo:
					throw 1;
				}

				return BufferPopulationResult;
			}

			// GZipSource can not know when the outer source is done with decompressing.
			// Neither should the DeflateDecoder inform GZipSource that it's done.
			// The way around this is to never "forward" the last 8 bytes (size of a GZipFooter) and use those at the appropriate time.
			const Elysium::Core::Template::Container::View::MultiSpan<Elysium::Core::Template::System::byte, 1024, 2> ReadableSpans = _Buffer.RequestReadableSpan(FooterSize);
			//const Elysium::Core::Template::Container::View::MultiSpan<Elysium::Core::Template::System::byte, 1024, 2> ReadableSpans = _Buffer.RequestReadableSpan();

			Elysium::Core::Template::System::size BytesFullyProcessedThisIteration = 0;
			const Elysium::Core::Template::IO::ReadResult DecompressionResult = _DeflateDecoder.Decode(ReadableSpans, _DecompressedOutputDataSpan, _DecompressedOutputDataBufferPosition,
				BytesFullyProcessedThisIteration);
			switch (DecompressionResult)
			{
			case Elysium::Core::Template::IO::ReadResult::HasData:
			{
				_Buffer.CommitReadableSpan(BytesFullyProcessedThisIteration);
				const Elysium::Core::Template::IO::ReadResult OutputResult = CopyOuputToUserView(TargetView);
				if (Elysium::Core::Template::IO::ReadResult::HasData != OutputResult)
				{	// @ToDo: implementation bug
					throw 1;
				}
			}
			return DecompressionResult;
			case Elysium::Core::Template::IO::ReadResult::Pending:
				_Buffer.CommitReadableSpan(BytesFullyProcessedThisIteration);
				return DecompressionResult;
			case Elysium::Core::Template::IO::ReadResult::EndOfStream:
				return DecompressionResult;
			default:
				// @ToDo
				throw 1;
			}
		}
		*/
		inline const Elysium::Core::Template::IO::ReadResult ReadFooter()
		{
			Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> SourceSpan{};
			const Elysium::Core::Template::IO::ReadResult Result = _InnerSource.ReadBlock(SourceSpan);
			switch (Result)
			{
			case Elysium::Core::Template::IO::ReadResult::HasData:
			{
				if (SourceSpan.GetLength() < _FooterSize)
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
				_InnerSource.AdvanceReadingBlock(_FooterSize);
				
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
			/*
			Elysium::Core::Template::System::size BytesPopulated = 0;
			const Elysium::Core::Template::IO::ReadResult BufferPopulationResult = EnsureAvailableData(_MostInnerSource, FooterSize, BytesPopulated);
			if (Elysium::Core::Template::IO::ReadResult::Pending == BufferPopulationResult)
			{
				return BufferPopulationResult;
			}

			const Elysium::Core::Template::Container::View::MultiSpan<Elysium::Core::Template::System::byte, 1024, 2> ReadableSpans = _Buffer.RequestReadableSpan();
			Elysium::Core::Template::IO::Compression::Format::GZip::GZipFooter* AddressOfFooter =
				_Buffer.TryGetContiguous<Elysium::Core::Template::IO::Compression::Format::GZip::GZipFooter>(ReadableSpans);
			if (nullptr != AddressOfFooter) ELYSIUM_CORE_PATH_LIKELY
			{
				_Footer = *AddressOfFooter;
			}
			else
			{
				const Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> ReadableSpan0 = ReadableSpans.GetFirst();
				const Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> ReadableSpan1 = ReadableSpans.GetSecond();
				if (ReadableSpan0.GetIsEmpty())
				{	// @ToDo: if this happens, I've found an error in my implementation!
					throw 1;
				}

				const Elysium::Core::Template::System::size BytesAvailable0 = ReadableSpan0.GetLength();

				Elysium::Core::Template::System::byte* Target = reinterpret_cast<Elysium::Core::Template::System::byte*>(&_Footer);
				Elysium::Core::Template::System::size BytesToCopy0 = Elysium::Core::Template::Math::Min(BytesAvailable0, FooterSize);
				Elysium::Core::Template::Memory::MemCpy(Target, ReadableSpan0.GetData(), BytesToCopy0);

				if (BytesAvailable0 < FooterSize)
				{
					Elysium::Core::Template::Memory::MemCpy(&Target[BytesToCopy0], ReadableSpan1.GetData(), FooterSize - BytesToCopy0);
				}
			}

			_Buffer.CommitReadableSpan(FooterSize);
			
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
			*/
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
		/*
		template <class Source>
		inline const Elysium::Core::Template::IO::ReadResult EnsureAvailableData(Source& InnerSource, const Elysium::Core::Template::System::size Desired, Elysium::Core::Template::System::size& BytesCopied)
		{
			// Since this method is private, the following checks really only are necessary in a debug-build.
			assert(Desired <= _Buffer.GetCapacity());

			if (_Buffer.GetLength() >= Desired)
			{	// there are enough bytes in the internal buffer already
				return Elysium::Core::Template::IO::ReadResult::HasData;
			}

			Elysium::Core::Template::Container::View::MultiSpan<Elysium::Core::Template::System::byte, 1024, 2> WriteableSpan = _Buffer.RequestWriteableSpan();
			Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> WriteableSpan0 = WriteableSpan.GetFirst();
			Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> WriteableSpan1 = WriteableSpan.GetSecond();
			Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> SourceSpan{};

			while (_Buffer.GetLength() < Desired)
			{
				bool MadeProgress = false;
				Elysium::Core::Template::IO::ReadResult Result = InnerSource.ReadBlock(SourceSpan);
				switch (Result)
				{
				case Elysium::Core::Template::IO::ReadResult::HasData:
				{
					if (0 == SourceSpan.GetLength())
					{	// @ToDo: need to check this case, if it ever happens because that would mean the underlying source's or device's implementation is wrong
						throw 1;
					}

					const Elysium::Core::Template::System::size BytesAvailable0 = WriteableSpan0.GetLength();
					const Elysium::Core::Template::System::size BytesToCopy0 = Elysium::Core::Template::Math::Min(BytesAvailable0, SourceSpan.GetLength());
					Elysium::Core::Template::Memory::MemCpy(WriteableSpan0.GetData(), SourceSpan.GetData(), BytesToCopy0);
					BytesCopied += BytesToCopy0;

					const Elysium::Core::Template::System::size BytesAvailable1 = WriteableSpan1.GetLength();
					if (BytesToCopy0 < BytesAvailable0 && 0 < BytesAvailable1)
					{
						// @ToDo: populate 2nd span as well
						throw 1;
					}

					InnerSource.AdvanceReadingBlock(BytesToCopy0);
					_Buffer.CommitWritableSpan(BytesToCopy0);

					MadeProgress = true;
				}
					break;
				case Elysium::Core::Template::IO::ReadResult::Pending:
					return Result;
				case Elysium::Core::Template::IO::ReadResult::EndOfStream:
					return Result;
				default:
					// @ToDo: if this happens, I must have added another value to ReadResult
					throw 1;
				}

				// prevent infinite loops
				if (!MadeProgress)
				{
					break;
				}
			}

			return Elysium::Core::Template::IO::ReadResult::HasData;
		}
		*/
	private:
		inline static constexpr const Elysium::Core::Template::System::size _NullTerminatedStringLengthThreshold = 4096;

		inline static constexpr const Elysium::Core::Template::System::size _FooterSize = Elysium::Core::Template::IO::Compression::Format::GZip::GZipFooter::Size;
	private:
		InnerSource& _InnerSource;
		MostInnerSourceType& _MostInnerSource;

		Elysium::Core::Template::IO::Compression::Format::GZip::GZipState _State;

		Elysium::Core::Template::IO::Compression::Format::GZip::GZipHeader _Header;
		Elysium::Core::Template::IO::Compression::Format::GZip::GZipFooter _Footer;

		//Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateDecoder _DeflateDecoder;

		Elysium::Core::Template::System::uint32_t _Crc32;
		Elysium::Core::Template::System::size _UncompressedSize;
	};
}
#endif
