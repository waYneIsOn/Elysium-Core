/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_NET_DNSENDPOINT
#define ELYSIUM_CORE_TEMPLATE_NET_DNSENDPOINT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_DNS
#include "Dns.hpp"
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

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "../Text/String.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRINGVIEW
#include "../Text/StringView.hpp"
#endif

namespace Elysium::Core::Template::Net
{
	class DnsEndPoint
	{
	public:
		constexpr DnsEndPoint() noexcept = default;

		inline constexpr DnsEndPoint(const Elysium::Core::Template::Text::StringView<char8_t> Host, const Elysium::Core::Template::System::uint16_t Port,
			const Elysium::Core::Template::Net::Sockets::AddressFamily AddressFamily)
			: _Host(&Host[0], Host.GetLength()), _Port(Port), _AddressFamily(AddressFamily)
		{ }

		constexpr DnsEndPoint(const DnsEndPoint& Source) = delete;

		constexpr DnsEndPoint(DnsEndPoint&& Right) noexcept = delete;

		constexpr ~DnsEndPoint() = default;
	public:
		constexpr DnsEndPoint& operator=(const DnsEndPoint& Source) = delete;

		constexpr DnsEndPoint& operator=(DnsEndPoint&& Right) noexcept = delete;
	public:
		inline explicit operator const Elysium::Core::Template::Net::SocketAddress() const noexcept
		{
			const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Net::IPAddress> Addresses = Elysium::Core::Template::Net::Dns::GetHostAddresses(_Host);
			/*
			// @ToDo: can this ever happen? I assume if a server/pc is not connected to anything or all devices have been disabled?
			if (0 == Addresses.GetLength())
			{ }
			*/

			// @ToDo: select "best" address instead of using the first one
			return SocketAddress(Addresses[0], _Port);
		}
	public:
		inline constexpr const Elysium::Core::Template::Net::Sockets::AddressFamily GetAddressFamily() const noexcept
		{
			return _AddressFamily;
		}

		inline constexpr const Elysium::Core::Template::Text::String<char8_t>& GetHost() const noexcept
		{
			return _Host;
		}

		inline constexpr const Elysium::Core::Template::System::uint16_t GetPort() const noexcept
		{
			return _Port;
		}
	private:
		const Elysium::Core::Template::Text::String<char8_t> _Host{};
		const Elysium::Core::Template::System::uint16_t _Port{};
		const Elysium::Core::Template::Net::Sockets::AddressFamily _AddressFamily{};
	};
}
#endif
