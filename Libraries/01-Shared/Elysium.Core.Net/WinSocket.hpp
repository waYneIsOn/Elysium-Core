/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_SOCKETS_INTERNAL_WINSOCKET
#define ELYSIUM_CORE_NET_SOCKETS_INTERNAL_WINSOCKET

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _WINSOCK2API_
#include <WinSock2.h>
#endif

#ifndef _MSWSOCK_
#include <MSWSock.h>
#endif

namespace Elysium::Core::Net::Sockets
{
	class Socket;
}

namespace Elysium::Core::Net::Sockets::Internal
{
	class WinSocket final
	{
		friend class Elysium::Core::Net::Sockets::Socket;
	public:
		WinSocket() = delete;

		WinSocket(const WinSocket& Source) = delete;

		WinSocket(WinSocket&& Right) noexcept = delete;

		~WinSocket() = delete;
	public:
		WinSocket& operator=(const WinSocket& Source) = delete;

		WinSocket& operator=(WinSocket&& Right) noexcept = delete;
	public:
		static void Initialize();

		static void Shutdown();
	private:
		static LPFN_CONNECTEX RetrieveFunctionConnectEx(SOCKET NativeWinSocketHandle);

		static LPFN_DISCONNECTEX RetrieveFunctionDisconnectEx(SOCKET NativeWinSocketHandle);
		/*
		static void NotifyIncomingWork(SOCKET NativeWinSocketHandle);

		static void CancelIncomingWorkNotification(SOCKET NativeWinSocketHandle);
		*/
	};
}
#endif
#endif
