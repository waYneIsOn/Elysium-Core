/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_COMPRESSION_OSCOMPRESSIONSTREAM
#define ELYSIUM_CORE_IO_COMPRESSION_OSCOMPRESSIONSTREAM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../Elysium.Core/Array.hpp"
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

#ifndef ELYSIUM_CORE_IO_COMPRESSION_OSCOMPRESSIONALGORITHM
#include "OSCompressionAlgorithm.hpp"
#endif

#if defined(ELYSIUM_CORE_OS_WINDOWS)
#ifndef _WINDOWS_
#include <Windows.h>
#endif

#include <compressapi.h>
#else
#error "unsupported os"
#endif

namespace Elysium::Core::IO::Compression
{
	class ELYSIUM_CORE_API OSCompressionStream : public Stream
	{
	public:
		OSCompressionStream(Stream& BaseStream, const OSCompressionAlgorithm Algorithm, const CompressionMode CompressionMode, const bool LeaveOpen);
		OSCompressionStream(const OSCompressionStream& Source) = delete;
		OSCompressionStream(OSCompressionStream&& Right) noexcept = delete;
		virtual ~OSCompressionStream();

		OSCompressionStream& operator=(const OSCompressionStream& Source) = delete;
		OSCompressionStream& operator=(OSCompressionStream&& Right) noexcept = delete;

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
		virtual void Seek(const Elysium::Core::int64_t Offset, const SeekOrigin Origin) override;
		virtual const size_t Read(Elysium::Core::byte* Buffer, const size_t Count) override;
		virtual Elysium::Core::byte ReadByte() override;
		virtual void Write(const Elysium::Core::byte* Buffer, const size_t Count) override;
	private:
		Stream& _BaseStream;
		const bool _LeaveOpen;

#if defined(ELYSIUM_CORE_OS_WINDOWS)
		COMPRESSOR_HANDLE _Handle;
		COMPRESS_ALLOCATION_ROUTINES _AllocationRoutines;
#else
#error "unsupported os"
#endif
		static constexpr const Elysium::Core::uint32_t DefaultBufferSize = 1 * 1024 * 1024;

		static void* AllocateBuffer(void* Context, size_t Size);
		static void FreeBuffer(void* Context, void* Memory);
	};
}
#endif
