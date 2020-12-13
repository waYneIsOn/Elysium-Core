/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_COMPRESSION_GZIPSTREAM
#define ELYSIUM_CORE_IO_COMPRESSION_GZIPSTREAM

#ifdef _MSC_VER
#pragma once
#endif

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

		virtual const bool GetCanRead() const override;
		virtual const bool GetCanSeek() const override;
		virtual const bool GetCanTimeout() const override;
		virtual const bool GetCanWrite() const override;

		virtual const size_t GetLength() const override;
		virtual const Elysium::Core::int64_t GetPosition() const override;
		virtual const Elysium::Core::int32_t GetReadTimeout() const override;
		virtual const Elysium::Core::int32_t GetWriteTimeout() const override;

		// properties - setter
		virtual void SetLength(const size_t Value) override;
		virtual void SetPosition(const Elysium::Core::int64_t Position) override;

		// methods
		virtual void Close() override;
		virtual void Flush() override;
		virtual void Seek(const Elysium::Core::int64_t Offset, const SeekOrigin Origin) override;
		virtual const size_t Read(Elysium::Core::byte* Buffer, const size_t Count) override;
		virtual Elysium::Core::byte ReadByte() override;
		virtual void Write(const Elysium::Core::byte* Buffer, const size_t Count) override;
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
