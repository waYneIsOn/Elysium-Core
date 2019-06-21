#include "GZipStream.hpp"

Elysium::Core::IO::Compression::GZipStream::GZipStream(const Stream & BaseStream, CompressionLevel CompressionLevel)
	: Elysium::Core::IO::Stream(),
	_BaseStream(BaseStream), _CompressionLevel(CompressionLevel), _CompressionMode(CompressionMode::Compress)
{
}
Elysium::Core::IO::Compression::GZipStream::GZipStream(const Stream & BaseStream, CompressionMode CompressionMode)
	: Elysium::Core::IO::Stream(),
	_BaseStream(BaseStream), _CompressionLevel(CompressionLevel::Optimal), _CompressionMode(CompressionMode)
{
}
Elysium::Core::IO::Compression::GZipStream::~GZipStream()
{
}

const Elysium::Core::IO::Stream & Elysium::Core::IO::Compression::GZipStream::GetBaseStream() const
{
	return _BaseStream;
}

bool Elysium::Core::IO::Compression::GZipStream::GetCanRead() const
{
	//return _CompressionMode == CompressionMode::Decompress;
	return false;
}
bool Elysium::Core::IO::Compression::GZipStream::GetCanSeek() const
{
	return false;
}
bool Elysium::Core::IO::Compression::GZipStream::GetCanTimeout() const
{
	return false;
}
bool Elysium::Core::IO::Compression::GZipStream::GetCanWrite() const
{
	//return _CompressionMode == CompressionMode::Compress;
	return false;
}

size_t Elysium::Core::IO::Compression::GZipStream::GetLength() const
{
	return size_t();
}
int64_t Elysium::Core::IO::Compression::GZipStream::GetPosition() const
{
	return int64_t();
}
int Elysium::Core::IO::Compression::GZipStream::GetReadTimeout() const
{
	return 0;
}
int Elysium::Core::IO::Compression::GZipStream::GetWriteTimeout() const
{
	return 0;
}

void Elysium::Core::IO::Compression::GZipStream::SetLength(size_t Value)
{
}
void Elysium::Core::IO::Compression::GZipStream::SetPosition(int64_t Position)
{
}

void Elysium::Core::IO::Compression::GZipStream::Close()
{
}
void Elysium::Core::IO::Compression::GZipStream::Flush()
{
}
void Elysium::Core::IO::Compression::GZipStream::Seek(const int64_t Offset, const SeekOrigin Origin)
{
}
size_t Elysium::Core::IO::Compression::GZipStream::Read(byte * Buffer, const size_t Count)
{
	return size_t();
}
void Elysium::Core::IO::Compression::GZipStream::Write(const byte * Buffer, const size_t Count)
{
}
