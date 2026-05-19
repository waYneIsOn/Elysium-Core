/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_STREAM
#define ELYSIUM_CORE_TEMPLATE_IO_STREAM

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::IO
{
	class Stream
	{
	protected:
		constexpr Stream() noexcept = default;
	public:
		constexpr Stream(const Stream& Source) = delete;

		constexpr Stream(Stream&& Right) noexcept = delete;

		virtual ~Stream() = default;
	public:
		constexpr Stream& operator=(const Stream& Source) = delete;

		constexpr Stream& operator=(Stream&& Right) noexcept = delete;
	/*
	public:
		virtual const bool GetCanRead() const = 0;

		virtual const bool GetCanSeek() const = 0;

		virtual const bool GetCanTimeout() const;

		virtual const bool GetCanWrite() const = 0;

		virtual const Elysium::Core::size GetLength() const = 0;

		virtual const Elysium::Core::uint64_t GetPosition() const;

		virtual const Elysium::Core::uint32_t GetReadTimeout() const;

		virtual const Elysium::Core::uint32_t GetWriteTimeout() const;
	public:
		virtual void SetLength(const Elysium::Core::size Value) = 0;

		virtual void SetPosition(const Elysium::Core::uint64_t Position) = 0;

		virtual void SetReadTimeout(const Elysium::Core::uint32_t Value);

		virtual void SetWriteTimeout(const Elysium::Core::uint32_t Value);
	public:
		virtual void CopyTo(Stream& Destination);

		virtual void CopyTo(Stream& Destination, const Elysium::Core::size BufferSize);

		virtual void Close() = 0;

		virtual void Flush() = 0;

		virtual const Elysium::Core::size Seek(const int64_t Offset, const SeekOrigin Origin) = 0;

		virtual const Elysium::Core::size Read(Elysium::Core::byte* Buffer, const Elysium::Core::size Count) = 0;

		virtual Elysium::Core::byte ReadByte() = 0;

		virtual void Write(const Elysium::Core::byte* Buffer, const Elysium::Core::size Count) = 0;

		virtual void WriteByte(const Elysium::Core::byte Value);
	public:
		virtual Elysium::Core::Template::Memory::UniquePointer<Elysium::Core::IAsyncResult> BeginWrite(const Elysium::Core::byte* Buffer, 
			const Elysium::Core::size Size, const Elysium::Core::Container::DelegateOfVoidAtomicIASyncResultReference& Callback,
			const void* State);

		virtual void EndWrite(const Elysium::Core::IAsyncResult* AsyncResult);

		virtual Elysium::Core::Template::Memory::UniquePointer<Elysium::Core::IAsyncResult> BeginRead(const Elysium::Core::byte* Buffer, const Elysium::Core::size Size,
			const Elysium::Core::Container::DelegateOfVoidAtomicIASyncResultReference& Callback, const void* State);

		virtual const Elysium::Core::size EndRead(const Elysium::Core::IAsyncResult* AsyncResult);
		*/
	};
}
#endif
