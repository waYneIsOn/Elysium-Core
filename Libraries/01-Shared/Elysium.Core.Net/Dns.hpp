/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

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
		
		static const Elysium::Core::Collections::Template::Array<Elysium::Core::Net::IPAddress> GetHostAddresses(const Elysium::Core::String& HostNameOrAddress);
		/*
		static const IPHostEntry GetHostEntry(const IPAddress& Address);
		static const IPHostEntry GetHostEntry(const Elysium::Core::String& Address);
		*/
		static const Elysium::Core::String GetHostName();
	private:
		~Dns() { }
	};
}
#endif
