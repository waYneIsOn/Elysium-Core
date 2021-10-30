/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_FILESTREAMASYNCRESULT
#define ELYSIUM_CORE_IO_FILESTREAMASYNCRESULT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_DELEGATE
#include "../Elysium.Core/Delegate.hpp"
#endif

#ifndef ELYSIUM_CORE_IASYNCRESULT
#include "../Elysium.Core/IAsyncResult.hpp"
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

namespace Elysium::Core::IO
{
	class FileStream;

	class ELYSIUM_CORE_API FileStreamAsyncResult final : public IAsyncResult
	{
		friend class FileStream;
	private:
		FileStreamAsyncResult(FileStream& Stream, const Elysium::Core::Delegate<void, const Elysium::Core::IAsyncResult*>&Callback, const void* AsyncState);
	public:
		FileStreamAsyncResult(const FileStreamAsyncResult& Source) = delete;

		FileStreamAsyncResult(FileStreamAsyncResult&& Right) noexcept = delete;

		virtual ~FileStreamAsyncResult();
	public:
		FileStreamAsyncResult& operator=(const FileStreamAsyncResult& Source) = delete;

		FileStreamAsyncResult& operator=(FileStreamAsyncResult&& Right) noexcept = delete;
	public:
		virtual const void* GetAsyncState() const override;

		virtual const Elysium::Core::Threading::WaitHandle& GetAsyncWaitHandle() const override;

		virtual const bool GetCompletedSynchronously() const override;

		virtual const bool GetIsCompleted() const override;

		const Elysium::Core::Delegate<void, const Elysium::Core::IAsyncResult*>& GetCallback() const;

		Elysium::Core::IO::FileStream& GetFileStream() const;
	private:
		FileStream& _Stream;
		const Elysium::Core::Delegate<void, const Elysium::Core::IAsyncResult*> _Callback;
		const void* _AsyncState;
		Elysium::Core::Threading::ManualResetEvent _OperationDoneEvent;

#if defined(ELYSIUM_CORE_OS_WINDOWS)
		PTP_IO _CompletionPortHandle;
		OVERLAPPED _Overlapped;

		static void IOCompletionPortCallback(PTP_CALLBACK_INSTANCE Instance, void* Context, void* Overlapped, ULONG IoResult, ULONG_PTR NumberOfBytesTransferred, PTP_IO Io);
#elif defined(ELYSIUM_CORE_OS_ANDROID)

#else

#endif
	};
}
#endif
