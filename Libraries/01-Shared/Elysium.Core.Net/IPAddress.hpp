/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_IPADDRESS
#define ELYSIUM_CORE_NET_IPADDRESS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_STRINGVIEW
#include "../Elysium.Core/StringView.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_IPADDRESS
#include "../Elysium.Core.Template/Net/IPAddress.hpp"
#endif

namespace Elysium::Core::Net
{
	class ELYSIUM_CORE_NET_API Elysium::Core::Template::Net::IPAddress;

	using IPAddress = Elysium::Core::Template::Net::IPAddress;
}
#endif
