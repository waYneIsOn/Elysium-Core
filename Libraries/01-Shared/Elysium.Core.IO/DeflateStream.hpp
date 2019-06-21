/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_IO_COMPRESSION_DEFLATESTREAM
#define ELYSIUM_CORE_IO_COMPRESSION_DEFLATESTREAM

#ifndef ELYSIUM_CORE_IO_STREAM
#include "Stream.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_COMPRESSION_COMPRESSIONLEVEL
#include "CompressionLevel.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_COMPRESSION_COMPRESSIONMODE
#include "CompressionMode.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace IO
		{
			namespace Compression
			{
				class ELYSIUM_CORE_API DeflateStream : public Stream
				{
				public:
					DeflateStream(const Stream& BaseStream, CompressionLevel CompressionLevel);
					DeflateStream(const Stream& BaseStream, CompressionMode CompressionMode);
					~DeflateStream();

					// properties - getter
					const Stream& GetBaseStream() const;

					virtual bool GetCanRead() const override;
					virtual bool GetCanSeek() const override;
					virtual bool GetCanTimeout() const override;
					virtual bool GetCanWrite() const override;

					virtual size_t GetLength() const override;
					virtual int64_t GetPosition() const override;
					virtual int GetReadTimeout() const override;
					virtual int GetWriteTimeout() const override;

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
					const Stream& _BaseStream;
					CompressionLevel _CompressionLevel;
					CompressionMode _CompressionMode;
				};
			}
		}
	}
}
#endif
