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

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Functional/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMCPY
#include "../Memory/MemCpy.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_IPADDRESS
#include "IPAddress.hpp"
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
		inline constexpr const Elysium::Core::Template::Net::Sockets::AddressFamily GetAddressFamily() const noexcept
		{
			return _Address.GetAddressFamily();
		}

		inline constexpr const Elysium::Core::Template::System::uint16_t GetPort() const noexcept
		{
			return _Port;
		}
	public:
#if defined ELYSIUM_CORE_OS_WINDOWS
		inline sockaddr_storage Serialize(socklen_t& Length) const
		{
			sockaddr_storage Result{};
			switch (_Address.GetAddressFamily())
			{
			case Elysium::Core::Template::Net::Sockets::AddressFamily::InterNetwork:
			{
				sockaddr_in* NativeAddress = reinterpret_cast<sockaddr_in*>(&Result);
				NativeAddress->sin_family = AF_INET;
				NativeAddress->sin_port = htons(_Port);
				Elysium::Core::Template::Memory::MemCpy(&NativeAddress->sin_addr, _Address.GetAddress(), sizeof(NativeAddress->sin_addr));

				Length = sizeof(sockaddr_in);
			}
			break;
			case Elysium::Core::Template::Net::Sockets::AddressFamily::InterNetworkV6:
			{
				sockaddr_in6* NativeAddress = reinterpret_cast<sockaddr_in6*>(&Result);
				NativeAddress->sin6_family = AF_INET6;
				NativeAddress->sin6_port = htons(_Port);
				Elysium::Core::Template::Memory::MemCpy(&NativeAddress->sin6_addr, _Address.GetAddress(), sizeof(NativeAddress->sin6_addr));
				//NativeAddress->sin6_scope_id = scope_id_;

				Length = sizeof(sockaddr_in6);
			}
			break;
			default:
				// @ToDo
				throw;
			}

			return Result;
		}
#endif
	private:
		Elysium::Core::Template::Net::IPAddress _Address{};
		Elysium::Core::Template::System::uint16_t _Port{};
	};
}
#endif
