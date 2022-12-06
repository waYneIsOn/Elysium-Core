/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_INTERNAL_ASYNCRESULT
#define ELYSIUM_CORE_INTERNAL_ASYNCRESULT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_IASYNCRESULT
#include "IAsyncResult.hpp"
#endif

#ifndef ELYSIUM_CORE_INTERNAL_WRAPPEDOVERLAP
#include "WrappedOverlap.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_MANUALRESETEVENT
#include "../Elysium.Core.Threading/ManualResetEvent.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DELEGATE
#include "../Elysium.Core.Template/Delegate.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef ELYSIUM_CORE_INTERNAL_WINDOWSERRORCODE
#include "../Elysium.Core/WindowsErrorCode.hpp"
#endif
#endif

namespace Elysium::Core::Internal
{
	class ELYSIUM_CORE_API AsyncResult : public IAsyncResult
	{
	protected:
		AsyncResult(const Elysium::Core::Template::Container::Delegate<void, const Elysium::Core::IAsyncResult*>& Callback, const void* AsyncState,
			const Elysium::Core::size Position);
	public:
		AsyncResult(const AsyncResult& Source) = delete;

		AsyncResult(AsyncResult&& Right) noexcept = delete;

		virtual ~AsyncResult();
	public:
		AsyncResult& operator=(const AsyncResult& Source) = delete;

		AsyncResult& operator=(AsyncResult&& Right) noexcept = delete;
	public:
		virtual const void* GetAsyncState() const override;

		virtual Elysium::Core::Threading::WaitHandle& GetAsyncWaitHandle() override;

		virtual const bool GetCompletedSynchronously() const override;

		virtual const bool GetIsCompleted() const override;

		const Elysium::Core::Template::Container::Delegate<void, const Elysium::Core::IAsyncResult*>& GetCallback() const;

		const Elysium::Core::uint16_t GetErrorCode() const;

#if defined ELYSIUM_CORE_OS_WINDOWS
		const Elysium::Core::Internal::WindowsErrorCode GetNamedErrorCode() const;
#endif
	public:
		const Elysium::Core::Template::Container::Delegate<void, const Elysium::Core::IAsyncResult*> _Callback;
		const void* _AsyncState;

		Elysium::Core::Threading::ManualResetEvent _OperationDoneEvent;
		Elysium::Core::uint16_t _ErrorCode;
		Elysium::Core::Internal::WrappedOverlap _WrappedOverlap;
	};
}
#endif
