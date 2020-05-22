/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_MEMORYSTREAM
#define ELYSIUM_CORE_IO_MEMORYSTREAM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "Stream.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_LIST
#include "../Elysium.Core/List.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

#pragma warning( disable : 4251 )

namespace Elysium::Core::IO
{
	class ELYSIUM_CORE_API MemoryStream : public Stream
	{
	public:
		MemoryStream();
		MemoryStream(const Collections::Template::Array<byte>& Data, size_t Offset, size_t Length);
		virtual ~MemoryStream();

		// properties - getter
		virtual bool GetCanRead() const override;
		virtual bool GetCanSeek() const override;
		virtual bool GetCanTimeout() const override;
		virtual bool GetCanWrite() const override;

		virtual const size_t GetLength() override;
		virtual const int64_t GetPosition() override;
		virtual const int GetReadTimeout() const override;
		virtual const int GetWriteTimeout() const override;

		virtual size_t GetCapacity() const;

		// properties - setter
		virtual void SetLength(size_t Value) override;
		virtual void SetPosition(int64_t Position) override;

		virtual void SetCapacity(size_t Capacity);

		// methods
		virtual void Close() override;
		virtual void Flush() override;
		virtual void Seek(const int64_t Offset, const SeekOrigin Origin) override;
		virtual size_t Read(byte* Buffer, const size_t Count) override;
		virtual int32_t ReadByte() override;
		virtual void Write(const byte* Buffer, const size_t Count) override;
	private:
		size_t _CurrentPosition = 0;
		Collections::Template::List<byte> _Buffer;
	};
}
#endif
