/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_IO_STREAM
#define ELYSIUM_CORE_IO_STREAM

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "../Elysium.Core/Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_SEEKORIGIN
#include "SeekOrigin.hpp"
#endif

#ifndef _STDINT_H
#include <cstdint>
#endif

#include <ostream>

namespace Elysium
{
	namespace Core
	{
		namespace IO
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
				virtual bool GetCanRead() const = 0;
				virtual bool GetCanSeek() const = 0;
				virtual bool GetCanTimeout() const;
				virtual bool GetCanWrite() const = 0;

				virtual size_t GetLength() const = 0;
				virtual int64_t GetPosition() const;
				virtual int GetReadTimeout() const;
				virtual int GetWriteTimeout() const;

				// properties - setter
				virtual void SetLength(size_t Value) = 0;
				virtual void SetPosition(int64_t Position) = 0;
				virtual void SetReadTimeout(int Value);
				virtual void SetWriteTimeout(int Value);

				// methods
				virtual void CopyTo(Stream* Destination);
				virtual void CopyTo(Stream* Destination, const size_t BufferSize);
				virtual void Close() = 0;
				virtual void Flush() = 0;
				virtual void Seek(const int64_t Offset, const SeekOrigin Origin) = 0;
				virtual size_t Read(byte* Buffer, const size_t Count) = 0;
				virtual void Write(const byte* Buffer, const size_t Count) = 0;

				// stream extraction and insertion
				Elysium::Core::IO::Stream& operator<<(const byte& Value);
				Elysium::Core::IO::Stream& operator<<(const unsigned int& Value);

				Elysium::Core::IO::Stream& operator>>(const unsigned int Value);
			protected:
				// constructors
				Stream();
			};
		}
	}
}
#endif
