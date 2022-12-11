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

		//IPAddress(const IPAddress& Source);
		 
		//IPAddress(IPAddress&& Right) noexcept;

		~IPAddress();
	public:
		//IPAddress& operator=(const IPAddress& Source);

		//IPAddress& operator=(IPAddress&& Right) noexcept;
	public:
		const Sockets::AddressFamily& GetAddressFamily() const;
	public:
		static const IPAddress& Any();

		static const IPAddress& Broadcast();

		//static const IPAddress& IPv6Any();
		// 
		//static const IPAddress& IPv6Loopback();
		// 
		//static const IPAddress& IPv6None();

		static const IPAddress& Loopback();

		//static const IPAddress& None();

		static const IPAddress Parse(const Elysium::Core::Utf8String& Value);
	private:
		Sockets::AddressFamily _Family;

		Elysium::Core::uint32_t _Address;
	};
}
#endif
