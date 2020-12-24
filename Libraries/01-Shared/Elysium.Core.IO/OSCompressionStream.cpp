#include "OSCompressionStream.hpp"
/*
#ifndef ELYSIUM_CORE_IO_IOEXCEPTION
#include "IOException.hpp"
#endif

Elysium::Core::IO::Compression::OSCompressionStream::OSCompressionStream(Stream& BaseStream, const OSCompressionAlgorithm Algorithm, const CompressionMode CompressionMode, const bool LeaveOpen)
	: Elysium::Core::IO::Stream(),
	_BaseStream(BaseStream), _LeaveOpen(LeaveOpen), _Handle(0), _AllocationRoutines(COMPRESS_ALLOCATION_ROUTINES())
{
	_AllocationRoutines.Allocate = AllocateBuffer;
	_AllocationRoutines.Free = FreeBuffer;
	_AllocationRoutines.UserContext = NULL;
	
	if (CompressionMode == Elysium::Core::IO::Compression::CompressionMode::Compress)
	{
		if (!CreateCompressor(static_cast<unsigned long>(Algorithm) | COMPRESS_RAW, &_AllocationRoutines, &_Handle))
		{
			throw IOException();
		}

		if (!SetCompressorInformation(_Handle, COMPRESS_INFORMATION_CLASS_BLOCK_SIZE, &DefaultBufferSize, sizeof(Elysium::Core::uint32_t)))
		{
			throw IOException();
		}
		/*
		Elysium::Core::uint32_t BlockSize = 0;
		COMPRESS_INFORMATION_CLASS Info = COMPRESS_INFORMATION_CLASS::COMPRESS_INFORMATION_CLASS_BLOCK_SIZE;
		if (!QueryCompressorInformation(_Handle, Info, &BlockSize, sizeof(Elysium::Core::uint32_t)))
		{
			throw IOException();
		}
		*-/
	}
	else
	{
		if (!CreateDecompressor(static_cast<unsigned long>(Algorithm) | COMPRESS_RAW, &_AllocationRoutines, &_Handle))
		{
			throw IOException();
		}

		if (!SetDecompressorInformation(_Handle, COMPRESS_INFORMATION_CLASS_BLOCK_SIZE, &DefaultBufferSize, sizeof(Elysium::Core::uint32_t)))
		{
			throw IOException();
		}
		/*
		Elysium::Core::uint32_t BlockSize = 0;
		COMPRESS_INFORMATION_CLASS Info = COMPRESS_INFORMATION_CLASS::COMPRESS_INFORMATION_CLASS_BLOCK_SIZE;
		if (!QueryDecompressorInformation(_Handle, Info, &BlockSize, sizeof(Elysium::Core::uint32_t)))
		{
			throw IOException();
		}
		*-/
	}
}
Elysium::Core::IO::Compression::OSCompressionStream::~OSCompressionStream()
{
	if (_Handle != 0)
	{
		CloseCompressor(_Handle);
		_Handle = 0;
	}

	if (!_LeaveOpen)
	{
		_BaseStream.Close();
	}
}

const Elysium::Core::IO::Stream& Elysium::Core::IO::Compression::OSCompressionStream::GetBaseStream() const
{
	return _BaseStream;
}

const bool Elysium::Core::IO::Compression::OSCompressionStream::GetCanRead() const
{
	return _BaseStream.GetCanRead();
}

const bool Elysium::Core::IO::Compression::OSCompressionStream::GetCanSeek() const
{
	return _BaseStream.GetCanSeek();
}

const bool Elysium::Core::IO::Compression::OSCompressionStream::GetCanTimeout() const
{
	return _BaseStream.GetCanTimeout();
}

const bool Elysium::Core::IO::Compression::OSCompressionStream::GetCanWrite() const
{
	return _BaseStream.GetCanWrite();
}

const size_t Elysium::Core::IO::Compression::OSCompressionStream::GetLength() const
{
	return _BaseStream.GetLength();
}

const Elysium::Core::uint64_t Elysium::Core::IO::Compression::OSCompressionStream::GetPosition() const
{
	return _BaseStream.GetPosition();
}

const Elysium::Core::uint32_t Elysium::Core::IO::Compression::OSCompressionStream::GetReadTimeout() const
{
	return _BaseStream.GetReadTimeout();
}

const Elysium::Core::uint32_t Elysium::Core::IO::Compression::OSCompressionStream::GetWriteTimeout() const
{
	return _BaseStream.GetWriteTimeout();
}

void Elysium::Core::IO::Compression::OSCompressionStream::SetLength(const size_t Value)
{
	_BaseStream.SetLength(Value);
}

void Elysium::Core::IO::Compression::OSCompressionStream::SetPosition(const Elysium::Core::uint64_t Position)
{
	_BaseStream.SetPosition(Position);
}

void Elysium::Core::IO::Compression::OSCompressionStream::Close()
{
	_BaseStream.Close();
}

void Elysium::Core::IO::Compression::OSCompressionStream::Flush()
{
	_BaseStream.Flush();
}

void Elysium::Core::IO::Compression::OSCompressionStream::Seek(const Elysium::Core::int64_t Offset, const SeekOrigin Origin)
{
	_BaseStream.Seek(Offset, Origin);
}

const size_t Elysium::Core::IO::Compression::OSCompressionStream::Read(Elysium::Core::byte* Buffer, const size_t Count)
{
	throw 1;
	/*
	const size_t BytesRead = _BaseStream.Read(&_Buffer[0], _Buffer.GetLength());

	Elysium::Core::int64_t RequiredBufferSize = 0;
	if (!Decompress(_Handle, &_Buffer[0], _Buffer.GetLength(), nullptr, 0, (PSIZE_T )&RequiredBufferSize))
	{
		if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
		{
			throw IOException();
		}
	}

	if (!Decompress(_Handle, &_Buffer[0], _Buffer.GetLength(), &Buffer[0], Count, nullptr))
	{
		throw IOException();
	}

	return RequiredBufferSize;
	*-/
}

Elysium::Core::byte Elysium::Core::IO::Compression::OSCompressionStream::ReadByte()
{
	throw 1;
}

void Elysium::Core::IO::Compression::OSCompressionStream::Write(const Elysium::Core::byte* Buffer, const size_t Count)
{
	Elysium::Core::uint64_t CompressedBlockSize = 0;
	if (!Compress(_Handle, nullptr, DefaultBufferSize, nullptr, 0, (PSIZE_T)&CompressedBlockSize))
	{
		if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
		{
			throw IOException();
		}
	}

	// Get max. possible size for compressed data for given input data.
	size_t OutputDataSize = (Count % DefaultBufferSize == 0) ? 0 : 1;
	OutputDataSize += Count / DefaultBufferSize;
	OutputDataSize = OutputDataSize * (2 * sizeof(unsigned long) + CompressedBlockSize) + sizeof(unsigned long);

	Elysium::Core::byte* OutputData = (Elysium::Core::byte*)malloc(OutputDataSize);
	if (OutputData == nullptr)
	{	// ToDo
		throw 1;
	}

	// Write uncompressed size to beginning of the buffer.
	*((unsigned long UNALIGNED*) * OutputData) = Count;
	size_t OutputSoFar = sizeof(unsigned long);

	// Compress data block by block.
	DWORD ProcessedSoFar = 0;
	while (ProcessedSoFar < Count)
	{

	}

	/*
	if (!Compress(_Handle, Buffer, Count, &_Buffer[0], _Buffer.GetLength(), (PSIZE_T)&RequiredBufferSize))
	{
		throw IOException();
	}
	_BaseStream.Write(&_Buffer[0], _Buffer.GetLength());
	*/


	/*
	Elysium::Core::int64_t TotalBytesToCompress = RequiredBufferSize;

	const size_t BufferSize = DefaultBufferSize;
	Elysium::Core::uint32_t BytesToCompress = 0;
	do
	{
		BytesToCompress = BufferSize;
		if (!Compress(_Handle, &Buffer[RequiredBufferSize - BytesToCompress], Count - BytesToCompress,
			&_Buffer[0], BytesToCompress, (PSIZE_T)&RequiredBufferSize))
		{
			throw IOException();
		}
		_BaseStream.Write(&_Buffer[0], BytesToCompress);

		TotalBytesToCompress -= BytesToCompress;
	} while (TotalBytesToCompress > 0);
	*-/
}

void * Elysium::Core::IO::Compression::OSCompressionStream::AllocateBuffer(void* Context, size_t Size)
{
	return malloc(Size);
}

void Elysium::Core::IO::Compression::OSCompressionStream::FreeBuffer(void* Context, void* Memory)
{
	if (Memory != nullptr)
	{
		free(Memory);
	}
}
*/