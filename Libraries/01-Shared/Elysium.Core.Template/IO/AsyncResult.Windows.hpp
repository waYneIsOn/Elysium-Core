/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_ASYNCRESULT_WINDOWS
#define ELYSIUM_CORE_TEMPLATE_IO_ASYNCRESULT_WINDOWS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DELEGATE
#include "../Container/Delegate.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_OBSERVERPOINTER
#include "../Memory/ObserverPointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_MANUALRESETEVENT
#include "../Threading/ManualResetEvent.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
	#ifndef _MINWINBASE_
	#include <minwinbase.h>
	#endif

	#ifndef _MINWINDEF_
	#include <minwindef.h>
	#endif
#endif

namespace Elysium::Core::Template::IO::Device
{
	class FileDevice;
}

namespace Elysium::Core::Template::IO
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	template <class AsyncResultDetails>
	class AsyncResult
	{
	public:
		friend class Elysium::Core::Template::IO::Device::FileDevice;
	public:
		constexpr AsyncResult() = delete;

		inline constexpr AsyncResult(const Elysium::Core::Template::System::size Position, 
			const Elysium::Core::Template::Container::Delegate<void, Elysium::Core::Template::Memory::ObserverPointer<AsyncResult<AsyncResultDetails>>>& Callback, AsyncResultDetails Details)
			: _Overlapped{}, _HasCompletedSynchronously{}, _ErrorCode{}, _OperationDoneEvent{}, _Callback(Callback), _Details(Details)
		{
			_Overlapped.Offset = static_cast<DWORD>(Position);
			_Overlapped.OffsetHigh = static_cast<DWORD>(Position >> 32);
		}

		constexpr AsyncResult(const AsyncResult& Source) = delete;

		constexpr AsyncResult(AsyncResult&& Right) noexcept = delete;

		constexpr ~AsyncResult() = default;
	public:
		constexpr AsyncResult& operator=(const AsyncResult& Source) = delete;

		constexpr AsyncResult& operator=(AsyncResult&& Right) noexcept = delete;
	public:
		inline const bool GetHasCompletedSynchronously() const noexcept
		{
			return _HasCompletedSynchronously;
		}

		inline const Elysium::Core::Template::System::uint16_t GetErrorCode() const noexcept
		{
			return _ErrorCode;
		}
		/*
		inline const Elysium::Core::Template::Threading::WaitHandle& GetAsyncWaitHandle() const noexcept
		{
			return _OperationDoneEvent;
		}
		*/
		inline const Elysium::Core::Template::Threading::ManualResetEvent& GetAsyncWaitHandle() const noexcept
		{
			return _OperationDoneEvent;
		}

		inline AsyncResultDetails& GetDetails() noexcept
		{
			return _Details;
		}
	private:
		// Keep _Overlapped as the first field!!! That way IOCP-Callback can cast correctly.
		OVERLAPPED _Overlapped;
		//void* _AsyncResult;

		bool _HasCompletedSynchronously;
		DWORD _ErrorCode;
		Elysium::Core::Template::Threading::ManualResetEvent _OperationDoneEvent;
		Elysium::Core::Template::Container::Delegate<void, Elysium::Core::Template::Memory::ObserverPointer<AsyncResult<AsyncResultDetails>>> _Callback;

		AsyncResultDetails _Details;
	};
#endif
}
#endif
