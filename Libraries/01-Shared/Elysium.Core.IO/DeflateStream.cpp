#include "DeflateStream.hpp"

Elysium::Core::IO::Compression::DeflateStream::DeflateStream(const Stream & BaseStream, CompressionLevel CompressionLevel)
	: Elysium::Core::IO::Stream(),
	_BaseStream(BaseStream), _CompressionLevel(CompressionLevel), _CompressionMode(CompressionMode::Compress)
{
}
Elysium::Core::IO::Compression::DeflateStream::DeflateStream(const Stream & BaseStream, CompressionMode CompressionMode)
	: Elysium::Core::IO::Stream(),
	_BaseStream(BaseStream), _CompressionLevel(CompressionLevel::Optimal), _CompressionMode(CompressionMode)
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
	return false;
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
	return false;
}

size_t Elysium::Core::IO::Compression::DeflateStream::GetLength() const
{
	return size_t();
}
int64_t Elysium::Core::IO::Compression::DeflateStream::GetPosition() const
{
	return int64_t();
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
{
}
void Elysium::Core::IO::Compression::DeflateStream::SetPosition(int64_t Position)
{
}

void Elysium::Core::IO::Compression::DeflateStream::Close()
{
}
void Elysium::Core::IO::Compression::DeflateStream::Flush()
{
}
void Elysium::Core::IO::Compression::DeflateStream::Seek(const int64_t Offset, const SeekOrigin Origin)
{
}
size_t Elysium::Core::IO::Compression::DeflateStream::Read(byte * Buffer, const size_t Count)
{
	return size_t();
}
void Elysium::Core::IO::Compression::DeflateStream::Write(const byte * Buffer, const size_t Count)
{
}
