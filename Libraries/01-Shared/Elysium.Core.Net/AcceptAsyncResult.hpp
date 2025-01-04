/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_SOCKETS_ACCEPTASYNCRESULT
#define ELYSIUM_CORE_NET_SOCKETS_ACCEPTASYNCRESULT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTERNAL_ASYNCRESULT
#include "../Elysium.Core/AsyncResult.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "../Elysium.Core/Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primivites.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DELEGATE
#include "../Elysium.Core.Template/Delegate.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _WINSOCK2API_
#include <WinSock2.h>
#endif
#endif

namespace Elysium::Core::Net::Sockets
{
	class Socket;

	class ELYSIUM_CORE_NET_API AcceptAsyncResult final : public Elysium::Core::Internal::AsyncResult
	{
		friend class Socket;
	private:
		AcceptAsyncResult(Elysium::Core::Net::Sockets::Socket& Socket, 
			const Elysium::Core::Container::DelegateOfVoidConstIASyncResultPointer& Callback, const void* AsyncState,
			const Elysium::Core::size BufferSize);
	public:
		AcceptAsyncResult(const AcceptAsyncResult& Source) = delete;

		AcceptAsyncResult(AcceptAsyncResult&& Right) noexcept = delete;

		virtual ~AcceptAsyncResult();
	public:
		AcceptAsyncResult& operator=(const AcceptAsyncResult& Source) = delete;

		AcceptAsyncResult& operator=(AcceptAsyncResult&& Right) noexcept = delete;
	public:
		Elysium::Core::Net::Sockets::Socket& GetSocket() const;
	private:
		Elysium::Core::Net::Sockets::Socket& _Socket;

		const Elysium::Core::byte _Addresses[88];	// (sizeof(sockaddr_in6) + 16) * 2.... sizeof(sockaddr_in6) = 28

#if defined ELYSIUM_CORE_OS_WINDOWS
		SOCKET _ClientSocket;
#else
#error "unsupported os"
#endif
	};
}
#endif
