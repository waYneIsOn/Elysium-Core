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
#ifndef ELYSIUM_CORE_INTERNAL_WINDOWSERRORCODE
#include "../Elysium.Core/WindowsErrorCode.hpp"
#endif

#ifndef _WINSOCK2API_
#include <WinSock2.h>
#endif
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

		const Elysium::Core::size GetBytesTransferred() const;

		const Elysium::Core::uint16_t GetErrorCode() const;
#if defined ELYSIUM_CORE_OS_WINDOWS
		const Elysium::Core::Internal::WindowsErrorCode GetNamedErrorCode() const;
#endif
	private:
		FileStream& _Stream;
		const Elysium::Core::Delegate<void, const Elysium::Core::IAsyncResult*> _Callback;
		const void* _AsyncState;
		Elysium::Core::Threading::ManualResetEvent _OperationDoneEvent;
		Elysium::Core::size _BytesTransferred;
		Elysium::Core::uint16_t _ErrorCode;

#if defined ELYSIUM_CORE_OS_WINDOWS 
		OVERLAPPED _Overlapped;
#else
#error "unsupported os"
#endif
	};
}
#endif
