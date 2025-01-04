/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_DNS
#define ELYSIUM_CORE_NET_DNS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_NET_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Elysium.Core.Template/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_IPADDRESS
#include "IPAddress.hpp"
#endif

namespace Elysium::Core::Net
{
	class ELYSIUM_CORE_NET_API Dns final
	{
	public:
		Dns() = delete;
		
		static const Elysium::Core::Template::Container::Vector<Elysium::Core::Net::IPAddress> GetHostAddresses(const Elysium::Core::Utf8String& HostNameOrAddress);
		/*
		static const IPHostEntry GetHostEntry(const IPAddress& Address);
		static const IPHostEntry GetHostEntry(const Elysium::Core::Utf8String& Address);
		*/
		static const Elysium::Core::Utf8String GetHostName();
	private:
		~Dns() { }
	};
}
#endif
