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

#ifndef ELYSIUM_CORE_IO_SEEKORIGIN
#include "SeekOrigin.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::IO
{
	/// <summary>
	/// 
	/// </summary>
	class ELYSIUM_CORE_API Stream
	{
	public:
		// destructor
		virtual ~Stream() {}

		// properties - getter
		virtual const bool GetCanRead() const = 0;
		virtual const bool GetCanSeek() const = 0;
		virtual const bool GetCanTimeout() const;
		virtual const bool GetCanWrite() const = 0;

		virtual const size_t GetLength() const = 0;
		virtual const Elysium::Core::int64_t GetPosition() const;
		virtual const Elysium::Core::int32_t GetReadTimeout() const;
		virtual const Elysium::Core::int32_t GetWriteTimeout() const;

		// properties - setter
		virtual void SetLength(const size_t Value) = 0;
		virtual void SetPosition(const Elysium::Core::int64_t Position) = 0;
		virtual void SetReadTimeout(const Elysium::Core::int32_t Value);
		virtual void SetWriteTimeout(const Elysium::Core::int32_t Value);

		// methods
		virtual void CopyTo(Stream& Destination);
		virtual void CopyTo(Stream& Destination, const size_t BufferSize);
		virtual void Close() = 0;
		virtual void Flush() = 0;
		virtual void Seek(const int64_t Offset, const SeekOrigin Origin) = 0;
		virtual const size_t Read(Elysium::Core::byte* Buffer, const size_t Count) = 0;
		virtual Elysium::Core::byte ReadByte() = 0;
		virtual void Write(const Elysium::Core::byte* Buffer, const size_t Count) = 0;
		virtual void WriteByte(const Elysium::Core::byte Value);

		// stream extraction and insertion
		Elysium::Core::IO::Stream& operator<<(const byte& Value);
		Elysium::Core::IO::Stream& operator<<(const unsigned int& Value);

		Elysium::Core::IO::Stream& operator>>(const unsigned int Value);
	protected:
		// constructors
		Stream();
	};
}
#endif
