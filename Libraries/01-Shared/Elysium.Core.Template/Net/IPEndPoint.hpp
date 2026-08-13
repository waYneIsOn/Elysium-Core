/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_NET_IPENDPOINT
#define ELYSIUM_CORE_TEMPLATE_NET_IPENDPOINT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_IPADDRESS
#include "IPAddress.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETADDRESS
#include "SocketAddress.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_ADDRESSFAMILY
#include "Sockets/AddressFamily.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Net
{
	class IPEndPoint
	{
	public:
		constexpr IPEndPoint() noexcept = default;

		inline constexpr IPEndPoint(const Elysium::Core::Template::Net::IPAddress Address, const Elysium::Core::Template::System::uint16_t Port)
			: _Address(Address), _Port(Port)
		{ }

		constexpr IPEndPoint(const IPEndPoint& Source) = default;

		constexpr IPEndPoint(IPEndPoint&& Right) noexcept = default;

		constexpr ~IPEndPoint() = default;
	public:
		constexpr IPEndPoint& operator=(const IPEndPoint& Source) = default;

		constexpr IPEndPoint& operator=(IPEndPoint&& Right) noexcept = default;
	public:
		inline explicit operator const Elysium::Core::Template::Net::SocketAddress() const noexcept
		{
			return { _Address, _Port };
		}
	public:
		inline constexpr const Elysium::Core::Template::Net::Sockets::AddressFamily GetAddressFamily() const noexcept
		{
			return _Address.GetAddressFamily();
		}

		inline constexpr const Elysium::Core::Template::System::uint16_t GetPort() const noexcept
		{
			return _Port;
		}
	private:
		Elysium::Core::Template::Net::IPAddress _Address{};
		Elysium::Core::Template::System::uint16_t _Port{};
	};
}
#endif
