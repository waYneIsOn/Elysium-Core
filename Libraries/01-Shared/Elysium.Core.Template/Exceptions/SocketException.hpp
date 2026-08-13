/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_NET_SOCKETS_SOCKETEXCEPTION
#define ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_NET_SOCKETS_SOCKETEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_SYSTEMEXCEPTION
#include "SystemException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_SOCKETERROR
#include "../Net/Sockets/SocketError.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Exceptions::Net::Sockets
{
	class SocketException
		: public Elysium::Core::Template::Exceptions::SystemException
	{
	public:
		inline constexpr SocketException(const char8_t* Message = nullptr)
			: Elysium::Core::Template::Exceptions::SystemException(Message)
		{}

		inline constexpr SocketException(const System::uint32_t ErrorCode, const char8_t* Message = nullptr)
			: Elysium::Core::Template::Exceptions::SystemException(ErrorCode, Message)
		{}

		inline constexpr SocketException(const SocketException& Source) = default;

		inline constexpr SocketException(SocketException&& Right) noexcept = default;

		virtual ~SocketException() override = default;
	public:
		inline constexpr SocketException& operator=(const SocketException& Source) = default;

		inline constexpr SocketException& operator=(SocketException&& Right) noexcept = default;
	public:
		inline constexpr const Elysium::Core::Template::Net::Sockets::SocketError GetSocketErrorCode() const noexcept
		{
			return static_cast<Elysium::Core::Template::Net::Sockets::SocketError>(GetErrorCode());
		}
	};
}
#endif
