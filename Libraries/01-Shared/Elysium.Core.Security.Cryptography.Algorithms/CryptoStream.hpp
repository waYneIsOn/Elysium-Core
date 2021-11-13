/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_CRYPTOSTREAM
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_CRYPTOSTREAM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "../Elysium.Core.IO/Stream.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_CRYPTOSTREAMMODE
#include "CryptoStreamMode.hpp"
#endif

namespace Elysium::Core::Security::Cryptography
{
	/*
	class ELYSIUM_CORE_SECURITY_API CryptoStream final : public Elysium::Core::IO::Stream
	{
	public:
		CryptoStream(Elysium::Core::IO::Stream& UnderlyingStream, const CryptoStreamMode Mode, const bool LeaveOpen);

		CryptoStream(const CryptoStream& Source) = delete;

		CryptoStream(CryptoStream&& Right) noexcept = delete;

		virtual ~CryptoStream();
	public:
		CryptoStream& operator=(const CryptoStream& Source) = delete;

		CryptoStream& operator=(CryptoStream&& Right) noexcept = delete;
	public:
		virtual const bool GetCanRead() const = 0;

		virtual const bool GetCanSeek() const = 0;

		virtual const bool GetCanWrite() const = 0;

		virtual const Elysium::Core::size GetLength() const = 0;

		virtual void SetLength(const Elysium::Core::size Value) = 0;

		virtual void SetPosition(const Elysium::Core::uint64_t Position) = 0;

		virtual void Close() = 0;

		virtual void Flush() = 0;

		virtual const Elysium::Core::size Seek(const int64_t Offset, const IO::SeekOrigin Origin) = 0;

		virtual const Elysium::Core::size Read(Elysium::Core::byte* Buffer, const Elysium::Core::size Count) = 0;

		virtual Elysium::Core::byte ReadByte() = 0;

		virtual void Write(const Elysium::Core::byte* Buffer, const Elysium::Core::size Count) = 0;
	};
	*/
}
#endif
