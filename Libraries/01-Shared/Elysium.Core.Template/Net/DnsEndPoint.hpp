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

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Functional/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_DNS
#include "Dns.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_IPENDPOINT
#include "IPEndPoint.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_ADDRESSFAMILY
#include "Sockets/AddressFamily.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../System/OperatingSystem.hpp"
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

#if defined ELYSIUM_CORE_OS_WINDOWS
	#ifndef _WS2DEF_
	#include <ws2def.h>
	#endif

	#ifndef _WS2TCPIP_H_
	#include <WS2tcpip.h>
	#endif
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

		inline constexpr DnsEndPoint(const DnsEndPoint& Source)
			: _Host(Source._Host), _Port(Source._Port), _AddressFamily(Source._AddressFamily)
		{ }

		inline constexpr DnsEndPoint(DnsEndPoint&& Right) noexcept
			: _Host{}, _Port{}, _AddressFamily{}
		{
			*this = Functional::Move(Right);
		}

		constexpr ~DnsEndPoint() = default;
	public:
		inline constexpr DnsEndPoint& operator=(const DnsEndPoint& Source)
		{
			if (this != &Source)
			{
				_Host = Source._Host;
				_Port = Source._Port;
				_AddressFamily = Source._AddressFamily;
			}
			return *this;
		}

		constexpr DnsEndPoint& operator=(DnsEndPoint&& Right) noexcept
		{
			if (this != &Right)
			{
				_Host = Elysium::Core::Template::Functional::Move(Right._Host);
				_Port = Elysium::Core::Template::Functional::Move(Right._Port);
				_AddressFamily = Elysium::Core::Template::Functional::Move(Right._AddressFamily);

				Right._Host = {};
				Right._Port = 0;
				Right._AddressFamily = Elysium::Core::Template::Net::Sockets::AddressFamily::Unspecified;
			}
			return *this;
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
	public:
#if defined ELYSIUM_CORE_OS_WINDOWS
		inline sockaddr_storage Serialize(socklen_t& Length) const
		{
			// As long as Dns::GetHostAddresses(...) requests ip-addresses using AF_UNSPEC, the first entry is the system's preferred address.
			// Ergo it makes sense to use it!
			const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Net::IPAddress> Addresses = Elysium::Core::Template::Net::Dns::GetHostAddresses(_Host);
			Elysium::Core::Template::Net::IPEndPoint SelectedEndPoint(Addresses[0], _Port);

			return SelectedEndPoint.Serialize(Length);
		}
#endif
	private:
		Elysium::Core::Template::Text::String<char8_t> _Host{};
		Elysium::Core::Template::System::uint16_t _Port{};
		Elysium::Core::Template::Net::Sockets::AddressFamily _AddressFamily{};
	};
}
#endif
