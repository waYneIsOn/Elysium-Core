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
			Hints.ai_family = AF_UNSPEC;
			Hints.ai_socktype = SOCK_STREAM;

			// @ToDo: use extended
			//ADDRINFOEXW* AddressInfosEx = nullptr;
			//INT QueryResult = GetAddrInfoExW(&NameOrAddress[0], nullptr, ..., ..., &Hints, &AddressInfosEx, ..., ..., ..., ...);
			ADDRINFOW* AddressInfos = nullptr;
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
				switch (AddressInfo->ai_family)
				{
				case AF_UNSPEC:
				{
					// @ToDo: inspect to select corresponding struct
					throw;
				}
					break;
				case AF_INET:
				{
					const sockaddr_in* Address = reinterpret_cast<sockaddr_in*>(AddressInfo->ai_addr);
					Result[ResultLength++] = { Elysium::Core::Template::Net::Sockets::AddressFamily::InterNetwork,
						reinterpret_cast<const Elysium::Core::Template::System::byte*>(&Address->sin_addr), sizeof(Address->sin_addr) };
				}
					break;
				case AF_UNIX:
				{
					// @ToDo
					//const SOCKADDR_UN* Address = reinterpret_cast<SOCKADDR_UN*>(AddressInfo->ai_addr);
					throw;
				}
					break;
				case AF_IPX:
				{
					// @ToDo
					//const SOCKADDR_IPX* Address = reinterpret_cast<SOCKADDR_IPX*>(AddressInfo->ai_addr);
					throw;
				}
					break;
				case AF_NETBIOS:
				{
					// @ToDo
					//const SOCKADDR_NB* Address = reinterpret_cast<SOCKADDR_NB*>(AddressInfo->ai_addr);
					throw;
				}
					break;
				case AF_ATM:
				{
					// @ToDo
					//const sockaddr_atm* Address = reinterpret_cast<sockaddr_atm*>(AddressInfo->ai_addr);
					throw;
				}
					break;
				case AF_INET6:
				{
					const sockaddr_in6* Address = reinterpret_cast<sockaddr_in6*>(AddressInfo->ai_addr);
					Result[ResultLength++] = { Elysium::Core::Template::Net::Sockets::AddressFamily::InterNetworkV6, 
						reinterpret_cast<const Elysium::Core::Template::System::byte*>(&Address->sin6_addr), sizeof(Address->sin6_addr) };
				}
					break;
				case AF_IRDA:
				{
					// @ToDo
					//const SOCKADDR_IRDA* Address = reinterpret_cast<SOCKADDR_IRDA*>(AddressInfo->ai_addr);
					throw;
				}
					break;
				case AF_BTH:
				{
					// @ToDo
					//const SOCKADDR_BTH* Address = reinterpret_cast<SOCKADDR_BTH*>(AddressInfo->ai_addr);
					throw;
				}
					break;
				case AF_HYPERV:
				{
					// @ToDo
					//const SOCKADDR_HV* Address = reinterpret_cast<SOCKADDR_HV*>(AddressInfo->ai_addr);
					throw;
				}
					break;
				default:
					// unknown, historical or provider-specific family
					// seems like there are new families that are get returned! https://learn.microsoft.com/en-us/windows/win32/api/ws2def/ns-ws2def-addrinfow
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