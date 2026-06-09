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

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_RINGBUFFER
#include "../../Container/RingBuffer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../Container/Vector.hpp"
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
		/// <summary>
		/// Fixed GZipHeader is 10 bytes in size.
		/// Fixed GZipFooter is 8 bytes in size.
		/// 
		/// What may differ is the optional GZipHeader containing null-terminated strings.
		/// </summary>
		inline static constexpr const Elysium::Core::Template::System::size MinimumBufferSize = 1024;
	public:
		inline constexpr GZipSource(InnerSource& InnerSource, const Elysium::Core::Template::System::size BufferSize = MinimumBufferSize) noexcept
			: _State(Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingHeader),
			_Buffer(MinimumBufferSize > BufferSize ? MinimumBufferSize : BufferSize), _Position(0), _EndPosition(0), _InnerSource(InnerSource)
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

		inline const Elysium::Core::Template::System::size Read(Elysium::Core::Template::System::byte* Buffer, const Elysium::Core::Template::System::size Count)
		{
			Elysium::Core::Template::System::size TotalBytesWritten = 0;

			while (0 == TotalBytesWritten)
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
					static constexpr const Elysium::Core::Template::System::size ReservedBytes = Elysium::Core::Template::IO::Compression::Format::GZip::GZipFooter::Size;

					Elysium::Core::Template::System::size BytesCopied = 0;

					// "push back" bytes to deflate and do not populate this internal buffer again as to not copy everything all the time!
					if (!_Buffer.GetIsEmpty())
					{
						const Elysium::Core::Template::Container::KeyValuePair<Elysium::Core::Template::System::byte*, Elysium::Core::Template::System::size> ReadableSpan =
							_Buffer.RequestReadableSpan();

						const Elysium::Core::Template::System::size BytesToCopy = Elysium::Core::Template::Math::Min(ReadableSpan.GetValue(), Count);
						Elysium::Core::Template::Memory::MemCpy(Buffer, ReadableSpan.GetKey(), BytesToCopy);

						_Buffer.CommitReadableSpan(BytesToCopy);

						BytesCopied += BytesToCopy;
					}

					if (BytesCopied == Count)
					{
						return BytesCopied;
					}

					const Elysium::Core::Template::System::size BytesRead = _InnerSource.Read(&Buffer[BytesCopied], Count - BytesCopied);

					return BytesCopied + BytesRead;
				}
					break;
				case Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::ReadingFooter:
				{
					ReadFooter();
				}
					break;
				case Elysium::Core::Template::IO::Compression::Format::GZip::GZipState::Done:
					return 0;
				default:
					// @ToDo: throw specific exception
					throw 1;
				}
			}

			return TotalBytesWritten;
		}
	private:
		inline const Elysium::Core::Template::System::size ReadHeader()
		{
			static constexpr const Elysium::Core::Template::System::size BytesToRead = Elysium::Core::Template::IO::Compression::Format::GZip::GZipHeader::Size;

			RefillInternalBuffer(BytesToRead);
			const Elysium::Core::Template::IO::Compression::Format::GZip::GZipHeader* Header =
				reinterpret_cast<Elysium::Core::Template::IO::Compression::Format::GZip::GZipHeader*>(&_Buffer[_Position]);

			if (!Header->ValidateIds())
			{	// @ToDo: magic number incorrect -> not a gzip file
				throw 1;
			}

			if (!Header->ValidateCompressionMethod())
			{	// @ToDo: must be deflate (8)
				throw 1;
			}

			if (0x1F != Header->_Id1 || 0x8B != Header->_Id2)
			{	// @ToDo: magic number incorrect -> not a gzip file
				throw 1;
			}

			if (8 != Header->_CompressionMethod)
			{	// @ToDo: must be deflate (8)
				throw 1;
			}

			Elysium::Core::Template::System::size BytesProcessed = BytesToRead;
			_Position += BytesProcessed;

			if (Header->GetExtraExists())
			{	// @ToDo: haven't encountered this case. need to make sure it's correct!
				RefillInternalBuffer(sizeof(Elysium::Core::Template::System::uint16_t));
				const Elysium::Core::Template::System::uint16_t* ExtraLength = reinterpret_cast<Elysium::Core::Template::System::uint16_t*>(&_Buffer[_Position]);
				BytesProcessed += sizeof(Elysium::Core::Template::System::uint16_t);
				_Position += sizeof(Elysium::Core::Template::System::uint16_t);

				RefillInternalBuffer(*ExtraLength);
				Elysium::Core::Template::System::byte* Extra = &_Buffer[_Position];

				BytesProcessed += *ExtraLength;
				_Position += *ExtraLength;
			}

			if (Header->GetNameExists())
			{
				const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> NameData = ReadNullTerminatedString();

				const Elysium::Core::Template::System::size DataLength = NameData.GetLength();
				BytesProcessed += DataLength;
				_Position += DataLength;
			}

			if (Header->GetCommentExists())
			{	// @ToDo: haven't encountered this case. need to make sure it's correct!
				const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> CommentData = ReadNullTerminatedString();

				const Elysium::Core::Template::System::size DataLength = CommentData.GetLength();
				BytesProcessed += DataLength;
				_Position += DataLength;
			}

			if (Header->GetHeaderCrcExists())
			{	// @ToDo: haven't encountered this case. need to make sure it's correct!
				RefillInternalBuffer(sizeof(Elysium::Core::Template::System::uint16_t));
				const Elysium::Core::Template::System::uint16_t* Crc = reinterpret_cast<Elysium::Core::Template::System::uint16_t*>(&_Buffer[_Position]);

				BytesProcessed += sizeof(Elysium::Core::Template::System::uint16_t);
				_Position += sizeof(Elysium::Core::Template::System::uint16_t);
			}

			return BytesProcessed;
		}

		inline void ReadBlockHeader()
		{
			if (_Buffer.GetIsEmpty())
			{	// can start working with _InnerStream right away

			}


			// 1st byte:
			//	- 1st bit BFINAL: final block == 1
			//  - 2nd and 3rd bit BTYPE:
			//		- 00 (0) uncompressed
			//		- 01 (1) compressed fixed huffman codes
			//		- 10 (2) compressed dynamic huffmand codes
			//		- 11 (3) reserved (currently invalid afaik)
			/*
			RefillInternalBuffer(sizeof(Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlock));
			const Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlock* CurrentBlock = 
				reinterpret_cast<Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlock*>(&_Buffer[_Position]);

			const bool IsFinalBlock = CurrentBlock->GetIsFinalBlock();
			const Elysium::Core::Template::System::uint16_t CompressionMethod = CurrentBlock->GetCompressionMethod();
			*/
		}

		inline void ReadBlock(Elysium::Core::byte* Buffer, const Elysium::Core::size Count)
		{

		}

		inline Elysium::Core::Template::IO::Compression::Format::GZip::GZipFooter ReadFooter()
		{
			return {};
			/*
			// @ToDo: might want to add a positional check?

			Elysium::Core::Template::IO::Compression::Format::GZip::GZipFooter Footer{};
			Elysium::Core::Template::System::byte* AddressOfFooter = reinterpret_cast<Elysium::Core::Template::System::byte*>(&Footer);

			Elysium::Core::Template::System::size TotalBytesRead = 0;
			while (TotalBytesRead < Elysium::Core::Template::IO::Compression::Format::GZip::GZipFooter::Size)
			{
				Elysium::Core::Template::System::size BytesRead = _InnerSource.Read(&AddressOfFooter[TotalBytesRead],
					Elysium::Core::Template::IO::Compression::Format::GZip::GZipFooter::Size - TotalBytesRead);
				TotalBytesRead += BytesRead;
			}

			return Footer;
			*/
		}

		inline const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> ReadNullTerminatedString()
		{
			Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> Result;
			Elysium::Core::Template::Container::KeyValuePair<Elysium::Core::Template::System::byte*, Elysium::Core::Template::System::size> ReadableSpan = _Buffer.RequestReadableSpan();

			Elysium::Core::Template::System::byte* Data = &ReadableSpan.GetKey()[_Position];
			
			// @ToDo: what if the string is longer than my buffer? afaik gzip does not impose a limit on the length!
			// need to handle this case!

			// @ToDo: don't use the byte by byte approach!!!!
			for (Elysium::Core::Template::System::size i = 0; i < ReadableSpan.GetValue(); ++i)
			{
				Elysium::Core::Template::System::byte CurrentByte = Data[i];
				Result.PushBack(CurrentByte);

				if (0x00 == CurrentByte)
				{
					break;
				}
			}
			/*
			while (true)
			{
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
			}
			*/
			return Result;
		}

		inline const Elysium::Core::Template::System::size RefillInternalBuffer(const Elysium::Core::Template::System::size Required)
		{
			// Since this method is private, the following checks really only needs to be done in a debug-build.
			assert(Required <= _Buffer.GetCapacity());
			assert(_EndPosition + Required <= _Buffer.GetCapacity());

			if (Required <= _EndPosition - _Position)
			{	// there are enough bytes in the internal buffer already
				return 0;
			}

			Elysium::Core::Template::Container::KeyValuePair<Elysium::Core::Template::System::byte*, Elysium::Core::Template::System::size> WriteableSpan = _Buffer.RequestWriteableSpan();
			Elysium::Core::Template::System::size TotalBytesRead = 0;
			while (TotalBytesRead < Required)
			{
				Elysium::Core::Template::System::size BytesRead = _InnerSource.Read(WriteableSpan.GetKey(), WriteableSpan.GetValue());
				TotalBytesRead += BytesRead;
			}
			_Buffer.CommitWritableSpan(TotalBytesRead);

			return TotalBytesRead;
		}
	private:
		Elysium::Core::Template::IO::Compression::Format::GZip::GZipState _State;

		Elysium::Core::Template::Container::RingBuffer<Elysium::Core::Template::System::byte> _Buffer;
		Elysium::Core::Template::System::size _Position;
		Elysium::Core::Template::System::size _EndPosition;
		InnerSource& _InnerSource;
	};
}
#endif
