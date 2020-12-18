#include "GZipStream.hpp"

#include <ostream>

#ifndef ELYSIUM_CORE_NOTSUPPORTEDEXCEPTION
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/NotSupportedException.hpp"
#endif

#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/InvalidOperationException.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_INVALIDDATAEXCEPTION
#include "InvalidDataException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/NotImplementedException.hpp"
#endif

Elysium::Core::IO::Compression::GZipStream::GZipStream(Stream & BaseStream, const CompressionMode CompressionMode)
	: Elysium::Core::IO::Stream(),
	_Buffer(), _UncompressedSize(0),
	_BaseStream(BaseStream), _CompressionMode(CompressionMode), _CompressionLevel(CompressionLevel::Optimal), _LeaveOpen(false),
	_DeflateStream(_BaseStream, CompressionMode)
{ }
Elysium::Core::IO::Compression::GZipStream::GZipStream(Stream & BaseStream, const CompressionMode CompressionMode, const bool LeaveOpen)
	: Elysium::Core::IO::Stream(),
	_Buffer(), _UncompressedSize(0),
	_BaseStream(BaseStream), _CompressionMode(CompressionMode), _CompressionLevel(CompressionLevel::Optimal), _LeaveOpen(LeaveOpen),
	_DeflateStream(_BaseStream, CompressionMode, LeaveOpen)
{ }
Elysium::Core::IO::Compression::GZipStream::GZipStream(Stream & BaseStream, const CompressionLevel CompressionLevel)
	: Elysium::Core::IO::Stream(),
	_Buffer(), _UncompressedSize(0),
	_BaseStream(BaseStream), _CompressionMode(CompressionMode::Compress), _CompressionLevel(CompressionLevel), _LeaveOpen(false),
	_DeflateStream(_BaseStream, CompressionLevel)
{ }
Elysium::Core::IO::Compression::GZipStream::GZipStream(Stream & BaseStream, const CompressionLevel CompressionLevel, const bool LeaveOpen)
	: Elysium::Core::IO::Stream(),
	_Buffer(), _UncompressedSize(0),
	_BaseStream(BaseStream), _CompressionMode(CompressionMode::Compress), _CompressionLevel(CompressionLevel), _LeaveOpen(LeaveOpen),
	_DeflateStream(_BaseStream, CompressionLevel, LeaveOpen)
{ }
Elysium::Core::IO::Compression::GZipStream::~GZipStream()
{
	if (!_LeaveOpen)
	{
		_BaseStream.Close();
	}
}

const Elysium::Core::IO::Stream & Elysium::Core::IO::Compression::GZipStream::GetBaseStream() const
{
	return _BaseStream;
}

const bool Elysium::Core::IO::Compression::GZipStream::GetCanRead() const
{
	return _CompressionMode == CompressionMode::Decompress && _BaseStream.GetCanRead();
}

const bool Elysium::Core::IO::Compression::GZipStream::GetCanSeek() const
{
	return false;
}

const bool Elysium::Core::IO::Compression::GZipStream::GetCanTimeout() const
{
	return false;
}

const bool Elysium::Core::IO::Compression::GZipStream::GetCanWrite() const
{
	return _CompressionMode == CompressionMode::Compress && _BaseStream.GetCanWrite();
}

const size_t Elysium::Core::IO::Compression::GZipStream::GetLength() const
{	// ToDo: message
	throw NotSupportedException();
}

const Elysium::Core::uint64_t Elysium::Core::IO::Compression::GZipStream::GetPosition() const
{	// ToDo: message
	throw NotSupportedException();
}

const Elysium::Core::uint32_t Elysium::Core::IO::Compression::GZipStream::GetReadTimeout() const
{
	return 0;
}

const Elysium::Core::uint32_t Elysium::Core::IO::Compression::GZipStream::GetWriteTimeout() const
{
	return 0;
}

void Elysium::Core::IO::Compression::GZipStream::SetLength(const size_t Value)
{	// ToDo: message
	throw NotSupportedException();
}

void Elysium::Core::IO::Compression::GZipStream::SetPosition(const Elysium::Core::uint64_t Position)
{	// ToDo: message
	throw NotSupportedException();
}

void Elysium::Core::IO::Compression::GZipStream::Close()
{ }

void Elysium::Core::IO::Compression::GZipStream::Flush()
{ }

void Elysium::Core::IO::Compression::GZipStream::Seek(const Elysium::Core::int64_t Offset, const SeekOrigin Origin)
{	// ToDo: message
	throw NotSupportedException();
}

const size_t Elysium::Core::IO::Compression::GZipStream::Read(Elysium::Core::byte * Buffer, const size_t Count)
{
	if (_CompressionMode != CompressionMode::Decompress)
	{
		throw InvalidOperationException(u8"Compression mode is not set to decompress");
	}

	// read header and footer if it hasn't been done so far
	if (!_HasReadHeaderAndFooter)
	{
		size_t BytesRead;
		_BaseStream.SetPosition(0);

		// make sure, we're actually working with gzip-compressed data (check of ID1 and ID2)
		BytesRead = _BaseStream.Read(_Buffer, 10);
		if (BytesRead != 10 || _Buffer[0] != 0x1F || _Buffer[1] != 0x8B)
		{
			throw InvalidDataException(u8"BaseStream does not contain gzip-compressed data");
		}

		// check CM (compression method)
		if (_Buffer[2] != 0x08)
		{
			throw InvalidDataException(u8"This implementation only supports DEFLATE compressed data");
		}

		// FLG (file flags)
        //		bit 0   FTEXT
		//      bit 1   FHCRC
		//      bit 2   FEXTRA
		//      bit 3   FNAME
		//      bit 4   FCOMMENT
		//      bit 5   reserved
		//      bit 6   reserved
		//      bit 7   reserved
		byte FLG = _Buffer[3];

		// MTIME (32-bit timestamp)
		int32_t ModificationDate;
		memcpy(&ModificationDate, &_Buffer[4], sizeof(int32_t));

		// XFL (compression flags)
		byte XFL = _Buffer[8];

		// operating system id
		//		0 - FAT filesystem(MS - DOS, OS / 2, NT / Win32)
		//		1 - Amiga
		//		2 - VMS(or OpenVMS)
		//		3 - Unix
		//		4 - VM / CMS
		//		5 - Atari TOS
		//		6 - HPFS filesystem(OS / 2, NT)
		//		7 - Macintosh
		//		8 - Z - System
		//		9 - CP / M
		//		10 - TOPS - 20
		//		11 - NTFS filesystem(NT)
		//		12 - QDOS
		//		13 - Acorn RISCOS
		//		255 - unknown
		byte OS = _Buffer[9];

		// check FLGs 3rd bit to see whether the header has an optional part
		if(FLG & (1 << 2))
		{
			BytesRead = _BaseStream.Read(_Buffer, 4);
			if (BytesRead != 4)
			{
				throw InvalidDataException(u8"BaseStream does not contain gzip-compressed data");
			}

			// SI1 and SI2
			byte SubId1 = _Buffer[0];
			byte SubId2 = _Buffer[1];

			// XLEN
			int16_t XLEN;
			memcpy(&XLEN, &_Buffer[2], sizeof(int16_t));

			// subfield data
			// ToDo: read and process the subfield data (do-while until XLEN has been reached)

			_HeaderSize += 4 + XLEN;
		}

		// read the gzip footer
		// ToDo: there could be bytes after the gzip footer -> find a better solution than just reading from the end of the stream
		_BaseStream.SetPosition(_BaseStream.GetLength() - 8);
		BytesRead = _BaseStream.Read(&_Buffer[11], 8);
		if (BytesRead != 8)
		{
			throw InvalidDataException(u8"BaseStream does not contain gzip-compressed data");
		}

		// cyclic redundancy check
		// ToDo: perform a check -> https://tools.ietf.org/html/rfc1952#section-8
		memcpy(&_CRC32, &_Buffer[11], sizeof(int32_t));

		// (original, uncompressed) input size
		memcpy(&_UncompressedSize, &_Buffer[15], sizeof(int32_t));

		_HasReadHeaderAndFooter = true;
		_BaseStream.SetPosition(_HeaderSize);
	}

	// use the deflate stream to read the compressed blocks
	return _DeflateStream.Read(Buffer, Count);
}

Elysium::Core::byte Elysium::Core::IO::Compression::GZipStream::ReadByte()
{
	return _DeflateStream.ReadByte();
}

void Elysium::Core::IO::Compression::GZipStream::Write(const Elysium::Core::byte * Buffer, const size_t Count)
{
	if (_CompressionMode != CompressionMode::Compress)
	{	// ToDo: message
		throw InvalidOperationException();
	}

	throw NotImplementedException();
}
