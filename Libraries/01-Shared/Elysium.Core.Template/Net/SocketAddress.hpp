/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETADDRESS
#define ELYSIUM_CORE_TEMPLATE_NET_SOCKETADDRESS

#ifdef _MSC_VER
#pragma once
#endif
/*
#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMSET
#include "../Memory/MemSet.hpp"
#endif
*/
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

namespace Elysium::Core::Template::Net
{
	class SocketAddress
	{
	private:
		friend class DnsEndPoint;
		friend class IPEndPoint;
	public:
		constexpr SocketAddress() = delete;
	private:
		inline constexpr SocketAddress(const Elysium::Core::Template::Net::IPAddress Address, const Elysium::Core::Template::System::uint16_t Port = 0)
			: SocketAddress(Address.GetAddressFamily(), Address.GetAddressFamily() == Elysium::Core::Template::Net::Sockets::AddressFamily::InterNetwork ? IPv4AddressSize : IPv6AddressSize)
		{
			// @ToDo
			if (Address.GetAddressFamily() == Elysium::Core::Template::Net::Sockets::AddressFamily::InterNetworkV6)
			{
				throw;
			}
			else
			{
				if (0 != Port)
				{
					_Data[2] = static_cast<char>(Port >> 8);
					_Data[3] = static_cast<char>(Port);
				}

				// @ToDo
				throw;
				/*
				const Elysium::Core::Template::System::uint32_t ActualAddress = Address.GetAddress();

				_Data[4] = static_cast<char>(ActualAddress >> 24);
				_Data[5] = static_cast<char>(ActualAddress >> 16);
				_Data[6] = static_cast<char>(ActualAddress >> 8);
				_Data[7] = static_cast<char>(ActualAddress);
				*/
			}
		}
	public:
		inline constexpr SocketAddress(const Elysium::Core::Template::Net::Sockets::AddressFamily AddressFamily, const Elysium::Core::Template::System::uint8_t Size = MaxSize)
			: _Data{}, _Size(Size < WriteableOffset ? WriteableOffset : Size)
		{
			//Elysium::Core::Template::Memory::MemSet(&_Data[0], 0, _Size);
#ifdef BIGENDIAN
			_Data[0] = static_cast<char>(static_cast<Elysium::Core::Template::System::uint16_t>(AddressFamily) >> 8);
			_Data[1] = static_cast<char>(AddressFamily);
#else
			_Data[0] = static_cast<char>(AddressFamily);
			_Data[1] = static_cast<char>(static_cast<Elysium::Core::Template::System::uint16_t>(AddressFamily) >> 8);
#endif
		}

		constexpr SocketAddress(const SocketAddress& Source) = delete;

		constexpr SocketAddress(SocketAddress&& Right) noexcept = delete;

		constexpr ~SocketAddress() = default;
	public:
		constexpr SocketAddress& operator=(const SocketAddress& Source) = delete;

		constexpr SocketAddress& operator=(SocketAddress&& Right) noexcept = delete;
	public:
		inline constexpr const Elysium::Core::Template::System::byte operator[](const Elysium::Core::Template::System::size Index) const
		{
			if (Index > _Size)
			{	// @ToDo: indexoutofrangeexception
				throw;
			}

			return _Data[Index];
		}
	public:
		const Elysium::Core::Template::Net::Sockets::AddressFamily GetFamily() const noexcept
		{
			return static_cast<Elysium::Core::Template::Net::Sockets::AddressFamily>(_Data[0] | (_Data[1] << 8));
		}

		inline constexpr const Elysium::Core::Template::System::uint8_t GetSize() const noexcept
		{
			return _Size;
		}
	private:
		inline static constexpr const Elysium::Core::Template::System::uint8_t MaxSize = 32;

		/// <summary>
		/// ...
		/// first two bytes contain address family
		/// </summary>
		inline static constexpr const Elysium::Core::Template::System::uint8_t WriteableOffset = 2;
	private:
		inline static constexpr  const Elysium::Core::Template::System::uint8_t IPv6AddressSize = 28;	// 2 byte address family, 26 byte rest (???)
		inline static constexpr  const Elysium::Core::Template::System::uint8_t IPv4AddressSize = 16;	// 2 byte address family, 14 byte rest (2 byte port? 12 byte ip?)
	private:
		// DO NOT CHANGE THE ORDER OF FIELDS!
		Elysium::Core::Template::System::byte _Data[MaxSize]{};
		Elysium::Core::Template::System::uint8_t _Size;
	};
}
#endif
