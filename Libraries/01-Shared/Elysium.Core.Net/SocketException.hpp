/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKETEXCEPTION
#define ELYSIUM_CORE_NET_SOCKETS_SOCKETEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_NET_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_RUNTIME_INTEROPSERVICES_EXTERNALEXCEPTION
#include "../Elysium.Core/ExternalException.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKETERROR
#include "SocketError.hpp"
#endif

namespace Elysium::Core::Net::Sockets
{
	/// <summary>
	/// 
	/// </summary>
	class ELYSIUM_CORE_NET_API SocketException : public Elysium::Core::Runtime::InteropServices::ExternalException
	{
	public:
		SocketException();

		SocketException(const Elysium::Core::int32_t ErrorCode);

		virtual ~SocketException();
	public:
		const SocketError GetSocketError() const;
	};
}
#endif
