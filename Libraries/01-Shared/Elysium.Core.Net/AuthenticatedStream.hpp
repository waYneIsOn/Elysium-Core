/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_SECURITY_AUTHENTICATEDSTREAM
#define ELYSIUM_CORE_NET_SECURITY_AUTHENTICATEDSTREAM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_NET_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "../Elysium.Core.IO/Stream.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

namespace Elysium::Core::Net::Security
{
	class ELYSIUM_CORE_NET_API AuthenticatedStream 
		: public IO::Stream
	{
	protected:
		AuthenticatedStream(IO::Stream& InnerStream, const bool LeaveInnerStreamOpen);
	public:
		virtual ~AuthenticatedStream() = default;
	public:
		virtual const bool GetCanRead() const override;

		virtual const bool GetCanSeek() const override;

		virtual const bool GetCanTimeout() const override;

		virtual const bool GetCanWrite() const override;

		virtual const Elysium::Core::size GetLength() const override;
	public:
		const IO::Stream& GetInnerStream() const;

		const bool GetLeaveInnerStreamOpen() const;
	public:
		virtual const bool GetIsAuthenticated() const = 0;

		virtual const bool GetIsEncrypted() const = 0;

		virtual const bool GetIsMutuallyAuthenticated() const = 0;

		virtual const bool GetIsServer() const = 0;

		virtual const bool GetIsSigned() const = 0;
	public:
		virtual void SetLength(const Elysium::Core::size Value) override;

		virtual void SetPosition(const Elysium::Core::uint64_t Position) override;
	public:
		virtual void Close() override;
	protected:
		Elysium::Core::IO::Stream& _InnerStream;
	private:
		const bool _LeaveInnerStreamOpen;
	};
}
#endif
