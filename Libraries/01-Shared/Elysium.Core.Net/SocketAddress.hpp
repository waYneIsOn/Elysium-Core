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

#ifndef ELYSIUM_CORE_NET_SOCKETS_ADDRESSFAMILY
#include "AddressFamily.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_IPADDRESS
#include "IPAddress.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "../Elysium.Core/Byte.hpp"
#endif

namespace Elysium::Core::Net
{
	class SocketAddress final
	{
		friend class DnsEndPoint;
		friend class IPEndPoint;
	public:
		SocketAddress(const Elysium::Core::Net::Sockets::AddressFamily AddressFamily, const Elysium::Core::uint8_t Size);
		SocketAddress(const Elysium::Core::Net::Sockets::AddressFamily AddressFamily);
		SocketAddress(const SocketAddress& Source) = delete;
		SocketAddress(SocketAddress&& Right) noexcept = delete;
		~SocketAddress();

		SocketAddress& operator=(const SocketAddress& Source) = delete;
		SocketAddress& operator=(SocketAddress&& Right) noexcept = delete;

		const Elysium::Core::Net::Sockets::AddressFamily GetFamily() const;
		const Elysium::Core::byte& operator[](size_t Index) const;
		const Elysium::Core::uint8_t GetSize() const;
	private:
		SocketAddress(const IPAddress& Address);
		SocketAddress(const IPAddress& Address, const Elysium::Core::uint16_t Port);

		static const Elysium::Core::uint8_t IPv6AddressSize = 28;	// 2 byte address family, 26 byte rest (???)
		static const Elysium::Core::uint8_t IPv4AddressSize = 16;	// 2 byte address family, 14 byte rest (2 byte port? 12 byte ip?)

		static const Elysium::Core::uint8_t WriteableOffset = 2;	// first two bytes contain address family
		static const Elysium::Core::uint8_t MaxSize = 32;

		// DO NOT CHANGE THE ORDER OF FIELDS!
		char _Data[MaxSize];
		const Elysium::Core::uint8_t _Size;
	};
}
#endif
