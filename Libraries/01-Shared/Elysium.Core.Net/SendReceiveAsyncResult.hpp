/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

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

#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
#ifndef _WINSOCK2API_
#include <WinSock2.h>
#endif
#elif defined(__ANDROID__)

#else
#error "undefined os"
#endif

namespace Elysium::Core::Net::Sockets
{
	class Socket;

	class ELYSIUM_CORE_NET_API SendReceiveAsyncResult final : public IAsyncResult
	{
		friend class Socket;
	public:
		SendReceiveAsyncResult(const SendReceiveAsyncResult& Source) = delete;
		virtual ~SendReceiveAsyncResult();

		SendReceiveAsyncResult& operator=(const SendReceiveAsyncResult& Source) = delete;

		const Elysium::Core::Net::Sockets::Socket& GetSocket() const;
		const Elysium::Core::Collections::Template::Array<Elysium::Core::byte>& GetBuffer() const;

		virtual const void* GetAsyncState() const override;
		virtual const Elysium::Core::Threading::WaitHandle& GetAsyncWaitHandle() const override;
		virtual const bool GetCompletedSynchronously() const override;
		virtual const bool GetIsCompleted() const override;
	private:
		SendReceiveAsyncResult(const Elysium::Core::Net::Sockets::Socket* Socket, const void* AsyncState, const size_t BufferSize);
		SendReceiveAsyncResult(SendReceiveAsyncResult&& Right) noexcept;

		SendReceiveAsyncResult& operator=(SendReceiveAsyncResult&& Right) noexcept;

		const Elysium::Core::Net::Sockets::Socket* _Socket;
		const void* _AsyncState;

		Elysium::Core::Collections::Template::Array<Elysium::Core::byte> _Buffer;
		Elysium::Core::uint32_t _BytesReceived = 0;
		Elysium::Core::uint32_t _BytesSent = 0;


#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
		OVERLAPPED Overlapped;
		WSABUF DataBuf;
#elif defined(__ANDROID__)

#else

#endif
	};
}
#endif
