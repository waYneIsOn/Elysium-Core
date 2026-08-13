/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_DNSENDPOINT
#define ELYSIUM_CORE_NET_DNSENDPOINT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_NET_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_DNSENDPOINT
#include "../Elysium.Core.Template/Net/DnsEndPoint.hpp"
#endif

namespace Elysium::Core::Net
{
	class ELYSIUM_CORE_NET_API Elysium::Core::Template::Net::DnsEndPoint;

	using DnsEndPoint = Elysium::Core::Template::Net::DnsEndPoint;
}
#endif
