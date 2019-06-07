/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKETEXCEPTION
#define ELYSIUM_CORE_NET_SOCKETS_SOCKETEXCEPTION

#ifndef ELYSIUM_CORE_NET_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_RUNTIME_INTEROPSERVICES_EXTERNALEXCEPTION
#include "../Elysium.Core/ExternalException.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKETERROR
#include "SocketError.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Net
		{
			namespace Sockets
			{
				/// <summary>
				/// 
				/// </summary>
				class ELYSIUM_CORE_NET_API SocketException : public Elysium::Core::Runtime::InteropServices::ExternalException
				{
				public:
					// constructors & destructor
					SocketException();
					SocketException(const String& Message);
					SocketException(const String& Message, const int ErrorCode);
					~SocketException();
				};
			}
		}
	}
}
#endif
