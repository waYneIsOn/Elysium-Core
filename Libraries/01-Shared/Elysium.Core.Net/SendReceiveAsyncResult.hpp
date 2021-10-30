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

#ifndef ELYSIUM_CORE_IASYNCRESULT
#include "../Elysium.Core/IAsyncResult.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "../Elysium.Core/Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_DELEGATE
#include "../Elysium.Core/Delegate.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_MANUALRESETEVENT
#include "../Elysium.Core.Threading/ManualResetEvent.hpp"
#endif

#if defined(ELYSIUM_CORE_OS_WINDOWS)
#ifndef _WINSOCK2API_
#include <WinSock2.h>
#endif
#elif defined(ELYSIUM_CORE_OS_ANDROID)

#else
#error "undefined os"
#endif

namespace Elysium::Core::Net::Sockets
{
	class Socket;

	class ELYSIUM_CORE_NET_API SendReceiveAsyncResult final : public IAsyncResult
	{
		friend class Socket;
	private:
		SendReceiveAsyncResult(Elysium::Core::Net::Sockets::Socket& Socket, const Elysium::Core::Delegate<void, const Elysium::Core::IAsyncResult*>& Callback, const void* AsyncState, const Elysium::Core::size BufferSize);
	public:
		SendReceiveAsyncResult(const SendReceiveAsyncResult& Source) = delete;

		SendReceiveAsyncResult(SendReceiveAsyncResult&& Right) noexcept = delete;

		virtual ~SendReceiveAsyncResult();
	public:
		SendReceiveAsyncResult& operator=(const SendReceiveAsyncResult& Source) = delete;

		SendReceiveAsyncResult& operator=(SendReceiveAsyncResult&& Right) noexcept = delete;
	public:
		virtual const void* GetAsyncState() const override;

		virtual const Elysium::Core::Threading::WaitHandle& GetAsyncWaitHandle() const override;

		virtual const bool GetCompletedSynchronously() const override;

		virtual const bool GetIsCompleted() const override;

		const Elysium::Core::Delegate<void, const Elysium::Core::IAsyncResult*>& GetCallback() const;

		Elysium::Core::Net::Sockets::Socket& GetSocket() const;

		const Elysium::Core::uint32_t& GetBytesTransferred() const;
	private:
		const void* _AsyncState;
		Elysium::Core::Threading::ManualResetEvent _OperationDoneEvent;

		const Elysium::Core::Delegate<void, const Elysium::Core::IAsyncResult*> _Callback;
		Elysium::Core::Net::Sockets::Socket& _Socket;
		Elysium::Core::uint32_t _BytesTransferred = 0;

#if defined(ELYSIUM_CORE_OS_WINDOWS)
		WSABUF _WSABuffer;
		WSAOVERLAPPED _Overlapped;
#elif defined(ELYSIUM_CORE_OS_ANDROID)

#else

#endif
	};
}
#endif
