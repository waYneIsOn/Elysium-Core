#include "DeflateStream.hpp"

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

Elysium::Core::IO::Compression::DeflateStream::DeflateStream(Stream & BaseStream, const CompressionMode CompressionMode)
	: Elysium::Core::IO::Stream(),
	_Buffer(DefaultBufferSize), _BaseStream(BaseStream), _CompressionMode(CompressionMode), _CompressionLevel(CompressionLevel::Optimal), _LeaveOpen(false)
{ }
Elysium::Core::IO::Compression::DeflateStream::DeflateStream(Stream & BaseStream, const CompressionMode CompressionMode, const bool LeaveOpen)
	: Elysium::Core::IO::Stream(),
	_Buffer(DefaultBufferSize), _BaseStream(BaseStream), _CompressionMode(CompressionMode), _CompressionLevel(CompressionLevel::Optimal), _LeaveOpen(LeaveOpen)
{ }
Elysium::Core::IO::Compression::DeflateStream::DeflateStream(Stream & BaseStream, const CompressionLevel CompressionLevel)
	: Elysium::Core::IO::Stream(),
	_Buffer(DefaultBufferSize), _BaseStream(BaseStream), _CompressionMode(CompressionMode::Compress), _CompressionLevel(CompressionLevel), _LeaveOpen(false)
{ }
Elysium::Core::IO::Compression::DeflateStream::DeflateStream(Stream & BaseStream, const CompressionLevel CompressionLevel, const bool LeaveOpen)
	: Elysium::Core::IO::Stream(),
	_Buffer(DefaultBufferSize), _BaseStream(BaseStream), _CompressionMode(CompressionMode::Compress), _CompressionLevel(CompressionLevel), _LeaveOpen(LeaveOpen)
{ }
Elysium::Core::IO::Compression::DeflateStream::~DeflateStream()
{
	if (!_LeaveOpen)
	{
		_BaseStream.Close();
	}
}

const Elysium::Core::IO::Stream & Elysium::Core::IO::Compression::DeflateStream::GetBaseStream() const
{
	return _BaseStream;
}

const bool Elysium::Core::IO::Compression::DeflateStream::GetCanRead() const
{
	return _CompressionMode == CompressionMode::Decompress && _BaseStream.GetCanRead();
}

const bool Elysium::Core::IO::Compression::DeflateStream::GetCanSeek() const
{
	return false;
}

const bool Elysium::Core::IO::Compression::DeflateStream::GetCanTimeout() const
{
	return false;
}

const bool Elysium::Core::IO::Compression::DeflateStream::GetCanWrite() const
{
	return _CompressionMode == CompressionMode::Compress && _BaseStream.GetCanWrite();
}

const size_t Elysium::Core::IO::Compression::DeflateStream::GetLength() const
{	// ToDo
	throw NotSupportedException();
}

const Elysium::Core::uint64_t Elysium::Core::IO::Compression::DeflateStream::GetPosition() const
{	// ToDo
	throw NotSupportedException();
}

const Elysium::Core::uint32_t Elysium::Core::IO::Compression::DeflateStream::GetReadTimeout() const
{
	return 0;
}

const Elysium::Core::uint32_t Elysium::Core::IO::Compression::DeflateStream::GetWriteTimeout() const
{
	return 0;
}

void Elysium::Core::IO::Compression::DeflateStream::SetLength(const size_t Value)
{	// ToDo
	throw NotSupportedException();
}

void Elysium::Core::IO::Compression::DeflateStream::SetPosition(const Elysium::Core::uint64_t Position)
{	// ToDo
	throw NotSupportedException();
}

void Elysium::Core::IO::Compression::DeflateStream::Close()
{ 	// ToDo
	throw NotSupportedException();
}

void Elysium::Core::IO::Compression::DeflateStream::Flush()
{ 	// ToDo
	throw NotSupportedException();
}

const size_t Elysium::Core::IO::Compression::DeflateStream::Seek(const Elysium::Core::int64_t Offset, const SeekOrigin Origin)
{	// ToDo
	throw NotSupportedException();
}

const size_t Elysium::Core::IO::Compression::DeflateStream::Read(Elysium::Core::byte * Buffer, const size_t Count)
{
	if (_CompressionMode != CompressionMode::Decompress)
	{	// ToDo: message
		throw InvalidOperationException();
	}

	size_t Index = 0;

	size_t BytesRead;
	bool IsLastBlock;	// BFINAL
	Elysium::Core::uint16_t EncodingMethod;

	bool EncodingMethod1;	// BTYPE part 1
	bool EncodingMethod2;	// BTYPE part 2

	BytesRead = _BaseStream.Read(&_Buffer[Index], DefaultBufferSize);

	do
	{
		byte Test = _Buffer[Index] >> 7;

		IsLastBlock = _Buffer[Index] >> 7;
		EncodingMethod = (_Buffer[Index] >> 5) & 0x02;

		switch (EncodingMethod)
		{
		case 0:	// a stored (aka raw or literal) section, between 0 and 65.535 bytes in length
			break;
		case 1:	// a static huffman compressed block, using pre-agreed huffman tree defined in the RFC
			break;
		case 2:	// a compressed block complete with the huffman table supplied
			break;
		case 3:	// reserved - don't use
			throw InvalidDataException(u8"Reserved encoding method.");
		default:
			throw InvalidDataException(u8"Unknown encoding method.");
		}
		/*
		if (!EncodingMethod1 && !EncodingMethod2)
		{	// 00 - uncompressed block
			Index += 1;
			int16_t BlockLength;
			memcpy(&BlockLength, &_Buffer[Index], sizeof(int16_t));

			Index += 2;
			int16_t BlockLengthComplement;
			memcpy(&BlockLengthComplement, &_Buffer[Index], sizeof(int16_t));
			Index += 2;

			// make sure BlockLength equals the complement on BlockLengthComplement
			if (BlockLength != ~BlockLengthComplement)
			{
				throw InvalidDataException(u8"LEN doesn't match complement of NLEN");
			}

			if (BlockLength > 0)
			{	// ToDo: copy the block
				Index += BlockLength;
				throw NotImplementedException();
			}
		}
		else if (!EncodingMethod1 && EncodingMethod2)
		{	// 01 - statically compressed block
			//int32_t Symbol;


			int x = 34;
		}
		else if (EncodingMethod1 && !EncodingMethod2)
		{	// 10 - dynamically compressed block
			int x = 34;
		}
		else
		{	// 11
			throw InvalidOperationException(u8"EncodingMethod 11 is reserved and musn't be used");
		}
		*/
	} while (!IsLastBlock);

	return -1;

	/*
	do
		read block header from input stream.
		if stored with no compression
			skip any remaining bits in current partially processed byte
			read LEN and NLEN (see next section)
			copy LEN bytes of data to output
		otherwise
			if compressed with dynamic Huffman codes
				read representation of code trees (see subsection below)
			loop (until end of block code recognized)
				decode literal/length value from input stream
				if value < 256
					copy value (literal byte) to output stream
				otherwise
				if value = end of block (256)
					break from loop
				otherwise (value = 257..285)
					decode distance from input stream

					move backwards distance bytes in the output
					stream, and copy length bytes from this
					position to the output stream.
			end loop
	while not last block
	*/
}

Elysium::Core::byte Elysium::Core::IO::Compression::DeflateStream::ReadByte()
{
	throw NotImplementedException();
}

void Elysium::Core::IO::Compression::DeflateStream::Write(const Elysium::Core::byte * Buffer, const size_t Count)
{
	if (_CompressionMode != CompressionMode::Compress)
	{	// ToDo: message
		throw InvalidOperationException();
	}

	throw NotImplementedException();
}
