/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_IPENDPOINT
#define ELYSIUM_CORE_NET_IPENDPOINT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_NET_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_IPENDPOINT
#include "../Elysium.Core.Template/Net/IPEndPoint.hpp"
#endif

namespace Elysium::Core::Net
{
	class ELYSIUM_CORE_NET_API Elysium::Core::Template::Net::IPEndPoint;

	using IPEndPoint = Elysium::Core::Template::Net::IPEndPoint;
}
#endif
