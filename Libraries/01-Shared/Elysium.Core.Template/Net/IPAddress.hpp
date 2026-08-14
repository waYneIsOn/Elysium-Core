/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_NET_IPADDRESS
#define ELYSIUM_CORE_TEMPLATE_NET_IPADDRESS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Container/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMCPY
#include "../Memory/MemCpy.hpp"
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

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CONVERT
#include "../Text/Convert.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRINGVIEW
#include "../Text/StringView.hpp"
#endif

namespace Elysium::Core::Template::Net
{
	class IPAddress
	{
	public:
		inline constexpr IPAddress(const Elysium::Core::Template::Net::Sockets::AddressFamily Family, const Elysium::Core::Template::System::byte* AddressBytes,
			const Elysium::Core::Template::System::size AddressLength) noexcept
			: _Family(Family), _Address(AddressLength)
		{
			// @ToDo: use MemCpy as soon as it's constexpr
			//Elysium::Core::Template::Memory::MemCpy(&_Address[0], Address, 8);
			for (Elysium::Core::Template::System::uint8_t i = 0; i < AddressLength; ++i)
			{
				_Address[i] = AddressBytes[i];
			}
		}
		
		inline constexpr IPAddress(const Elysium::Core::Template::Net::Sockets::AddressFamily Family = Elysium::Core::Template::Net::Sockets::AddressFamily::Unspecified,
			const Elysium::Core::Template::System::uint32_t Address = 0) noexcept
			: IPAddress(Family, reinterpret_cast<const Elysium::Core::Template::System::byte*>(&Address), sizeof(Address))
		{ }

		constexpr IPAddress(const IPAddress& Source) = default;

		constexpr IPAddress(IPAddress&& Right) noexcept = default;

		constexpr ~IPAddress() = default;
	public:
		constexpr IPAddress& operator=(const IPAddress& Source) = default;

		constexpr IPAddress& operator=(IPAddress&& Right) noexcept = default;
	public:
		inline constexpr const Elysium::Core::Template::System::byte* GetAddress() const noexcept
		{
			return &_Address[0];
		}

		inline constexpr const Elysium::Core::Template::Net::Sockets::AddressFamily GetAddressFamily() const noexcept
		{
			return _Family;
		}
	public:
		inline static constexpr const IPAddress& Any() noexcept
		{
			static const Elysium::Core::Template::Net::IPAddress Address(Elysium::Core::Template::Net::Sockets::AddressFamily::Unspecified, 0x00);
			return Address;
		}

		inline static constexpr const IPAddress& Broadcast() noexcept
		{
			static const Elysium::Core::Template::Net::IPAddress Address(Elysium::Core::Template::Net::Sockets::AddressFamily::Unspecified, 0xFFFFFFFF);
			return Address;
		}

		inline static constexpr const IPAddress& IPv6Any() noexcept
		{	// @ToDo
			static const Elysium::Core::Template::Net::IPAddress Address(Elysium::Core::Template::Net::Sockets::AddressFamily::Unspecified, 0x00);
			return Address;
		}
		
		inline static constexpr const IPAddress& IPv6Loopback() noexcept
		{	// @ToDo
			static const Elysium::Core::Template::Net::IPAddress Address(Elysium::Core::Template::Net::Sockets::AddressFamily::Unspecified, 0x00);
			return Address;
		}
		 
		inline static constexpr const IPAddress& IPv6None() noexcept
		{	// @ToDo
			static const Elysium::Core::Template::Net::IPAddress Address(Elysium::Core::Template::Net::Sockets::AddressFamily::Unspecified, 0x00);
			return Address;
		}

		inline static constexpr const IPAddress& Loopback() noexcept
		{
			static const Elysium::Core::Template::Net::IPAddress Address(Elysium::Core::Template::Net::Sockets::AddressFamily::Unspecified, 0x100007F);
			return Address;
		}

		inline static constexpr const IPAddress& None() noexcept
		{	// @ToDo
			static const Elysium::Core::Template::Net::IPAddress Address(Elysium::Core::Template::Net::Sockets::AddressFamily::Unspecified, 0x00);
			return Address;
		}
	public:
		inline static constexpr const IPAddress Parse(const Elysium::Core::Template::Text::StringView<char8_t> Value)
		{
			// @ToDo: implement correctly (127.0.0.1, 127.0.0.1:80 etc.) + IPv6, long etc.

			Elysium::Core::Template::System::size StartIndexIpPart = 0;
			Elysium::Core::Template::System::size EndIndexIpPart = Value.IndexOf('.', StartIndexIpPart);
			const Elysium::Core::Template::System::uint8_t IpPart1 = 
				Elysium::Core::Template::Text::Convert<char8_t>::ToUInt8(&Value[StartIndexIpPart], EndIndexIpPart - StartIndexIpPart, 10);

			StartIndexIpPart = EndIndexIpPart + 1;
			EndIndexIpPart = StartIndexIpPart + Value.IndexOf('.', StartIndexIpPart);
			const Elysium::Core::Template::System::uint8_t IpPart2 = 
				Elysium::Core::Template::Text::Convert<char8_t>::ToUInt8(&Value[StartIndexIpPart], EndIndexIpPart - StartIndexIpPart, 10);

			StartIndexIpPart = EndIndexIpPart + 1;
			EndIndexIpPart = StartIndexIpPart + Value.IndexOf('.', StartIndexIpPart);
			const Elysium::Core::Template::System::uint8_t IpPart3 = 
				Elysium::Core::Template::Text::Convert<char8_t>::ToUInt8(&Value[StartIndexIpPart], EndIndexIpPart - StartIndexIpPart, 10);

			StartIndexIpPart = EndIndexIpPart + 1;
			EndIndexIpPart = Value.GetLength();
			const Elysium::Core::Template::System::uint8_t IpPart4 = 
				Elysium::Core::Template::Text::Convert<char8_t>::ToUInt8(&Value[StartIndexIpPart], EndIndexIpPart - StartIndexIpPart, 10);

			return IPAddress(Elysium::Core::Template::Net::Sockets::AddressFamily::Unspecified, (IpPart1 << 24) + (IpPart2 << 16) + (IpPart3 << 8) + IpPart4);
		}
	private:
		Elysium::Core::Template::Net::Sockets::AddressFamily _Family;
		Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> _Address;
	};
}
#endif
