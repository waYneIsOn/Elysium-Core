/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_READONLYSTREAM
#define ELYSIUM_CORE_IO_READONLYSTREAM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "Stream.hpp"
#endif

namespace Elysium::Core::IO
{
	class ELYSIUM_CORE_API ReadOnlyStream : public Stream
	{
	public:
		ReadOnlyStream(Stream& BaseStream, const Elysium::Core::uint64_t Start, const Elysium::Core::uint64_t End);
		ReadOnlyStream(const ReadOnlyStream& Source) = delete;
		ReadOnlyStream(ReadOnlyStream&& Right) noexcept = delete;
		virtual ~ReadOnlyStream();

		ReadOnlyStream& operator=(const ReadOnlyStream& Source) = delete;
		ReadOnlyStream& operator=(ReadOnlyStream&& Right) noexcept = delete;

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
		const Elysium::Core::uint64_t _Start;
		const Elysium::Core::uint64_t _End;

		Elysium::Core::uint64_t _Position;
	};
}
#endif
