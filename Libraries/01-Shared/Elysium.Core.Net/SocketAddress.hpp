/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_SOCKETADDRESS
#define ELYSIUM_CORE_NET_SOCKETADDRESS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_NET_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETADDRESS
#include "../Elysium.Core.Template/Net/SocketAddress.hpp"
#endif

namespace Elysium::Core::Net
{
	class ELYSIUM_CORE_NET_API Elysium::Core::Template::Net::SocketAddress;

	using SocketAddress = Elysium::Core::Template::Net::SocketAddress;
}
#endif
