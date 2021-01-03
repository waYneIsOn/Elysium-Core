/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

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
		MemoryStream(const size_t Capacity);
		MemoryStream(const byte* Data, size_t Length);
		MemoryStream(const Collections::Template::Array<byte>& Data, size_t Offset, size_t Length);
		virtual ~MemoryStream();

		// properties - getter
		virtual const bool GetCanRead() const override;
		virtual const bool GetCanSeek() const override;
		virtual const bool GetCanTimeout() const override;
		virtual const bool GetCanWrite() const override;

		virtual const size_t GetLength() const override;
		virtual const Elysium::Core::uint64_t GetPosition() const override;
		virtual const Elysium::Core::uint32_t GetReadTimeout() const override;
		virtual const Elysium::Core::uint32_t GetWriteTimeout() const override;

		virtual const size_t GetCapacity() const;

		// properties - setter
		virtual void SetLength(const size_t Value) override;
		virtual void SetPosition(const Elysium::Core::uint64_t Position) override;

		virtual void SetCapacity(const size_t Capacity);

		// methods
		virtual void Close() override;
		virtual void Flush() override;
		virtual const size_t Seek(const Elysium::Core::int64_t Offset, const SeekOrigin Origin) override;
		virtual const size_t Read(Elysium::Core::byte* Buffer, const size_t Count) override;
		virtual Elysium::Core::byte ReadByte() override;
		virtual void Write(const Elysium::Core::byte* Buffer, const size_t Count) override;
	private:
		size_t _CurrentPosition = 0;
		Collections::Template::List<byte> _Buffer;
	};
}
#endif
