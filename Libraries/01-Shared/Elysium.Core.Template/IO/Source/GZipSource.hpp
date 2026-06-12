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
			: _Buffer(MinimumBufferSize > BufferSize ? MinimumBufferSize : BufferSize), _Position(0), _EndPosition(0), _InnerSource(InnerSource),
			_State(Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingHeader), _DecompressedDataBuffer(4096), _DeflateDecoder()
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
			// @ToDo: need to see how to implement this correctly as there is _Buffer
			_InnerSource.SetPosition(Position);
			_Position = 0;
			_EndPosition = 0;
		}
	public:
		inline void Close()
		{
			if constexpr (requires { _InnerSource.Close(); })
			{
				_InnerSource.Close();
			}
		}

		inline const Elysium::Core::Template::IO::ReadResult ReadBlock(Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte>& DataView)
		{
			while (true)
			{
				switch (_State)
				{
				case Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingHeader:
				{
					const Elysium::Core::Template::System::size BytesProcessed = ReadHeader();

					_Buffer.Pop(BytesProcessed);
					_Position -= BytesProcessed;

					_State = Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::DecodingBlock;
				}
					break;
				case Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::DecodingBlock:
				{
					// GZipSource can not know when the outer source is done with decompressing.
					// Neither should the DeflateDecoder inform GZipSource that it's done.
					// The way around this is to never "forward" the last 8 bytes (size of a GZipFooter) and use those at the appropriate time.
					static constexpr const Elysium::Core::Template::System::size ReservedBytes = Elysium::Core::Template::IO::Compression::Format::GZip::GZipFooter::Size;

					while(true)
					{
						Elysium::Core::Template::System::size BytesRead = 0;


						// @ToDo: this will break at the end of a file or if device is a socket and there is no more data available
						RepopulateBuffer(_Buffer.GetLength(), BytesRead);




						assert(_Buffer.GetLength() > 0);

						Elysium::Core::Template::Container::View::MultiSpan<const Elysium::Core::Template::System::byte, 1024, 2> SourceSpan = _Buffer.RequestReadableSpan();
						Elysium::Core::Template::Container::View::MultiSpan<Elysium::Core::Template::System::byte, 1024, 2> TargetSpan = _DecompressedDataBuffer.RequestWriteableSpan();

						assert(SourceSpan.GetFirst().GetLength() != 0);
						assert(TargetSpan.GetFirst().GetLength() != 0);

						const Elysium::Core::Template::System::size DecompressedBytes = _DeflateDecoder.Decode(SourceSpan, TargetSpan);
						if (DecompressedBytes > 0)
						{





							// @ToDo: this is not right! 
							// _DeflateDecoder.Decode(...) might not have read all the available data!
							// DecompressedBytes doesn't help us here either!
							_Buffer.CommitReadableSpan(SourceSpan.GetFirst().GetLength());







							DataView.SetData(TargetSpan.GetFirst().GetData());
							DataView.SetLength(DecompressedBytes);

							if (Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateState::Done == _DeflateDecoder.GetState())
							{
								_State = Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingFooter;
							}

							return Elysium::Core::Template::IO::ReadResult::HasData;
						}
					}

					return Elysium::Core::Template::IO::ReadResult::HasData;
				}
					break;
				case Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingFooter:
				{
					ReadFooter();
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
			_DecompressedDataBuffer.CommitWritableSpan(Length);
		}
	private:
		inline const Elysium::Core::Template::System::size ReadHeader()
		{
			static constexpr const Elysium::Core::Template::System::size BytesToRead = Elysium::Core::Template::IO::Compression::Format::GZip::GZipHeader::Size;
			Elysium::Core::Template::System::size BytesRead = 0;
			const Elysium::Core::Template::IO::ReadResult InitialRepopulateBufferResult = RepopulateBuffer(BytesToRead, BytesRead);
			if (_Buffer.GetLength() < BytesToRead)
			{
				// @ToDo: not enough data (handling here depends on the internal handling of RepopulateBuffer for ReadResult::Pending)
				throw 1;
			}

			Elysium::Core::Template::Memory::MemCpy(&_Header, &_Buffer[_Position], BytesToRead);

			if (!_Header.ValidateIds())
			{	// @ToDo: magic number incorrect -> not a gzip file
				throw 1;
			}

			if (!_Header.ValidateCompressionMethod())
			{	// @ToDo: must be deflate (8)
				throw 1;
			}

			Elysium::Core::Template::System::size BytesProcessed = BytesToRead;
			_Position += BytesProcessed;

			if (_Header.GetExtraExists())
			{	// @ToDo: haven't encountered this case. need to make sure it's correct!
				static constexpr const Elysium::Core::Template::System::size BytesToReadExtraLength = sizeof(Elysium::Core::Template::System::uint16_t);
				Elysium::Core::Template::System::size BytesRead = 0;
				const Elysium::Core::Template::IO::ReadResult ExtraLengthRepopulateBufferResult = RepopulateBuffer(BytesToReadExtraLength, BytesRead);
				if (_Buffer.GetLength() < BytesToReadExtraLength)
				{
					// @ToDo: not enough data (handling here depends on the internal handling of RepopulateBuffer for ReadResult::Pending)
					throw 1;
				}

				const Elysium::Core::Template::System::uint16_t ExtraLength = *reinterpret_cast<Elysium::Core::Template::System::uint16_t*>(&_Buffer[_Position]);
				BytesProcessed += BytesToReadExtraLength;
				_Position += BytesToReadExtraLength;

				ReadBytes(ExtraLength, _Header._ExtraBuffer);

				BytesProcessed += ExtraLength;
				_Position += ExtraLength;
			}

			if (_Header.GetNameExists())
			{
				ReadNullTerminatedString(_Header._NameBuffer);

				const Elysium::Core::Template::System::size DataLength = _Header._NameBuffer.GetLength();
				BytesProcessed += DataLength;
				_Position += DataLength;
			}

			if (_Header.GetCommentExists())
			{	// @ToDo: haven't encountered this case. need to make sure it's correct!
				ReadNullTerminatedString(_Header._CommentBuffer);

				const Elysium::Core::Template::System::size DataLength = _Header._CommentBuffer.GetLength();
				BytesProcessed += DataLength;
				_Position += DataLength;
			}

			if (_Header.GetHeaderCrcExists())
			{	// @ToDo: haven't encountered this case. need to make sure it's correct!
				static constexpr const Elysium::Core::Template::System::size BytesToReadCrc = sizeof(Elysium::Core::Template::System::uint16_t);
				Elysium::Core::Template::System::size BytesRead = 0;
				const Elysium::Core::Template::IO::ReadResult CrcRepopulateBufferResult = RepopulateBuffer(BytesToReadCrc, BytesRead);
				_Header._Crc = *reinterpret_cast<Elysium::Core::Template::System::uint16_t*>(&_Buffer[_Position]);

				BytesProcessed += BytesToReadCrc;
				_Position += BytesToReadCrc;
			}

			return BytesProcessed;
		}

		inline Elysium::Core::Template::IO::Compression::Format::GZip::GZipFooter ReadFooter()
		{
			static constexpr const Elysium::Core::Template::System::size BytesToRead = Elysium::Core::Template::IO::Compression::Format::GZip::GZipFooter::Size;

			Elysium::Core::Template::System::size BytesRead = 0;
			const Elysium::Core::Template::IO::ReadResult InitialRepopulateBufferResult = RepopulateBuffer(BytesToRead, BytesRead);
			if (_Buffer.GetLength() < BytesToRead)
			{
				// @ToDo: not enough data (handling here depends on the internal handling of RepopulateBuffer for ReadResult::Pending)
				throw 1;
			}

			return *reinterpret_cast<Elysium::Core::Template::IO::Compression::Format::GZip::GZipFooter*>(&_Buffer[_Position]);
		}

		inline void ReadBytes(const Elysium::Core::Template::System::size Length, Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte>& Buffer)
		{
			Elysium::Core::Template::System::size TotalBytesRead = _Buffer.GetLength();
			while (TotalBytesRead < Length)
			{
				Elysium::Core::Template::System::size BytesRead = 0;
				const Elysium::Core::Template::IO::ReadResult ExtraRepopulateBufferResult = RepopulateBuffer(Length, BytesRead);
				TotalBytesRead += BytesRead;
				if (_Buffer.GetLength() < Length)
				{
					// @ToDo: not enough data (handling here depends on the internal handling of RepopulateBuffer for ReadResult::Pending)
					throw 1;
				}

				Buffer.PushBackRange(&_Buffer[_Position], Elysium::Core::Template::Math::Min(BytesRead, Length));
				_Position += BytesRead;
			}
		}

		inline void ReadNullTerminatedString(Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte>& StringBuffer)
		{
			// @Exploit: gzip does not impose a limit on the length of a null-terminated string. I will!
			// @ToDo: handle string-length > buffer-length

			Elysium::Core::Template::System::size TotalBytesRead = 0;

			while (true)
			{
				Elysium::Core::Template::System::size BytesRead = 0;
				RepopulateBuffer(_Buffer.GetLength(), BytesRead);
				TotalBytesRead += BytesRead;

				Elysium::Core::Template::Container::View::MultiSpan<const Elysium::Core::Template::System::byte, 1024, 2> ReadableSpan = _Buffer.RequestReadableSpan();

				const Elysium::Core::Template::System::byte* Data = &ReadableSpan.GetFirst().GetData()[_Position];

				// @ToDo: don't use the byte by byte approach!!!!
				for (Elysium::Core::Template::System::size i = 0; i < ReadableSpan.GetFirst().GetLength(); ++i)
				{
					Elysium::Core::Template::System::byte CurrentByte = Data[i];
					StringBuffer.PushBack(CurrentByte);

					if (0x00 == CurrentByte)
					{
						return;
					}
				}

				//_Buffer.CommitReadableSpan(ReadableSpan.GetValue());

				/*
				// @ToDo: stl remnant
				const void* Found = std::memchr(ReadableSan.GetKey(), 0x00, ReadableSan.GetValue());

				if (Found)
				{
					bool bla = false;
				}
				else
				{
					bool bla = false;
				}

				if (0 == ReadableSan.GetValue())
				{

				}
				*/
			}

		}

		inline const Elysium::Core::Template::IO::ReadResult RepopulateBuffer(const Elysium::Core::Template::System::size Desired, Elysium::Core::Template::System::size& BytesCopied)
		{
			// Since this method is private, the following checks really only are necessary in a debug-build.
			assert(Desired <= _Buffer.GetCapacity());
			assert(_EndPosition + Desired <= _Buffer.GetCapacity());

			if (Desired <= _EndPosition - _Position || _Buffer.GetLength() >= Desired)
			{	// there are enough bytes in the internal buffer already
				return Elysium::Core::Template::IO::ReadResult::HasData;
			}

			Elysium::Core::Template::Container::View::MultiSpan<Elysium::Core::Template::System::byte, 1024, 2> WriteableSpan = _Buffer.RequestWriteableSpan();
			Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> Span{};
			Elysium::Core::Template::System::size TotalBytesRead = 0;

			while (_Buffer.GetLength() < Desired)
			{
				bool MadeProgress = false;
				Elysium::Core::Template::IO::ReadResult Result = _InnerSource.ReadBlock(Span);

				switch (Result)
				{
				case Elysium::Core::Template::IO::ReadResult::HasData:
				{
					if (0 == Span.GetLength())
					{	// @ToDo: need to check this case, if it ever happens because that would mean the underlying source's or device's implementation is wrong
						throw 1;
					}

					const Elysium::Core::Template::System::size BytesToCopy = Elysium::Core::Template::Math::Min(WriteableSpan.GetFirst().GetLength(), Span.GetLength());
					Elysium::Core::Template::Memory::MemCpy(WriteableSpan.GetFirst().GetData(), Span.GetData(), BytesToCopy);
					_InnerSource.AdvanceReadingBlock(BytesToCopy);
					_Buffer.CommitWritableSpan(BytesToCopy);

					TotalBytesRead += BytesToCopy;
					MadeProgress = true;
				}
					break;
				case Elysium::Core::Template::IO::ReadResult::Pending:
					// @ToDo: this is going to happen on non-blocking io (for instance sockets) for sure -> need to handle this case
					// no data avilable -> don't just retry -> strategy?
					throw 1;

					break;
				case Elysium::Core::Template::IO::ReadResult::EndOfStream:
					return Elysium::Core::Template::IO::ReadResult::EndOfStream;
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
	public:
		/// <summary>
		/// Fixed GZipHeader is 10 bytes in size.
		/// Optional GZipHeader size is not defined or limited by RFC 1952.
		/// The amount of DeflateBlocks as well as their lengths vary in size - DeflateDecoder has to deal with having less than a block or multiple blocks in the buffer.
		/// Fixed GZipFooter is 8 bytes in size.
		/// 
		/// To reduce the amount of state information that needs to be saved, the defined minimum buffer size guarantees GZipHeader and GZipFooter fit into the buffer.
		/// Additionally a carefully selected value helps with performance when reading extra-data, null-terminated-strings or DeflateBlocks.
		/// @ToDo: find a value that performs well
		/// </summary>
		inline static constexpr const Elysium::Core::Template::System::size MinimumBufferSize = 1024;
	private:
		inline static constexpr const Elysium::Core::Template::System::size _NullTerminatedStringLengthThreshold = 4096;
	private:
		Elysium::Core::Template::Container::RingBuffer<Elysium::Core::Template::System::byte> _Buffer;
		Elysium::Core::Template::System::size _Position;
		Elysium::Core::Template::System::size _EndPosition;
		InnerSource& _InnerSource;

		Elysium::Core::Template::IO::Compression::Format::GZip::GZipState _State;

		Elysium::Core::Template::IO::Compression::Format::GZip::GZipHeader _Header;
		Elysium::Core::Template::IO::Compression::Format::GZip::GZipFooter _Footer;

		Elysium::Core::Template::Container::RingBuffer<Elysium::Core::Template::System::byte> _DecompressedDataBuffer;
		Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateDecoder _DeflateDecoder;
	};
}
#endif
