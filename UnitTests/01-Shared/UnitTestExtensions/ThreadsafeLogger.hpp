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
			//GetMutex().Lock();
			//Logger::WriteMessage(message);
			//GetMutex().Unlock();
		}

		static void WriteMessage(const char* message)
		{
			//GetMutex().Lock();
			//Logger::WriteMessage(message);
			//GetMutex().Unlock();
		}
	private:
		static Elysium::Core::Template::Threading::Mutex& GetMutex()
		{
			static Elysium::Core::Template::Threading::Mutex Value = Elysium::Core::Template::Threading::Mutex();
			return Value;
		}
	};
}
#endif
