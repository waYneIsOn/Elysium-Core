#ifndef MS_CPP_UNITTESTFRAMEWORK_THREADSAFELOGGER
#define MS_CPP_UNITTESTFRAMEWORK_THREADSAFELOGGER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_MUTEX
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Mutex.hpp"
#endif

#ifndef MS_CPP_UNITTESTFRAMEWORK_LOGGER
#include <CppUnitTestLogger.h>
#endif

namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	class ThreadsafeLogger
	{
	public:
		static void WriteMessage(const wchar_t* message)
		{
			_Mutex.Lock();
			Logger::WriteMessage(message);
			_Mutex.Unlock();
		}

		static void WriteMessage(const char* message)
		{
			_Mutex.Lock();
			Logger::WriteMessage(message);
			_Mutex.Unlock();
		}
	private:
		inline static Elysium::Core::Template::Threading::Mutex _Mutex = Elysium::Core::Template::Threading::Mutex();
	};
}
#endif
