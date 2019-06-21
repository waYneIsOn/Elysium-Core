/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_NET_SECURITY_AUTHENTICATEDSTREAM
#define ELYSIUM_CORE_NET_SECURITY_AUTHENTICATEDSTREAM

#ifndef ELYSIUM_CORE_NET_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "../Elysium.Core.IO/Stream.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Net
		{
			namespace Security
			{
				class ELYSIUM_CORE_NET_API AuthenticatedStream : public Elysium::Core::IO::Stream
				{
				public:
					virtual ~AuthenticatedStream();

					const Elysium::Core::IO::Stream* GetInnerStream() const;
					const bool GetLeaveInnerStreamOpen() const;
				protected:
					AuthenticatedStream(Elysium::Core::IO::Stream& InnerStream, const bool LeaveInnerStreamOpen);
				private:
					Elysium::Core::IO::Stream* _InnerStream;
					bool _LeaveInnerStreamOpen;
				};
			}
		}
	}
}
#endif
