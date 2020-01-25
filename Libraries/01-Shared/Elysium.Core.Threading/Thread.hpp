/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_THREADING_THREAD
#define ELYSIUM_CORE_THREADING_THREAD

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_DELEGATE
#include "../Elysium.Core/Delegate.hpp"
#endif

#ifndef ELYSIUM_CORE_TIMESPAN
#include "../Elysium.Core/TimeSpan.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_THREADSTATE
#include "ThreadState.hpp"
#endif

#ifndef ELYSIUM_CORE_GLOBALIZATION_CULTUREINFO
#include "../Elysium.Core/CultureInfo.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_SYSTEM
#include "System.hpp"
#endif

#ifndef _ATOMIC_
#include <atomic>
#endif

#pragma warning(disable : 4251)

namespace Elysium::Core::Threading
{
	class ELYSIUM_CORE_API Thread final
	{
	public:
		Thread(const Delegate<void>& ThreadStart);
		Thread(const Delegate<void, void*>& ParameterizedThreadStart);
		Thread(const Thread& Source) = delete;
		Thread(Thread&& Right) noexcept = delete;
		~Thread();

		Thread& operator=(const Thread& Source) = delete;
		Thread& operator=(Thread&& Right) noexcept = delete;

		bool operator==(const Thread& Other) const;
		bool operator!=(const Thread& Other) const;

		const Globalization::CultureInfo& GetCurrentCulture() const;
		const int GetThreadId() const;

		static const int GetCurrentThreadId();

		void Start();
		void Start(void* Parameter);

		void Join();

		static void Sleep(const TimeSpan& Timeout);
		//static bool Yield();
	private:
		unsigned long _Id;
		ELYSIUM_SYNCHRONIZATION_PRIMITIVE_HANDLE _Handle;
		Elysium::Core::String _Name;
		std::atomic<ThreadState> _State;
		Globalization::CultureInfo _CurrentCulture;

		struct ThreadParameters
		{
			ThreadParameters(const Delegate<void>& ThreadStart);
			ThreadParameters(const Delegate<void, void*>& ParameterizedThreadStart);
			~ThreadParameters();

			void* _Target;
			void(*_Method)(void* NonSpecificInstance);
			void* _FurtherParameter;
			void(*_ParamaterizedMethod)(void* NonSpecificInstance, void* FurtherParameter);
		};

		ThreadParameters _Parameters;

		static void ThreadMain(ThreadParameters& Parameters);
	};
}
#endif
