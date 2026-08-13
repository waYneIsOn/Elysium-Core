/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_DEVICE_SOCKETDEVICE
#define ELYSIUM_CORE_TEMPLATE_IO_DEVICE_SOCKETDEVICE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_EXCEPTION
#include "../../Exceptions/Exception.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_SYSTEMEXCEPTION
#include "../../Exceptions/SystemException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_ADDRESSFAMILY
#include "../../Net/Sockets/AddressFamily.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_PROTOCOLTYPE
#include "../../Net/Sockets/ProtocolType.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_SOCKET
#include "../../Net/Sockets/Socket.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_SOCKETTYPE
#include "../../Net/Sockets/SocketType.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRINGVIEW
#include "../../Text/StringView.hpp"
#endif

namespace Elysium::Core::Template::IO::Device
{
	class SocketDevice
	{
	public:
		constexpr SocketDevice() noexcept = delete;
	
		inline constexpr SocketDevice(const Elysium::Core::Template::Net::Sockets::Socket& Socket)
		{ }

		constexpr SocketDevice(const SocketDevice& Source) = delete;

		constexpr SocketDevice(SocketDevice&& Right) noexcept = delete;

		inline constexpr ~SocketDevice()
		{
			Close();
		}
	public:
		constexpr SocketDevice& operator=(const SocketDevice& Source) = delete;

		constexpr SocketDevice& operator=(SocketDevice&& Right) noexcept = delete;
	public:
		inline constexpr const bool operator==(const SocketDevice& Other) const noexcept
		{
			return false;
		}

		inline constexpr const bool operator!=(const SocketDevice& Other) const noexcept
		{
			return false;
		}
	public:
		inline constexpr const Elysium::Core::Template::System::size GetLength() const
		{
			return 0;
		}

		inline constexpr const Elysium::Core::Template::System::uint64_t GetPosition() const
		{
			return 0;
		}
	public:
		inline void SetPosition(const Elysium::Core::Template::System::uint64_t Position)
		{

		}
	public:
		inline void Connect(const Elysium::Core::Template::Text::StringView<char8_t> Host, const Elysium::Core::Template::System::uint16_t Port)
		{

			bool sdfds = false;
		}

		inline void Close()
		{

		}
	public:
		inline const Elysium::Core::Template::System::size Read(Elysium::Core::Template::System::byte* Buffer, const Elysium::Core::Template::System::size Count)
		{
			return 0;
		}
	public:
		inline void Write(const Elysium::Core::Template::System::byte* Buffer, const Elysium::Core::Template::System::size Count)
		{

		}

		inline void Flush()
		{

		}
	private:
		//Elysium::Core::Template::Net::Sockets::Socket& _Socket;
	};
}
#endif
