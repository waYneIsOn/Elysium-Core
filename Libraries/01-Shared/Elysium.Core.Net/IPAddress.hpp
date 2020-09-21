/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_IPADDRESS
#define ELYSIUM_CORE_NET_IPADDRESS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_NET_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "../Elysium.Core/Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_ADDRESSFAMILY
#include "AddressFamily.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

namespace Elysium::Core::Net
{
	class ELYSIUM_CORE_NET_API IPAddress final
	{
		friend class SocketAddress;
	public:
		IPAddress();
		IPAddress(const Elysium::Core::uint32_t Address);
		//IPAddress(const IPAddress& Source) = delete;
		//IPAddress(IPAddress&& Right) noexcept = delete;
		~IPAddress();

		//IPAddress& operator=(const IPAddress& Source) = delete;
		//IPAddress& operator=(IPAddress&& Right) noexcept = delete;

		const Sockets::AddressFamily& GetAddressFamily() const;

		static const IPAddress& Any();
		//static const IPAddress& Broadcast();
		//static const IPAddress& IPv6Any();
		//static const IPAddress& IPv6Loopback();
		//static const IPAddress& IPv6None();
		//static const IPAddress& Loopback();
		//static const IPAddress& None();

		static const IPAddress Parse(const Elysium::Core::String& Value);
	private:
		Sockets::AddressFamily _Family;
		Elysium::Core::uint32_t _Address;
	};
}
#endif
