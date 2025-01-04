/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_SOCKETS_SENDRECEIVEASYNCRESULT
#define ELYSIUM_CORE_NET_SOCKETS_SENDRECEIVEASYNCRESULT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_NET_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_INTERNAL_ASYNCRESULT
#include "../Elysium.Core/AsyncResult.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primivites.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DELEGATE
#include "../Elysium.Core.Template/Delegate.hpp"
#endif

#if defined(ELYSIUM_CORE_OS_WINDOWS)
#ifndef _WINSOCK2API_
#include <WinSock2.h>
#endif
#endif

namespace Elysium::Core::Net::Sockets
{
	class Socket;

	class ELYSIUM_CORE_NET_API SendReceiveAsyncResult final : public Elysium::Core::Internal::AsyncResult
	{
		friend class Socket;
	private:
		SendReceiveAsyncResult(Elysium::Core::Net::Sockets::Socket& Socket, const Elysium::Core::Container::DelegateOfVoidConstIASyncResultPointer& Callback,
			const void* AsyncState);
	public:
		SendReceiveAsyncResult(const SendReceiveAsyncResult& Source) = delete;

		SendReceiveAsyncResult(SendReceiveAsyncResult&& Right) noexcept = delete;

		virtual ~SendReceiveAsyncResult();
	public:
		SendReceiveAsyncResult& operator=(const SendReceiveAsyncResult& Source) = delete;

		SendReceiveAsyncResult& operator=(SendReceiveAsyncResult&& Right) noexcept = delete;
	public:
		Elysium::Core::Net::Sockets::Socket& GetSocket() const;

		const Elysium::Core::uint32_t& GetBytesTransferred() const;
	private:
		Elysium::Core::Net::Sockets::Socket& _Socket;
		Elysium::Core::uint32_t _BytesTransferred = 0;

#if defined(ELYSIUM_CORE_OS_WINDOWS)
		WSABUF _WSABuffer;
#endif
	};
}
#endif
