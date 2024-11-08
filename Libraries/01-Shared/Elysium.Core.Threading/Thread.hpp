/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_THREAD
#define ELYSIUM_CORE_THREADING_THREAD

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_TIMESPAN
#include "../Elysium.Core/TimeSpan.hpp"
#endif

#ifndef ELYSIUM_CORE_GLOBALIZATION_CULTUREINFO
#include "../Elysium.Core.Globalization/CultureInfo.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DELEGATE
#include "../Elysium.Core.Template/Delegate.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_SYSTEM
#include "System.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_THREADSTATE
#include "ThreadState.hpp"
#endif

#ifndef _ATOMIC_
#include <atomic>
#endif

//#pragma warning(disable : 4251)

namespace Elysium::Core::Threading
{
	class ELYSIUM_CORE_API Thread final
	{
	public:
		Thread(const Elysium::Core::Template::Container::Delegate<void>& ThreadStart);

		Thread(const Elysium::Core::Template::Container::Delegate<void, void*>& ParameterizedThreadStart);

		Thread(const Thread& Source) = delete;

		Thread(Thread&& Right) noexcept;

		~Thread();
	public:
		Thread& operator=(const Thread& Source) = delete;

		Thread& operator=(Thread&& Right) noexcept;
	public:
		bool operator==(const Thread& Other) const;

		bool operator!=(const Thread& Other) const;
	public:
		const Globalization::CultureInfo& GetCurrentCulture() const;

		const Elysium::Core::uint32_t GetThreadId() const;

		static const Elysium::Core::uint32_t GetCurrentThreadIdX();

		void Start();

		void Start(void* Parameter);

		void Join();

		static void Sleep(const TimeSpan& Timeout);

		//static bool Yield();
	private:
		struct ThreadParameters
		{
		public:
			ThreadParameters();

			ThreadParameters(const Elysium::Core::Template::Container::Delegate<void>& ThreadStart);

			ThreadParameters(const Elysium::Core::Template::Container::Delegate<void, void*>& ParameterizedThreadStart);

			~ThreadParameters();
		public:
			void* _Target;

			void(*_Method)(void* NonSpecificInstance);

			void* _FurtherParameter;

			void(*_ParamaterizedMethod)(void* NonSpecificInstance, void* FurtherParameter);
		};
	private:
		unsigned long _Id;

		ELYSIUM_SYNCHRONIZATION_PRIMITIVE_HANDLE _Handle;

		Elysium::Core::Utf8String _Name;

		std::atomic<ThreadState> _State;

		Globalization::CultureInfo _CurrentCulture;

		ThreadParameters _Parameters;
	private:
		static void ThreadMain(ThreadParameters& Parameters);
	};
}
#endif
