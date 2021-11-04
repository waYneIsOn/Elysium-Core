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

#ifndef ELYSIUM_CORE_DELEGATE
#include "../Elysium.Core/Delegate.hpp"
#endif

#ifndef ELYSIUM_CORE_IASYNCRESULT
#include "../Elysium.Core/IAsyncResult.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAYOFBYTE
#include "../Elysium.Core/ArrayOfByte.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_MANUALRESETEVENT
#include "../Elysium.Core.Threading/ManualResetEvent.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _WINSOCK2API_
#include <WinSock2.h>
#endif
#else
#error "undefined os"
#endif

namespace Elysium::Core::Net::Sockets
{
	class Socket;

	class ELYSIUM_CORE_NET_API AcceptAsyncResult final : public IAsyncResult
	{
		friend class Socket;
	private:
		AcceptAsyncResult(Elysium::Core::Net::Sockets::Socket& Socket, 
			const Elysium::Core::Delegate<void, const AcceptAsyncResult*>& Callback, const void* AsyncState,
			const Elysium::Core::size BufferSize);
	public:
		AcceptAsyncResult(const AcceptAsyncResult& Source) = delete;

		AcceptAsyncResult(AcceptAsyncResult&& Right) noexcept = delete;

		virtual ~AcceptAsyncResult();
	public:
		AcceptAsyncResult& operator=(const AcceptAsyncResult& Source) = delete;

		AcceptAsyncResult& operator=(AcceptAsyncResult&& Right) noexcept = delete;
	public:
		virtual const void* GetAsyncState() const override;

		virtual const Elysium::Core::Threading::WaitHandle& GetAsyncWaitHandle() const override;

		virtual const bool GetCompletedSynchronously() const override;

		virtual const bool GetIsCompleted() const override;

		const Elysium::Core::Delegate<void, const AcceptAsyncResult*>& GetCallback() const;

		Elysium::Core::Net::Sockets::Socket& GetSocket() const;
	private:
		Elysium::Core::Net::Sockets::Socket& _Socket;
		const Elysium::Core::Delegate<void, const AcceptAsyncResult*> _Callback;
		const void* _AsyncState;
		Elysium::Core::Threading::ManualResetEvent _OperationDoneEvent;
		Elysium::Core::uint16_t _ErrorCode;

		const Elysium::Core::byte _Addresses[88];	// (sizeof(sockaddr_in6) + 16) * 2.... sizeof(sockaddr_in6) = 28

#if defined ELYSIUM_CORE_OS_WINDOWS
		WSAOVERLAPPED _Overlapped;
		SOCKET _ClientSocket;
#else
#error "unsupported os"
#endif
	};
}
#endif
