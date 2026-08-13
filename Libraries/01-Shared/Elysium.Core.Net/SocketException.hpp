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

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_NET_SOCKETS_SOCKETEXCEPTION
#include "../Elysium.Core.Template/Exceptions/SocketException.hpp"
#endif

namespace Elysium::Core::Net::Sockets
{
	class ELYSIUM_CORE_NET_API Elysium::Core::Template::Exceptions::Net::Sockets::SocketException;

	using SocketException = Elysium::Core::Template::Exceptions::Net::Sockets::SocketException;
}
#endif
