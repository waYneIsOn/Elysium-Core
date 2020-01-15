#include "CppUnitTest.h"

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#include "CppUnitTestFrameworkExtension.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_THREAD
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/Thread.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_MUTEX
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/Mutex.hpp"
#endif

#ifndef ELYSIUM_CORE_DATETIME
#include "../../../Libraries/01-Shared/Elysium.Core/DateTime.hpp"
#endif

#ifndef ELYSIUM_CORE_TIMESPAN
#include "../../../Libraries/01-Shared/Elysium.Core/TimeSpan.hpp"
#endif

#ifndef _WINDOWS_
#include <Windows.h>
#endif

using namespace Elysium::Core;
using namespace Elysium::Core::Threading;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsCore
{
	TEST_CLASS(Core_Threading_Thread)
	{
	public:
		TEST_METHOD(ThreadStartThread)
		{
			_WorkerThreadId = std::this_thread::get_id();

			Thread T = Thread();
			T.Start(Delegate<void>::CreateDelegate<Core_Threading_Thread, &Core_Threading_Thread::ZeroParameterThreadStart>(*this));
			Assert::AreEqual(25, _CalculatedValue);
			Assert::IsFalse(std::this_thread::get_id() == _WorkerThreadId);
		}
		TEST_METHOD(ParameterizedThreadStartThread)
		{
			_WorkerThreadId = std::this_thread::get_id();

			Thread T = Thread();
			T.Start<int>(Delegate<void, int>::CreateDelegate<Core_Threading_Thread, &Core_Threading_Thread::SingleParameterThreadStart>(*this), 6);
			Assert::AreEqual(36, _CalculatedValue);
			Assert::IsFalse(std::this_thread::get_id() == _WorkerThreadId);
		}
		TEST_METHOD(AwaitLongRunning)
		{
			_WorkerThreadId = std::this_thread::get_id();

			DateTime Start = DateTime::Now();
			Thread T = Thread();
			T.Start(Delegate<void>::CreateDelegate<Core_Threading_Thread, &Core_Threading_Thread::LongRunning>(*this));
			T.Join();
			TimeSpan ElapsedTime = DateTime::Now() - Start;
			double ElapsedSecondsTotal = ElapsedTime.GetTotalSeconds();
			Assert::AreEqual(5, ElapsedTime.GetSeconds());
			Assert::IsTrue(ElapsedSecondsTotal > 5.0 && ElapsedSecondsTotal < 6.0);
		}
		TEST_METHOD(AwaitMutex)
		{
			_WorkerThreadId = std::this_thread::get_id();

			DateTime Start = DateTime::Now();
			Thread T = Thread();
			T.Start(Delegate<void>::CreateDelegate<Core_Threading_Thread, &Core_Threading_Thread::RunMutex>(*this));

			// sleep for a bit just to make sure T has locked the mutex
			Thread::Sleep(TimeSpan::FromSeconds(1));
			RunMutex();

			TimeSpan ElapsedTime = DateTime::Now() - Start;
			double ElapsedSecondsTotal = ElapsedTime.GetTotalSeconds();
			Assert::AreEqual(10, ElapsedTime.GetSeconds());
			Assert::IsTrue(ElapsedSecondsTotal > 10.0 && ElapsedSecondsTotal < 11.0);
		}
		TEST_METHOD(AwaitSignal)
		{
			Assert::Fail();
			/*
			_WorkerThreadId = std::this_thread::get_id();

			DateTime Start = DateTime::Now();
			Thread T = Thread();
			T.Start(Delegate<void>::CreateDelegate<Core_Threading_Thread, &Core_Threading_Thread::LongRunning>(*this));

			// this should block until Thread T unlocks the mutex
			// ToDo

			TimeSpan ElapsedTime = DateTime::Now() - Start;

			double TotallyElapsedSeconds = ElapsedTime.GetTotalSeconds();
			Assert::IsTrue(TotallyElapsedSeconds > 5.0 && TotallyElapsedSeconds < 6.0);
			*/
		}
	private:
		int _OriginalValue = 5;
		int _CalculatedValue;
		std::thread::id _WorkerThreadId;

		Mutex _Mutex = Mutex();

		void ZeroParameterThreadStart()
		{
			_CalculatedValue = _OriginalValue * _OriginalValue;
			_WorkerThreadId = std::this_thread::get_id();
		}
		void SingleParameterThreadStart(int OriginalValue)
		{
			_CalculatedValue = OriginalValue * OriginalValue;
			_WorkerThreadId = std::this_thread::get_id();
		}
		void LongRunning()
		{
			Thread::Sleep(TimeSpan::FromSeconds(5));
		}
		void RunMutex()
		{
			_Mutex.Lock();
			Thread::Sleep(TimeSpan::FromSeconds(5));
			_Mutex.Unlock();
		}
	};
}
