#include "GZipStream.hpp"

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
	_Buffer(DefaultBufferSize), _UncompressedSize(0),
	_BaseStream(BaseStream), _CompressionMode(CompressionMode), _CompressionLevel(CompressionLevel::Optimal), _LeaveOpen(false),
	_DeflateStream(_BaseStream, CompressionMode)
{ }
Elysium::Core::IO::Compression::GZipStream::GZipStream(Stream & BaseStream, const CompressionMode CompressionMode, const bool LeaveOpen)
	: Elysium::Core::IO::Stream(),
	_Buffer(DefaultBufferSize), _UncompressedSize(0),
	_BaseStream(BaseStream), _CompressionMode(CompressionMode), _CompressionLevel(CompressionLevel::Optimal), _LeaveOpen(LeaveOpen),
	_DeflateStream(_BaseStream, CompressionMode, LeaveOpen)
{ }
Elysium::Core::IO::Compression::GZipStream::GZipStream(Stream & BaseStream, const CompressionLevel CompressionLevel)
	: Elysium::Core::IO::Stream(),
	_Buffer(DefaultBufferSize), _UncompressedSize(0),
	_BaseStream(BaseStream), _CompressionMode(CompressionMode::Compress), _CompressionLevel(CompressionLevel), _LeaveOpen(false),
	_DeflateStream(_BaseStream, CompressionLevel)
{ }
Elysium::Core::IO::Compression::GZipStream::GZipStream(Stream & BaseStream, const CompressionLevel CompressionLevel, const bool LeaveOpen)
	: Elysium::Core::IO::Stream(),
	_Buffer(DefaultBufferSize), _UncompressedSize(0),
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

const Elysium::Core::size Elysium::Core::IO::Compression::GZipStream::GetLength() const
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

void Elysium::Core::IO::Compression::GZipStream::SetLength(const Elysium::Core::size Value)
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

const Elysium::Core::size Elysium::Core::IO::Compression::GZipStream::Seek(const Elysium::Core::int64_t Offset, const SeekOrigin Origin)
{	// ToDo: message
	throw NotSupportedException();
}

const Elysium::Core::size Elysium::Core::IO::Compression::GZipStream::Read(Elysium::Core::byte * Buffer, const Elysium::Core::size Count)
{
	if (_CompressionMode != CompressionMode::Decompress)
	{
		throw InvalidOperationException(u8"Compression mode is not set to decompress.");
	}

	// read header and footer if it hasn't been done so far
	if (!_HasReadHeaderAndFooter)
	{
		Elysium::Core::size BytesRead;
		_BaseStream.SetPosition(0);

		// make sure, we're actually working with gzip-compressed data (check of ID1 and ID2)
		BytesRead = _BaseStream.Read(&_Buffer[0], _Buffer.GetLength());
		if (BytesRead < _DefaultHeaderSize || _Buffer[0] != 0x1F || _Buffer[1] != 0x8B)
		{
			throw InvalidDataException(u8"BaseStream does not contain gzip-compressed data.");
		}

		// check CM (compression method)
		//		0 - None -> copy the bytes
		//		1 - Compressed
		//		2 - Packed
		//		3 - LZH
		//		4 - Reserved
		//		5 - Reserved
		//		6 - Reserved
		//		7 - Reserved
		//		8 - Deflate
		const Elysium::Core::uint8_t CM = _Buffer[2];
		if (CM != 0x00 && CM != 0x08)
		{
			throw InvalidDataException(u8"This implementation only supports DEFLATE compressed data.");
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
		const Elysium::Core::uint8_t FLG = _Buffer[3];

		// MTIME (32-bit timestamp)
		const Elysium::Core::uint32_t ModificationDate = *(Elysium::Core::uint32_t*)(&Buffer[4]);

		// XFL (compression flags)
		const Elysium::Core::uint8_t XFL = _Buffer[8];

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
		const Elysium::Core::uint8_t OS = _Buffer[9];

		// optional data
		if ((FLG >> 6) & 0x01)
		{
			BytesRead = _BaseStream.Read(&_Buffer[0], 4);
			if (BytesRead != 4)
			{
				throw InvalidDataException(u8"BaseStream does not contain gzip-compressed data.");
			}

			// SubfieldId
			Elysium::Core::uint16_t SubfieldId = *(Elysium::Core::uint16_t*)(&Buffer[0]);

			// XLEN
			Elysium::Core::uint16_t ExtraLength = *(Elysium::Core::uint16_t*)(&Buffer[2]);

			// Subfield data length
			_OptionalHeaderSize += 4 + ExtraLength;

			// ToDo: FLG.FNAME set
			if (FLG)
			{

			}

			// ToDo: FLG.FCOMMENT set
			if (FLG)
			{

			}

			// ToDo: FLG.FHCRC set
			if (FLG)
			{

			}
		}

		// read the gzip footer
		// ToDo: there could be bytes after the gzip footer -> find a better solution than just reading from the end of the stream
		_BaseStream.SetPosition(_BaseStream.GetLength() - _DefaultFooterSize);
		BytesRead = _BaseStream.Read(&_Buffer[11], _DefaultFooterSize);
		if (BytesRead != _DefaultFooterSize)
		{
			throw InvalidDataException(u8"BaseStream does not contain gzip-compressed data.");
		}

		// cyclic redundancy check
		// ToDo: perform a check -> https://tools.ietf.org/html/rfc1952#section-8
		_CRC32 = *(Elysium::Core::uint32_t*)(&Buffer[11]);

		// (original uncompressed) input size
		_UncompressedSize = *(Elysium::Core::uint32_t*)(&Buffer[15]);

		_HasReadHeaderAndFooter = true;
	}

	// use the deflate stream to read the compressed blocks
	return _DeflateStream.Read(Buffer, Count);
}

Elysium::Core::byte Elysium::Core::IO::Compression::GZipStream::ReadByte()
{
	return _DeflateStream.ReadByte();
}

void Elysium::Core::IO::Compression::GZipStream::Write(const Elysium::Core::byte * Buffer, const Elysium::Core::size Count)
{
	if (_CompressionMode != CompressionMode::Compress)
	{	// ToDo: message
		throw InvalidOperationException();
	}

	throw NotImplementedException();
}

const Elysium::Core::IAsyncResult* Elysium::Core::IO::Compression::GZipStream::BeginWrite(const Elysium::Core::byte* Buffer, const Elysium::Core::size Size, const Elysium::Core::Delegate<void, const Elysium::Core::IAsyncResult*>& Callback, const void* State)
{
	throw 1;
}

void Elysium::Core::IO::Compression::GZipStream::EndWrite(const Elysium::Core::IAsyncResult* AsyncResult)
{
	throw 1;
}
