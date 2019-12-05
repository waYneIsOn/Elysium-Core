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

namespace Elysium
{
	namespace Core
	{
		namespace Threading
		{
			class ELYSIUM_CORE_API Thread
			{
			public:
				// constructors & destructor
				Thread(void(*Start)());
				Thread(const Thread& Source) = delete;
				//Thread(void(*Start)(void*));
				~Thread();

				Thread& operator=(const Thread&) = delete;

				// properties - getter
				void GetCurrentCulture(Globalization::CultureInfo* Value) const;
				void GetThreadId(unsigned int* Value) const;

				static void GetCurrentThreadId(unsigned int* Value);

				// properties - setter

				// methods
				void Join();
				void Start();

				static void Sleep(TimeSpan& Timeout);
				//static bool Yield();
			private:
				void(*_ThreadStart)();
				std::thread _NativeThread;

				Globalization::CultureInfo _CurrentCulture;
			};
		}
	}
}
#endif
