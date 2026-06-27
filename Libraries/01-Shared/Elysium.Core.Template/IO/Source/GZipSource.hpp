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

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_KEYVALUEPAIR
#include "../../Container/KeyValuePair.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_RINGBUFFER
#include "../../Container/RingBuffer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../Container/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_READRESULT
#include "../ReadResult.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_ALGORITHM_DEFLATE_DEFLATEDECODER
#include "../Compression/Algorithm/Deflate/DeflateDecoder.hpp"
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
	public:
		inline constexpr GZipSource(InnerSource& InnerSource, const Elysium::Core::Template::System::size BufferSize = MinimumBufferSize) noexcept
			: _Buffer(MinimumBufferSize > BufferSize ? MinimumBufferSize : BufferSize), _InnerSource(InnerSource),
			_State(Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingFixedHeader), _Header{}, _Footer{}, _DecompressedOutputDataBuffer(4096), 
			_DecompressedOutputDataSpan(&_DecompressedOutputDataBuffer[0], _DecompressedOutputDataBuffer.GetCapacity()), _DecompressedOutputDataBufferPosition{}, _DeflateDecoder()
		{ }

		constexpr GZipSource(const GZipSource& Source) = delete;

		constexpr GZipSource(GZipSource&& Right) noexcept = delete;

		inline ~GZipSource()
		{
			Close();
		}
	public:
		constexpr GZipSource& operator=(const GZipSource& Source) = delete;

		constexpr GZipSource& operator=(GZipSource&& Right) noexcept = delete;
	public:
		inline constexpr const Elysium::Core::Template::System::size GetLength() const
		{
			return _InnerSource.GetLength();
		}

		inline constexpr const Elysium::Core::Template::System::uint64_t GetPosition() const
		{
			return _InnerSource.GetPosition();
		}

		inline constexpr const DeviceType& GetDevice() const
		{
			return _InnerSource.GetDevice();
		}
	public:
		inline void SetPosition(const Elysium::Core::Template::System::uint64_t Position)
		{
			_InnerSource.SetPosition(Position);
			_Buffer.Clear();
		}
	public:
		inline void Close()
		{
			if constexpr (requires { _InnerSource.Close(); })
			{
				_InnerSource.Close();
			}
		}

		inline const Elysium::Core::Template::IO::ReadResult ReadBlock(Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte>& TargetView)
		{
			TargetView.SetData(nullptr);
			TargetView.SetLength(0);

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
					const Elysium::Core::Template::IO::ReadResult Result = Decompress(TargetView);
					switch (Result)
					{
					case Elysium::Core::Template::IO::ReadResult::HasData:
						return Result;
					case Elysium::Core::Template::IO::ReadResult::Pending:
						return Result;
					case Elysium::Core::Template::IO::ReadResult::EndOfStream:
						_State = Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingFooter;
						break;
					default:
						// @ToDo:
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
			if (Length > _DecompressedOutputDataBufferPosition)
			{	// @ToDo
				throw 1;
			}

			_DecompressedOutputDataBufferPosition -= Length;
		}
	private:
		inline const Elysium::Core::Template::IO::ReadResult ReadHeader()
		{
			static constexpr const Elysium::Core::Template::System::size HeaderSize = Elysium::Core::Template::IO::Compression::Format::GZip::GZipHeader::Size;

			Elysium::Core::Template::System::size BytesPopulated = 0;
			const Elysium::Core::Template::IO::ReadResult BufferPopulationResult = EnsureAvailableData(HeaderSize, BytesPopulated);
			if (Elysium::Core::Template::IO::ReadResult::Pending == BufferPopulationResult)
			{
				return BufferPopulationResult;
			}

			const Elysium::Core::Template::Container::View::MultiSpan<Elysium::Core::Template::System::byte, 1024, 2> ReadableSpans = _Buffer.RequestReadableSpan();
			Elysium::Core::Template::IO::Compression::Format::GZip::GZipHeader* AddressOfHeader =
				_Buffer.TryGetContiguous<Elysium::Core::Template::IO::Compression::Format::GZip::GZipHeader>(ReadableSpans);
			if (nullptr != AddressOfHeader) ELYSIUM_CORE_PATH_LIKELY
			{
				// this wouldn't work due to the optional fields having none-sense memory values
				//_Header = *AddressOfHeader;

				// ergo simply do a memcpy here
				Elysium::Core::Template::System::byte* TargetData = reinterpret_cast<Elysium::Core::Template::System::byte*>(&_Header);
				Elysium::Core::Template::Memory::MemCpy(TargetData, AddressOfHeader, HeaderSize);
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

				Elysium::Core::Template::System::byte* Target = reinterpret_cast<Elysium::Core::Template::System::byte*>(&_Header);
				Elysium::Core::Template::System::size BytesToCopy0 = Elysium::Core::Template::Math::Min(BytesAvailable0, HeaderSize);
				Elysium::Core::Template::Memory::MemCpy(Target, ReadableSpan0.GetData(), BytesToCopy0);

				if (BytesAvailable0 < HeaderSize)
				{
					Elysium::Core::Template::Memory::MemCpy(&Target[BytesToCopy0], ReadableSpan1.GetData(), HeaderSize - BytesToCopy0);
				}
			}

			if (!_Header.ValidateIds())
			{	// @ToDo: magic number incorrect -> not a gzip file
				throw 1;
			}

			if (!_Header.ValidateCompressionMethod())
			{	// @ToDo: must be deflate (8)
				throw 1;
			}

			_Buffer.CommitReadableSpan(HeaderSize);
			_State = Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingOptionalHeaderExtra;

			return Elysium::Core::Template::IO::ReadResult::HasData;
		}

		inline const Elysium::Core::Template::IO::ReadResult ReadExtra()
		{
			if (!_Header.GetExtraExists())
			{
				_State = Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingOptionalHeaderName;
				return Elysium::Core::Template::IO::ReadResult::HasData;
			}

			// @ToDo: haven't encountered this yet, need to ensure the implementation is correct!
			if (0 == _Header._ExtraLength)
			{
				static constexpr const Elysium::Core::Template::System::size ExtraLengthSize = sizeof(_Header._ExtraLength);

				Elysium::Core::Template::System::size BytesPopulated = 0;
				const Elysium::Core::Template::IO::ReadResult BufferPopulationResult = EnsureAvailableData(ExtraLengthSize, BytesPopulated);
				if (Elysium::Core::Template::IO::ReadResult::Pending == BufferPopulationResult)
				{
					return BufferPopulationResult;
				}

				const Elysium::Core::Template::Container::View::MultiSpan<Elysium::Core::Template::System::byte, 1024, 2> ReadableSpans = _Buffer.RequestReadableSpan();
				Elysium::Core::Template::System::uint16_t* AddressOfExtraLength = _Buffer.TryGetContiguous<Elysium::Core::Template::System::uint16_t>(ReadableSpans);
				if (nullptr != AddressOfExtraLength)
				{
					_Header._ExtraLength = *AddressOfExtraLength;
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

					Elysium::Core::Template::System::byte* Target = reinterpret_cast<Elysium::Core::Template::System::byte*>(&_Header._ExtraLength);
					Elysium::Core::Template::System::size BytesToCopy0 = Elysium::Core::Template::Math::Min(BytesAvailable0, ExtraLengthSize);
					Elysium::Core::Template::Memory::MemCpy(Target, ReadableSpan0.GetData(), BytesToCopy0);

					if (BytesAvailable0 < ExtraLengthSize)
					{
						Elysium::Core::Template::Memory::MemCpy(&Target[BytesToCopy0], ReadableSpan1.GetData(), ExtraLengthSize - BytesToCopy0);
					}
				}

				_Buffer.CommitReadableSpan(ExtraLengthSize);

				if (0 == _Header._ExtraLength)
				{	// extra with no length? consider that data read ;)
					// @ToDo: I guess this would actually be an error regarding the format? need to look it up and potentially throw a specific exception.
					return Elysium::Core::Template::IO::ReadResult::HasData;
				}
			}

			const Elysium::Core::Template::IO::ReadResult ReadBytesResult = ReadBytes(_Header._ExtraLength - _Header._ExtraBuffer.GetLength(), _Header._ExtraBuffer);
			if (Elysium::Core::Template::IO::ReadResult::Pending == ReadBytesResult)
			{
				return ReadBytesResult;
			}

			_State = Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingOptionalHeaderName;

			return Elysium::Core::Template::IO::ReadResult::HasData;
		}

		inline const Elysium::Core::Template::IO::ReadResult ReadName()
		{
			if (!_Header.GetNameExists())
			{
				_State = Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingOptionalHeaderComment;
				return Elysium::Core::Template::IO::ReadResult::HasData;
			}

			const Elysium::Core::Template::IO::ReadResult ReadNullTerminatedStringResult = ReadNullTerminatedString(_Header._NameBuffer);
			if (Elysium::Core::Template::IO::ReadResult::Pending == ReadNullTerminatedStringResult)
			{
				return ReadNullTerminatedStringResult;
			}

			_State = Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingOptionalHeaderComment;

			return Elysium::Core::Template::IO::ReadResult::HasData;
		}

		inline const Elysium::Core::Template::IO::ReadResult ReadComment()
		{
			if (!_Header.GetCommentExists())
			{
				_State = Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingOptionalHeaderCrc;
				return Elysium::Core::Template::IO::ReadResult::HasData;
			}

			// @ToDo: haven't encountered this yet, need to ensure the implementation is correct!
			const Elysium::Core::Template::IO::ReadResult ReadNullTerminatedStringResult = ReadNullTerminatedString(_Header._CommentBuffer);
			if (Elysium::Core::Template::IO::ReadResult::Pending == ReadNullTerminatedStringResult)
			{
				return ReadNullTerminatedStringResult;
			}

			_State = Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingOptionalHeaderCrc;

			return Elysium::Core::Template::IO::ReadResult::HasData;
		}

		inline const Elysium::Core::Template::IO::ReadResult ReadCrc()
		{
			if (!_Header.GetHeaderCrcExists())
			{
				_State = Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::DecodingBlock;
				return Elysium::Core::Template::IO::ReadResult::HasData;
			}

			// @ToDo: haven't encountered this yet, need to ensure the implementation is correct!
			static constexpr const Elysium::Core::Template::System::size CrcSize = sizeof(_Header._Crc);

			Elysium::Core::Template::System::size BytesPopulated = 0;
			const Elysium::Core::Template::IO::ReadResult BufferPopulationResult = EnsureAvailableData(CrcSize, BytesPopulated);
			if (Elysium::Core::Template::IO::ReadResult::Pending == BufferPopulationResult)
			{
				return BufferPopulationResult;
			}

			const Elysium::Core::Template::Container::View::MultiSpan<Elysium::Core::Template::System::byte, 1024, 2> ReadableSpans = _Buffer.RequestReadableSpan();
			Elysium::Core::Template::System::uint16_t* AddressOfCrc = _Buffer.TryGetContiguous<Elysium::Core::Template::System::uint16_t>(ReadableSpans);
			if (nullptr != AddressOfCrc) ELYSIUM_CORE_PATH_LIKELY
			{
				_Header._Crc = *AddressOfCrc;
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

				Elysium::Core::Template::System::byte* Target = reinterpret_cast<Elysium::Core::Template::System::byte*>(&_Header._Crc);
				Elysium::Core::Template::System::size BytesToCopy0 = Elysium::Core::Template::Math::Min(BytesAvailable0, CrcSize);
				Elysium::Core::Template::Memory::MemCpy(Target, ReadableSpan0.GetData(), BytesToCopy0);

				if (BytesAvailable0 < CrcSize)
				{
					Elysium::Core::Template::Memory::MemCpy(&Target[BytesToCopy0], ReadableSpan1.GetData(), CrcSize - BytesToCopy0);
				}
			}

			_Buffer.CommitReadableSpan(CrcSize);
			_State = Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::DecodingBlock;

			return Elysium::Core::Template::IO::ReadResult::HasData;
		}
	
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
			const Elysium::Core::Template::IO::ReadResult BufferPopulationResult = EnsureAvailableData(FooterSize + 1, BytesPopulated);
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
			{
				bool sdfsdfa = false;
			}
				return DecompressionResult;
			default:
				// @ToDo
				throw 1;
			}
		}

		inline const Elysium::Core::Template::IO::ReadResult ReadFooter()
		{
			static constexpr const Elysium::Core::Template::System::size FooterSize = Elysium::Core::Template::IO::Compression::Format::GZip::GZipFooter::Size;

			Elysium::Core::Template::System::size BytesPopulated = 0;
			const Elysium::Core::Template::IO::ReadResult BufferPopulationResult = EnsureAvailableData(FooterSize, BytesPopulated);
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

			return Elysium::Core::Template::IO::ReadResult::EndOfStream;
		}
	private:
		inline const Elysium::Core::Template::IO::ReadResult ReadBytes(const Elysium::Core::Template::System::size Length, 
			Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte>& TargetBuffer)
		{
			Elysium::Core::Template::System::size BytesPopulated = 0;
			const Elysium::Core::Template::IO::ReadResult BufferPopulationResult = EnsureAvailableData(Length, BytesPopulated);
			if (Elysium::Core::Template::IO::ReadResult::Pending == BufferPopulationResult)
			{
				return BufferPopulationResult;
			}

			const Elysium::Core::Template::Container::View::MultiSpan<Elysium::Core::Template::System::byte, 1024, 2> ReadableSpans = _Buffer.RequestReadableSpan();
			Elysium::Core::Template::System::byte* AddressOfData = _Buffer.TryGetContiguous<Elysium::Core::Template::System::byte>(ReadableSpans, Length);
			if (nullptr != AddressOfData)
			{
				TargetBuffer.PushBackRange(AddressOfData, Length);
				_Buffer.CommitReadableSpan(Length);
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

				Elysium::Core::Template::System::size BytesToCopy0 = Elysium::Core::Template::Math::Min(BytesAvailable0, Length);
				TargetBuffer.PushBackRange(ReadableSpan0.GetData(), BytesToCopy0);

				const Elysium::Core::Template::System::size BytesAvailable1 = ReadableSpan1.GetLength();
				Elysium::Core::Template::System::size BytesToCopy1 = Elysium::Core::Template::Math::Min(BytesAvailable1, Length);
				if (BytesAvailable0 < Length)
				{
					TargetBuffer.PushBackRange(ReadableSpan1.GetData(), BytesToCopy1);
				}

				_Buffer.CommitReadableSpan(BytesToCopy0 + BytesToCopy1);
			}

			return Elysium::Core::Template::IO::ReadResult::HasData;
		}

		inline const Elysium::Core::Template::IO::ReadResult ReadNullTerminatedString(Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte>& StringBuffer)
		{
			Elysium::Core::Template::System::size BytesPopulated = 0;
			const Elysium::Core::Template::IO::ReadResult BufferPopulationResult = EnsureAvailableData(0, BytesPopulated);
			if (Elysium::Core::Template::IO::ReadResult::Pending == BufferPopulationResult)
			{
				return BufferPopulationResult;
			}

			// there is no hot-path in this case, we simply have to "scan" through the spans
			const Elysium::Core::Template::Container::View::MultiSpan<Elysium::Core::Template::System::byte, 1024, 2> ReadableSpans = _Buffer.RequestReadableSpan();
			const Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> ReadableSpan0 = ReadableSpans.GetFirst();
			const Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> ReadableSpan1 = ReadableSpans.GetSecond();

			const Elysium::Core::Template::System::byte* Data0 = ReadableSpan0.GetData();
			const Elysium::Core::Template::System::size Length0 = ReadableSpan0.GetLength();

			const Elysium::Core::Template::System::byte* Found = 
				reinterpret_cast<const Elysium::Core::Template::System::byte*>(Elysium::Core::Template::Memory::MemChr(Data0, 0x00, Length0));
			if (nullptr != Found) ELYSIUM_CORE_PATH_LIKELY
			{
				const Elysium::Core::Template::System::size StringLength = Found - Data0;
				StringBuffer.PushBackRange(Data0, StringLength);
				_Buffer.CommitReadableSpan(StringLength + 1);	// musn't forget '\0'!

				return Elysium::Core::Template::IO::ReadResult::HasData;
			}
			else
			{	
				StringBuffer.PushBackRange(Data0, Length0);

				const Elysium::Core::Template::System::byte* Data1 = ReadableSpan1.GetData();
				const Elysium::Core::Template::System::size Length1 = ReadableSpan1.GetLength();

				throw 1;
			}

			return Elysium::Core::Template::IO::ReadResult::HasData;
		}

		inline const Elysium::Core::Template::IO::ReadResult EnsureAvailableData(const Elysium::Core::Template::System::size Desired, Elysium::Core::Template::System::size& BytesCopied)
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
				Elysium::Core::Template::IO::ReadResult Result = _InnerSource.ReadBlock(SourceSpan);
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

					_InnerSource.AdvanceReadingBlock(BytesToCopy0);
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

		inline const Elysium::Core::Template::IO::ReadResult CopyOuputToUserView(Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte>& TargetView)
		{
			if (0 < _DecompressedOutputDataBufferPosition)
			{
				TargetView.SetData(&_DecompressedOutputDataBuffer[0]);
				TargetView.SetLength(_DecompressedOutputDataBufferPosition);

				return Elysium::Core::Template::IO::ReadResult::HasData;
			}
			
			return Elysium::Core::Template::IO::ReadResult::Pending;
		}
	public:
		/// <summary>
		/// Fixed GZipHeader is 10 bytes in size.
		/// Optional GZipHeader size is not defined or limited by RFC 1952.
		/// The amount of DeflateBlocks as well as their lengths vary in size - DeflateDecoder has to deal with having less than a block or multiple blocks in the buffer.
		/// Fixed GZipFooter is 8 bytes in size.
		/// 
		/// To reduce the amount of state information that needs to be saved, the defined minimum buffer size guarantees GZipHeader and GZipFooter fit into the buffer.
		/// Additionally a carefully selected value is a good trade-off between memory-consumption and performance.
		/// @ToDo: find a value that performs well
		/// </summary>
		inline static constexpr const Elysium::Core::Template::System::size MinimumBufferSize = 1024;
	private:
		inline static constexpr const Elysium::Core::Template::System::size _NullTerminatedStringLengthThreshold = 4096;
	private:
		Elysium::Core::Template::Container::RingBuffer<Elysium::Core::Template::System::byte> _Buffer;
		InnerSource& _InnerSource;

		Elysium::Core::Template::IO::Compression::Format::GZip::GZipState _State;

		Elysium::Core::Template::IO::Compression::Format::GZip::GZipHeader _Header;
		Elysium::Core::Template::IO::Compression::Format::GZip::GZipFooter _Footer;

		//Elysium::Core::Template::Container::RingBuffer<Elysium::Core::Template::System::byte> _DecompressedOutputDataBuffer;
		Elysium::Core::Template::Container::FixedSizeBuffer<Elysium::Core::Template::System::byte> _DecompressedOutputDataBuffer;
		Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> _DecompressedOutputDataSpan;
		Elysium::Core::Template::System::size _DecompressedOutputDataBufferPosition;

		Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateDecoder _DeflateDecoder;
	};
}
#endif
