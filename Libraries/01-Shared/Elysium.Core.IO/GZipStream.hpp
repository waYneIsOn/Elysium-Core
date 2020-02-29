/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_IO_COMPRESSION_GZIPSTREAM
#define ELYSIUM_CORE_IO_COMPRESSION_GZIPSTREAM

#ifndef ELYSIUM_CORE_IO_STREAM
#include "Stream.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_COMPRESSION_COMPRESSIONLEVEL
#include "CompressionLevel.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_COMPRESSION_COMPRESSIONMODE
#include "CompressionMode.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_COMPRESSION_DEFLATESTREAM
#include "DeflateStream.hpp"
#endif

namespace Elysium::Core::IO::Compression
{
	class ELYSIUM_CORE_API GZipStream : public Stream
	{
	public:
		GZipStream(Stream& BaseStream, CompressionMode CompressionMode);
		GZipStream(Stream& BaseStream, CompressionMode CompressionMode, bool LeaveOpen);
		GZipStream(Stream& BaseStream, CompressionLevel CompressionLevel);
		GZipStream(Stream& BaseStream, CompressionLevel CompressionLevel, bool LeaveOpen);
		~GZipStream();

		// properties - getter
		const Stream& GetBaseStream() const;

		virtual bool GetCanRead() const override;
		virtual bool GetCanSeek() const override;
		virtual bool GetCanTimeout() const override;
		virtual bool GetCanWrite() const override;

		virtual const size_t GetLength() override;
		virtual const int64_t GetPosition() override;
		virtual const int GetReadTimeout() const override;
		virtual const int GetWriteTimeout() const override;

		// properties - setter
		virtual void SetLength(size_t Value) override;
		virtual void SetPosition(int64_t Position) override;

		// methods
		virtual void Close() override;
		virtual void Flush() override;
		virtual void Seek(const int64_t Offset, const SeekOrigin Origin) override;
		virtual size_t Read(byte* Buffer, const size_t Count) override;
		virtual void Write(const byte* Buffer, const size_t Count) override;
	private:
		Stream& _BaseStream;
		CompressionMode _CompressionMode;
		CompressionLevel _CompressionLevel;
		bool _LeaveOpen;

		const static size_t _BufferSize = 8192;
		byte _Buffer[8192];

		bool _HasReadHeaderAndFooter = false;
		int32_t _HeaderSize = 10;
		int32_t _CRC32;
		int32_t _UncompressedSize;

		DeflateStream _DeflateStream;
	};
}
#endif
