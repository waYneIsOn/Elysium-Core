/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_STREAM
#define ELYSIUM_CORE_IO_STREAM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "../Elysium.Core/Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_IASYNCRESULT
#include "../Elysium.Core/IAsyncResult.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_SEEKORIGIN
#include "SeekOrigin.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DELEGATE
#include "../Elysium.Core.Template/Delegate.hpp"
#endif

namespace Elysium::Core::IO
{
	class ELYSIUM_CORE_API Stream
	{
	protected:
		Stream();
	public:
		Stream(const Stream& Source) = delete;

		Stream(Stream&& Right) noexcept = delete;

		virtual ~Stream();
	public:
		Stream& operator=(const Stream& Source) = delete;

		Stream& operator=(Stream&& Right) noexcept = delete;
		/*
		Stream& operator<<(const Elysium::Core::byte Value);

		Stream& operator<<(const Elysium::Core::uint32_t Value);

		Stream& operator>>(const Elysium::Core::uint32_t Value);
		*/
	public:
		virtual const bool GetCanRead() const = 0;

		virtual const bool GetCanSeek() const = 0;

		virtual const bool GetCanTimeout() const;

		virtual const bool GetCanWrite() const = 0;

		virtual const Elysium::Core::size GetLength() const = 0;

		virtual const Elysium::Core::uint64_t GetPosition() const;

		virtual const Elysium::Core::uint32_t GetReadTimeout() const;

		virtual const Elysium::Core::uint32_t GetWriteTimeout() const;

		virtual void SetLength(const Elysium::Core::size Value) = 0;

		virtual void SetPosition(const Elysium::Core::uint64_t Position) = 0;

		virtual void SetReadTimeout(const Elysium::Core::uint32_t Value);

		virtual void SetWriteTimeout(const Elysium::Core::uint32_t Value);

		virtual void CopyTo(Stream& Destination);

		virtual void CopyTo(Stream& Destination, const Elysium::Core::size BufferSize);

		virtual void Close() = 0;

		virtual void Flush() = 0;

		virtual const Elysium::Core::size Seek(const int64_t Offset, const SeekOrigin Origin) = 0;

		virtual const Elysium::Core::size Read(Elysium::Core::byte* Buffer, const Elysium::Core::size Count) = 0;

		virtual Elysium::Core::byte ReadByte() = 0;

		virtual void Write(const Elysium::Core::byte* Buffer, const Elysium::Core::size Count) = 0;

		virtual void WriteByte(const Elysium::Core::byte Value);

		virtual const Elysium::Core::IAsyncResult* BeginWrite(const Elysium::Core::byte* Buffer, const Elysium::Core::size Size,
			const Elysium::Core::Template::Container::Delegate<void, const Elysium::Core::IAsyncResult*>& Callback, const void* State);

		virtual void EndWrite(const Elysium::Core::IAsyncResult* AsyncResult);

		virtual const Elysium::Core::IAsyncResult* BeginRead(const Elysium::Core::byte* Buffer, const Elysium::Core::size Size,
			const Elysium::Core::Template::Container::Delegate<void, const Elysium::Core::IAsyncResult*>& Callback, const void* State);

		virtual const Elysium::Core::size EndRead(const Elysium::Core::IAsyncResult* AsyncResult);
	};
}
#endif
