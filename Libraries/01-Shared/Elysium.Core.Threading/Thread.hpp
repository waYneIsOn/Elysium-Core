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

#ifndef ELYSIUM_CORE_GLOBALIZATION_CULTUREINFO
#include "../Elysium.Core/CultureInfo.hpp"
#endif

#ifndef _THREAD_
#include <thread>
#endif

#pragma warning(disable : 4251)

namespace Elysium::Core::Threading
{
	//class ThreadPool;

	class ELYSIUM_CORE_API Thread
	{
		//friend class Elysium::Core::Collections::Template::List<Thread>;
		//friend class Elysium::Core::Threading::ThreadPool;
	public:
		Thread();
		Thread(const Thread& Source) = delete;
		Thread(Thread&& Right) noexcept;
		~Thread();

		Thread& operator=(const Thread& Source) = delete;
		Thread& operator=(Thread&& Right) noexcept;

		bool operator==(const Thread& Other) const;
		bool operator!=(const Thread& Other) const;

		const Globalization::CultureInfo& GetCurrentCulture() const;
		const int GetThreadId() const;

		static const int GetCurrentThreadId();

		void Start(const Delegate<void>& ThreadStart);
		template<class T>
		void Start(const Delegate<void, T>& ParameterizedThreadStart, T Parameter);

		void Join();

		static void Sleep(TimeSpan& Timeout);
		//static bool Yield();
	private:
		std::thread _NativeThread;

		Globalization::CultureInfo _CurrentCulture;
	};

	template<class T>
	inline void Thread::Start(const Delegate<void, T>& ParameterizedThreadStart, T Parameter)
	{
		_NativeThread = std::thread(ParameterizedThreadStart, Parameter);
	}
}
#endif
