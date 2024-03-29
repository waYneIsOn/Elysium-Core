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

#ifndef ELYSIUM_CORE_CONTAINER_VECTOROFBYTE
#include "../Elysium.Core/VectorOfByte.hpp"
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
	// https://tools.ietf.org/html/rfc1952
	class ELYSIUM_CORE_API GZipStream final : public Stream
	{
	public:
		GZipStream(Stream& BaseStream, const CompressionMode CompressionMode);

		GZipStream(Stream& BaseStream, const CompressionMode CompressionMode, const bool LeaveOpen);

		GZipStream(Stream& BaseStream, const CompressionLevel CompressionLevel);

		GZipStream(Stream& BaseStream, const CompressionLevel CompressionLevel, const bool LeaveOpen);

		GZipStream(const GZipStream& Source) = delete;

		GZipStream(GZipStream&& Right) noexcept = delete;

		virtual ~GZipStream();
	public:
		GZipStream& operator=(const GZipStream& Source) = delete;

		GZipStream& operator=(GZipStream&& Right) noexcept = delete;
	public:
		const Stream& GetBaseStream() const;

		virtual const bool GetCanRead() const override;

		virtual const bool GetCanSeek() const override;

		virtual const bool GetCanTimeout() const override;

		virtual const bool GetCanWrite() const override;

		virtual const Elysium::Core::size GetLength() const override;

		virtual const Elysium::Core::uint64_t GetPosition() const override;

		virtual const Elysium::Core::uint32_t GetReadTimeout() const override;

		virtual const Elysium::Core::uint32_t GetWriteTimeout() const override;
	public:
		virtual void SetLength(const Elysium::Core::size Value) override;

		virtual void SetPosition(const Elysium::Core::uint64_t Position) override;
	public:
		virtual void Close() override;

		virtual void Flush() override;

		virtual const Elysium::Core::size Seek(const Elysium::Core::int64_t Offset, const SeekOrigin Origin) override;

		virtual const Elysium::Core::size Read(Elysium::Core::byte* Buffer, const Elysium::Core::size Count) override;

		virtual Elysium::Core::byte ReadByte() override;

		virtual void Write(const Elysium::Core::byte* Buffer, const Elysium::Core::size Count) override;
	private:
		static const Elysium::Core::uint32_t DefaultBufferSize = 4096;
		static const Elysium::Core::int32_t _DefaultHeaderSize = 10;
		static const Elysium::Core::int32_t _DefaultFooterSize = 8;
	private:
		Stream& _BaseStream;
		const CompressionMode _CompressionMode;
		const CompressionLevel _CompressionLevel;
		const bool _LeaveOpen;

		Elysium::Core::Container::VectorOfByte _Buffer;

		bool _HasReadHeaderAndFooter = false;
		Elysium::Core::uint32_t _OptionalHeaderSize = 0;
		Elysium::Core::uint32_t _CRC32 = 0;
		Elysium::Core::uint32_t _UncompressedSize = 0;

		DeflateStream _DeflateStream;
	};
}
#endif
