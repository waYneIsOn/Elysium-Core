/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_THREADING_THREAD
#define ELYSIUM_CORE_THREADING_THREAD

#ifndef ELYSIUM_CORE_EXPORT
#include "../Elysium.Core/Export.hpp"
#endif

#ifndef ELYSIUM_CORE_TIMESPAN
#include "../Elysium.Core/TimeSpan.hpp"
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
			class EXPORT Thread
			{
			public:
				// constructors & destructor
				Thread(void(*Start)());
				//Thread(void(*Start)(void*));
				~Thread();

				// properties - getter
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
			};
		}
	}
}
#endif
