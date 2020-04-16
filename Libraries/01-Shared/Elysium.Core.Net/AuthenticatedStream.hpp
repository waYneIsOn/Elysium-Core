/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

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

namespace Elysium::Core::Net::Security
{
	class ELYSIUM_CORE_NET_API AuthenticatedStream : public IO::Stream
	{
	public:
		virtual ~AuthenticatedStream();

		const IO::Stream& GetInnerStream() const;
		virtual const bool GetIsAuthenticated() const = 0;
		virtual const bool GetIsEncrypted() const = 0;
		virtual const bool GetIsMutuallyAuthenticated() const = 0;
		virtual const bool GetIsServer() const = 0;
		virtual const bool GetIsSigned() const = 0;
		const bool GetLeaveInnerStreamOpen() const;
	protected:
		AuthenticatedStream(IO::Stream& InnerStream, const bool LeaveInnerStreamOpen);

		Elysium::Core::IO::Stream& _InnerStream;
	private:
		const bool _LeaveInnerStreamOpen;
	};
}
#endif
