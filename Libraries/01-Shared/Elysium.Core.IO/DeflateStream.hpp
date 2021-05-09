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

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAYOFBYTE
#include "../Elysium.Core/ArrayOfByte.hpp"
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

		DeflateStream& operator=(const DeflateStream& Source) = delete;
		DeflateStream& operator=(DeflateStream&& Right) noexcept = delete;

		const Stream& GetBaseStream() const;

		virtual const bool GetCanRead() const override;
		virtual const bool GetCanSeek() const override;
		virtual const bool GetCanTimeout() const override;
		virtual const bool GetCanWrite() const override;

		virtual const size_t GetLength() const override;
		virtual const Elysium::Core::uint64_t GetPosition() const override;
		virtual const Elysium::Core::uint32_t GetReadTimeout() const override;
		virtual const Elysium::Core::uint32_t GetWriteTimeout() const override;

		virtual void SetLength(const size_t Value) override;
		virtual void SetPosition(const Elysium::Core::uint64_t Position) override;

		virtual void Close() override;
		virtual void Flush() override;
		virtual const size_t Seek(const Elysium::Core::int64_t Offset, const SeekOrigin Origin) override;
		virtual const size_t Read(Elysium::Core::byte* Buffer, const size_t Count) override;
		virtual Elysium::Core::byte ReadByte() override;
		virtual void Write(const Elysium::Core::byte* Buffer, const size_t Count) override;
	private:
		Stream& _BaseStream;
		const CompressionMode _CompressionMode;
		const CompressionLevel _CompressionLevel;
		const bool _LeaveOpen;

		static constexpr const Elysium::Core::uint16_t DefaultBufferSize = 4096;
		Elysium::Core::Collections::Template::Array<Elysium::Core::byte> _Buffer;

		static constexpr const Elysium::Core::uint32_t DefaultByteIndex = 0;
		static constexpr const Elysium::Core::uint32_t DefaultBitIndex = 7;
		size_t _BytesAvailable = 0;
		size_t _CurrentByteIndex = DefaultByteIndex;
		Elysium::Core::uint8_t _CurrentBitIndex = DefaultBitIndex;

		void ReadIfNecessary();
		const Elysium::Core::uint8_t GetBits(const Elysium::Core::uint8_t Amount);
	};
}
#endif
