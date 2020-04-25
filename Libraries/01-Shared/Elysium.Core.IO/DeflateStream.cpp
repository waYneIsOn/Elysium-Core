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

Elysium::Core::IO::Compression::DeflateStream::DeflateStream(Stream & BaseStream, CompressionMode CompressionMode)
	: Elysium::Core::IO::Stream(),
	_BaseStream(BaseStream), _CompressionMode(CompressionMode), _CompressionLevel(CompressionLevel::Optimal), _LeaveOpen(false)
{
}
Elysium::Core::IO::Compression::DeflateStream::DeflateStream(Stream & BaseStream, CompressionMode CompressionMode, bool LeaveOpen)
	: Elysium::Core::IO::Stream(),
	_BaseStream(BaseStream), _CompressionMode(CompressionMode), _CompressionLevel(CompressionLevel::Optimal), _LeaveOpen(LeaveOpen)
{
}
Elysium::Core::IO::Compression::DeflateStream::DeflateStream(Stream & BaseStream, CompressionLevel CompressionLevel)
	: Elysium::Core::IO::Stream(),
	_BaseStream(BaseStream), _CompressionMode(CompressionMode::Compress), _CompressionLevel(CompressionLevel), _LeaveOpen(false)
{
}
Elysium::Core::IO::Compression::DeflateStream::DeflateStream(Stream & BaseStream, CompressionLevel CompressionLevel, bool LeaveOpen)
	: Elysium::Core::IO::Stream(),
	_BaseStream(BaseStream), _CompressionMode(CompressionMode::Compress), _CompressionLevel(CompressionLevel), _LeaveOpen(LeaveOpen)
{
}
Elysium::Core::IO::Compression::DeflateStream::~DeflateStream()
{
}

const Elysium::Core::IO::Stream & Elysium::Core::IO::Compression::DeflateStream::GetBaseStream() const
{
	return _BaseStream;
}

bool Elysium::Core::IO::Compression::DeflateStream::GetCanRead() const
{
	return _CompressionMode == CompressionMode::Decompress && _BaseStream.GetCanRead();
}
bool Elysium::Core::IO::Compression::DeflateStream::GetCanSeek() const
{
	return false;
}
bool Elysium::Core::IO::Compression::DeflateStream::GetCanTimeout() const
{
	return false;
}
bool Elysium::Core::IO::Compression::DeflateStream::GetCanWrite() const
{
	return _CompressionMode == CompressionMode::Compress && _BaseStream.GetCanWrite();
}

const size_t Elysium::Core::IO::Compression::DeflateStream::GetLength()
{	// ToDo: message
	throw NotSupportedException();
}
const int64_t Elysium::Core::IO::Compression::DeflateStream::GetPosition()
{	// ToDo: message
	throw NotSupportedException();
}
const int Elysium::Core::IO::Compression::DeflateStream::GetReadTimeout() const
{
	return 0;
}
const int Elysium::Core::IO::Compression::DeflateStream::GetWriteTimeout() const
{
	return 0;
}

void Elysium::Core::IO::Compression::DeflateStream::SetLength(size_t Value)
{	// ToDo: message
	throw NotSupportedException();
}
void Elysium::Core::IO::Compression::DeflateStream::SetPosition(int64_t Position)
{	// ToDo: message
	throw NotSupportedException();
}

void Elysium::Core::IO::Compression::DeflateStream::Close()
{
}
void Elysium::Core::IO::Compression::DeflateStream::Flush()
{
}
void Elysium::Core::IO::Compression::DeflateStream::Seek(const int64_t Offset, const SeekOrigin Origin)
{	// ToDo: message
	throw NotSupportedException();
}
size_t Elysium::Core::IO::Compression::DeflateStream::Read(byte * Buffer, const size_t Count)
{
	if (_CompressionMode != CompressionMode::Decompress)
	{	// ToDo: message
		throw InvalidOperationException();
	}

	size_t Index = 0;

	size_t BytesRead;
	bool IsLastBlock;	// BFINAL
	bool EncodingMethod1;	// BTYPE part 1
	bool EncodingMethod2;	// BTYPE part 2


	BytesRead = _BaseStream.Read(&_Buffer[Index], _BufferSize);

	do
	{
		IsLastBlock = _Buffer[Index] & (1 << 0);
		EncodingMethod1 = _Buffer[Index] & (1 << 1);
		EncodingMethod2 = _Buffer[Index] & (1 << 2);

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
				throw InvalidDataException(u"LEN doesn't match complement of NLEN");
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
			throw InvalidOperationException(u"EncodingMethod 11 is reserved and musn't be used");
		}
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
int32_t Elysium::Core::IO::Compression::DeflateStream::ReadByte()
{
	throw NotImplementedException();
}
void Elysium::Core::IO::Compression::DeflateStream::Write(const byte * Buffer, const size_t Count)
{
	if (_CompressionMode != CompressionMode::Compress)
	{	// ToDo: message
		throw InvalidOperationException();
	}

	throw NotImplementedException();
}
