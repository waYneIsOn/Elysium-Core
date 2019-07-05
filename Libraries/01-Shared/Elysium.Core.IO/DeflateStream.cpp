#include "DeflateStream.hpp"

#ifndef ELYSIUM_CORE_NOTSUPPORTEDEXCEPTION
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/NotSupportedException.hpp"
#endif

#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/InvalidOperationException.hpp"
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

size_t Elysium::Core::IO::Compression::DeflateStream::GetLength()
{	// ToDo: message
	throw NotSupportedException();
}
int64_t Elysium::Core::IO::Compression::DeflateStream::GetPosition()
{	// ToDo: message
	throw NotSupportedException();
}
int Elysium::Core::IO::Compression::DeflateStream::GetReadTimeout() const
{
	return 0;
}
int Elysium::Core::IO::Compression::DeflateStream::GetWriteTimeout() const
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

	size_t BytesRead;
	do
	{
		BytesRead = _BaseStream.Read(&_Buffer[0], _BufferSize);
		break;
	} while (true);

	return -1;

	/*
	do
		read block header from input stream.
		if stored with no compression
			skip any remaining bits in current partially
				processed byte
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
void Elysium::Core::IO::Compression::DeflateStream::Write(const byte * Buffer, const size_t Count)
{
	if (_CompressionMode != CompressionMode::Compress)
	{	// ToDo: message
		throw InvalidOperationException();
	}

	throw NotImplementedException();
}
