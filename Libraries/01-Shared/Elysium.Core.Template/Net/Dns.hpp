/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_NET_DNS
#define ELYSIUM_CORE_TEMPLATE_NET_DNS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Container/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_SYSTEMEXCEPTION
#include "../Exceptions/SystemException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_IPADDRESS
#include "IPAddress.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "../Text/String.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRINGVIEW
#include "../Text/StringView.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF16
#include "../Text/Unicode/Utf16.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
	#ifndef _SYSINFOAPI_H_
	#include <sysinfoapi.h>
	#endif

	#ifndef _WS2TCPIP_H_
	#include <WS2tcpip.h>
	#endif
#else
#error "unsupported os"
#endif


namespace Elysium::Core::Template::Net
{
	class Dns
	{
	public:
		constexpr Dns() noexcept = delete;

		constexpr Dns(const Dns& Source) = delete;

		constexpr Dns(Dns&& Right) noexcept = delete;

		constexpr ~Dns() = delete;
	public:
		constexpr Dns& operator=(const Dns& Source) = delete;

		constexpr Dns& operator=(Dns&& Right) noexcept = delete;
	public:
		inline static Elysium::Core::Template::Text::String<char8_t> GetHostName()
		{
#if defined ELYSIUM_CORE_OS_WINDOWS
			return GetHostName(_COMPUTER_NAME_FORMAT::ComputerNameDnsHostname);
#endif
			// @ToDo
			return u8"";
		}

		inline static Elysium::Core::Template::Text::String<char8_t> GetFQHostName()
		{
#if defined ELYSIUM_CORE_OS_WINDOWS
			return GetHostName(_COMPUTER_NAME_FORMAT::ComputerNameDnsFullyQualified);
#endif
			// @ToDo
			return u8"";
		}

		inline static Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Net::IPAddress> GetHostAddresses(const Elysium::Core::Template::Text::StringView<char8_t> HostNameOrAdddress)
		{
#if defined ELYSIUM_CORE_OS_WINDOWS
			Elysium::Core::Template::Text::String<wchar_t> NameOrAddress = Elysium::Core::Template::Text::Unicode::Utf16::SafeToWideString(&HostNameOrAdddress[0], HostNameOrAdddress.GetLength());

			ADDRINFOW Hints{};
			Hints.ai_family = AF_UNSPEC;   // IPv4 + IPv6
			Hints.ai_socktype = SOCK_STREAM;

			ADDRINFOW* AddressInfos = nullptr;

			//INT QueryResult = GetAddrInfoExW()
			INT QueryResult = GetAddrInfoW(&NameOrAddress[0], nullptr, &Hints, &AddressInfos);
			if (0 != QueryResult)
			{
				// @ToDo: GetLastError() appears to be the wrong method here.
				// I should probably use gai_strerror() or gai_strerrorW() - need to check!
				throw;
			}

			Elysium::Core::Template::System::size ResultLength = 0;
			for (ADDRINFOW* CurrentAddressInfo = AddressInfos; nullptr != CurrentAddressInfo; CurrentAddressInfo = CurrentAddressInfo->ai_next)
			{
				++ResultLength;
			}


			Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Net::IPAddress> Result(ResultLength);
			ResultLength = 0;
			for (ADDRINFOW* AddressInfo = AddressInfos; AddressInfo != nullptr; AddressInfo = AddressInfo->ai_next)
			{
				// @ToDo: use actual address types (sockaddr_in, sockaddr_in6 etc.)
				Elysium::Core::Template::System::uint32_t Address = *reinterpret_cast<Elysium::Core::Template::System::uint32_t*>(&AddressInfo->ai_addr->sa_data[2]);

				switch (AddressInfo->ai_family)
				{
				case AF_UNSPEC:
				{
					Result[ResultLength++] = { Elysium::Core::Template::Net::Sockets::AddressFamily::Unspecified, Address };
				}
					break;
				case AF_INET:
				{
					sockaddr_in* address = reinterpret_cast<sockaddr_in*>(AddressInfo->ai_addr);
					Result[ResultLength++] = { Elysium::Core::Template::Net::Sockets::AddressFamily::InterNetwork, Address };
				}
					break;
				case AF_NETBIOS:
				{
					Result[ResultLength++] = { Elysium::Core::Template::Net::Sockets::AddressFamily::NetBios, Address };
				}
					break;
				case AF_INET6:
				{
					sockaddr_in6* address = reinterpret_cast<sockaddr_in6*>(AddressInfo->ai_addr);
					Result[ResultLength++] = { Elysium::Core::Template::Net::Sockets::AddressFamily::InterNetworkV6, Address };
				}
					break;
				case AF_IRDA:
				{
					Result[ResultLength++] = { Elysium::Core::Template::Net::Sockets::AddressFamily::AtmIrda, Address };
				}
					break;
				case AF_BTH:
				{
					// @ToDo
					throw;
					/*
					Result[ResultLength++] = { Elysium::Core::Template::Net::Sockets::AddressFamily::Bluetooth, Address };
					break;
					*/
				}
					break;
				default:
					// seems like there are new values! https://learn.microsoft.com/en-us/windows/win32/api/ws2def/ns-ws2def-addrinfow
					throw;
				}
			}
			FreeAddrInfoW(AddressInfos);

			return Result;
#endif
			
			// @ToDo
			return {};
		}
	private:
		inline static Elysium::Core::Template::Text::String<char8_t> GetHostName(const _COMPUTER_NAME_FORMAT NameFormat)
		{
#if defined ELYSIUM_CORE_OS_WINDOWS

			DWORD RequiredLength = 0;
			BOOL InitialQueryResult = GetComputerNameExW(NameFormat, nullptr, &RequiredLength);
			if (FALSE == InitialQueryResult)
			{
				const DWORD ErrorCode = GetLastError();
				if (ERROR_MORE_DATA != ErrorCode)
				{
					throw Elysium::Core::Template::Exceptions::SystemException();
				}
			}

			Elysium::Core::Template::Container::Vector<wchar_t> Buffer(RequiredLength);
			BOOL QueryResult = GetComputerNameExW(NameFormat, &Buffer[0], &RequiredLength);
			if (FALSE == QueryResult)
			{
				throw Elysium::Core::Template::Exceptions::SystemException();
			}

			return Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<char8_t>(&Buffer[0], RequiredLength);
#endif
		}
	};
}
#endif