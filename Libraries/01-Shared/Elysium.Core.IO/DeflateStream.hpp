/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_COMPRESSION_DEFLATESTREAM
#define ELYSIUM_CORE_IO_COMPRESSION_DEFLATESTREAM

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

namespace Elysium::Core::IO::Compression
{
	class ELYSIUM_CORE_API DeflateStream final : public Stream
	{
	public:
		DeflateStream(Stream& BaseStream, const CompressionMode CompressionMode);

		DeflateStream(Stream& BaseStream, const CompressionMode CompressionMode, const bool LeaveOpen);

		DeflateStream(Stream& BaseStream, const CompressionLevel CompressionLevel);

		DeflateStream(Stream& BaseStream, const CompressionLevel CompressionLevel, const bool LeaveOpen);

		DeflateStream(const DeflateStream& Source) = delete;

		DeflateStream(DeflateStream&& Right) noexcept = delete;

		virtual ~DeflateStream();
	public:
		DeflateStream& operator=(const DeflateStream& Source) = delete;

		DeflateStream& operator=(DeflateStream&& Right) noexcept = delete;
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
		void ReadIfNecessary();

		const Elysium::Core::uint8_t GetBits(const Elysium::Core::uint8_t Amount);
	private:
		static const Elysium::Core::uint16_t DefaultBufferSize = 4096;

		static const Elysium::Core::uint32_t DefaultByteIndex = 0;

		static const Elysium::Core::uint32_t DefaultBitIndex = 7;
	private:
		Stream& _BaseStream;
		const CompressionMode _CompressionMode;
		const CompressionLevel _CompressionLevel;
		const bool _LeaveOpen;

		Elysium::Core::Container::VectorOfByte _Buffer;

		Elysium::Core::size _BytesAvailable = 0;
		Elysium::Core::size _CurrentByteIndex = DefaultByteIndex;
		Elysium::Core::uint8_t _CurrentBitIndex = DefaultBitIndex;
	};
}
#endif
