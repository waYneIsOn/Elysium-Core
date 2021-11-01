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

#ifndef ELYSIUM_CORE_BYTE
#include "../Elysium.Core/Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_LIST
#include "../Elysium.Core/List.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LISTOFBYTE
#include "../Elysium.Core/ListOfByte.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::IO
{
	class ELYSIUM_CORE_API MemoryStream : public Stream
	{
	public:
		MemoryStream();
		MemoryStream(const Elysium::Core::size Capacity);
		MemoryStream(const byte* Data, Elysium::Core::size Length);
		MemoryStream(const Collections::Template::Array<byte>& Data, Elysium::Core::size Offset, Elysium::Core::size Length);
		virtual ~MemoryStream();

		virtual const bool GetCanRead() const override;
		virtual const bool GetCanSeek() const override;
		virtual const bool GetCanTimeout() const override;
		virtual const bool GetCanWrite() const override;

		virtual const Elysium::Core::size GetLength() const override;
		virtual const Elysium::Core::uint64_t GetPosition() const override;
		virtual const Elysium::Core::uint32_t GetReadTimeout() const override;
		virtual const Elysium::Core::uint32_t GetWriteTimeout() const override;

		virtual const Elysium::Core::size GetCapacity() const;

		virtual void SetLength(const Elysium::Core::size Value) override;
		virtual void SetPosition(const Elysium::Core::uint64_t Position) override;

		virtual void SetCapacity(const Elysium::Core::size Capacity);

		virtual void Close() override;
		virtual void Flush() override;
		virtual const Elysium::Core::size Seek(const Elysium::Core::int64_t Offset, const SeekOrigin Origin) override;
		virtual const Elysium::Core::size Read(Elysium::Core::byte* Buffer, const Elysium::Core::size Count) override;
		virtual Elysium::Core::byte ReadByte() override;
		virtual void Write(const Elysium::Core::byte* Buffer, const Elysium::Core::size Count) override;
	private:
		Elysium::Core::size _CurrentPosition = 0;
		Collections::Template::List<byte> _Buffer;
	};
}
#endif
