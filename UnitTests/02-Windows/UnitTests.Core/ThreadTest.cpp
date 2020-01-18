#include "CppUnitTest.h"

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#include "CppUnitTestFrameworkExtension.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_THREAD
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/Thread.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_INTERLOCKED
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/Interlocked.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_MUTEX
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/Mutex.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_AUTORESETEVENT
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/AutoResetEvent.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_MANUALRESETEVENT
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/ManualResetEvent.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_SEMAPHORE
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/Semaphore.hpp"
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

		TEST_METHOD(LongRunningJoin)
		{
			DateTime Start = DateTime::Now();
			Thread T = Thread();
			T.Start(Delegate<void>::CreateDelegate<Core_Threading_Thread, &Core_Threading_Thread::LongRunning>(*this));
			T.Join();
			TimeSpan ElapsedTime = DateTime::Now() - Start;
			double ElapsedSecondsTotal = ElapsedTime.GetTotalSeconds();
			Assert::AreEqual(5, ElapsedTime.GetSeconds());
			Assert::IsTrue(ElapsedSecondsTotal > 5.0 && ElapsedSecondsTotal < 6.0);
		}

		TEST_METHOD(InterlockedIncrementAndDecrement)
		{
			const int NumberOfThreads = 64;
			const int NumberOfIncrementsPerThread = 10000;

			Thread T[NumberOfThreads];
			for (uint16_t i = 0; i < NumberOfThreads; i++)
			{
				T[i].Start<const int>(Delegate<void, const int>::CreateDelegate<Core_Threading_Thread, &Core_Threading_Thread::IncrementInterlocked>(*this), NumberOfIncrementsPerThread);
			}
			for (uint16_t i = 0; i < NumberOfThreads; i++)
			{
				T[i].Join();
			}
			Assert::AreEqual(NumberOfThreads * NumberOfIncrementsPerThread, _InterlockedInteger);

			for (uint16_t i = 0; i < NumberOfThreads; i++)
			{
				T[i].Start<const int>(Delegate<void, const int>::CreateDelegate<Core_Threading_Thread, &Core_Threading_Thread::DecrementInterlocked>(*this), NumberOfIncrementsPerThread);
			}
			for (uint16_t i = 0; i < NumberOfThreads; i++)
			{
				T[i].Join();
			}
			Assert::AreEqual(0, _InterlockedInteger);
		}

		TEST_METHOD(MutexLock)
		{
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
		TEST_METHOD(MutexWaitOne)
		{
			DateTime Start = DateTime::Now();
			Thread T = Thread();
			T.Start(Delegate<void>::CreateDelegate<Core_Threading_Thread, &Core_Threading_Thread::RunMutex>(*this));

			// sleep for a bit just to make sure T has locked the mutex
			Thread::Sleep(TimeSpan::FromSeconds(1));
			_Mutex.WaitOne();
			_Mutex.ReleaseMutex();

			TimeSpan ElapsedTime = DateTime::Now() - Start;
			double ElapsedSecondsTotal = ElapsedTime.GetTotalSeconds();
			Assert::AreEqual(5, ElapsedTime.GetSeconds());
			Assert::IsTrue(ElapsedSecondsTotal > 5.0 && ElapsedSecondsTotal < 6.0);
		}

		TEST_METHOD(AutoResetEventWaitOne)
		{
			DateTime Start = DateTime::Now();
			Thread T = Thread();
			T.Start(Delegate<void>::CreateDelegate<Core_Threading_Thread, &Core_Threading_Thread::RunAutoResetEvent>(*this));

			_AutoResetEvent.WaitOne();

			TimeSpan ElapsedTime = DateTime::Now() - Start;
			double ElapsedSecondsTotal = ElapsedTime.GetTotalSeconds();
			Assert::AreEqual(5, ElapsedTime.GetSeconds());
			Assert::IsTrue(ElapsedSecondsTotal > 5.0 && ElapsedSecondsTotal < 6.0);
		}

		TEST_METHOD(ManualResetEventWaitOne)
		{
			DateTime Start = DateTime::Now();
			Thread T = Thread();
			T.Start(Delegate<void>::CreateDelegate<Core_Threading_Thread, &Core_Threading_Thread::RunManualResetEvent>(*this));

			_ManualResetEvent.WaitOne();

			TimeSpan ElapsedTime = DateTime::Now() - Start;
			double ElapsedSecondsTotal = ElapsedTime.GetTotalSeconds();
			Assert::AreEqual(5, ElapsedTime.GetSeconds());
			Assert::IsTrue(ElapsedSecondsTotal > 5.0 && ElapsedSecondsTotal < 6.0);
		}

		TEST_METHOD(SemaphoreWaitOne)
		{
			DateTime Start = DateTime::Now();
			Thread T = Thread();
			T.Start(Delegate<void>::CreateDelegate<Core_Threading_Thread, &Core_Threading_Thread::RunSemaphore>(*this));

			// sleep for a bit just to make sure T has incremented the semaphore
			Thread::Sleep(TimeSpan::FromSeconds(1));
			_Semaphore.WaitOne();

			TimeSpan ElapsedTime = DateTime::Now() - Start;
			double ElapsedSecondsTotal = ElapsedTime.GetTotalSeconds();
			Assert::AreEqual(10, ElapsedTime.GetSeconds());
			Assert::IsTrue(ElapsedSecondsTotal > 10.0 && ElapsedSecondsTotal < 11.0);
		}
	private:
		int _OriginalValue = 5;
		int _CalculatedValue;
		std::thread::id _WorkerThreadId;

		int32_t _InterlockedInteger = 0;
		Mutex _Mutex = Mutex();
		AutoResetEvent _AutoResetEvent = AutoResetEvent(false);
		ManualResetEvent _ManualResetEvent = ManualResetEvent(false);
		Semaphore _Semaphore = Semaphore(0, 1);

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

		void IncrementInterlocked(const int NumberOfIncrementsPerThread)
		{
			for (uint16_t i = 0; i < NumberOfIncrementsPerThread; i++)
			{
				//_InterlockedInteger = _InterlockedInteger + 1;
				Interlocked::Increment(_InterlockedInteger);
			}
		}
		void DecrementInterlocked(const int NumberOfIncrementsPerThread)
		{
			for (uint16_t i = 0; i < NumberOfIncrementsPerThread; i++)
			{
				//_InterlockedInteger = _InterlockedInteger - 1;
				Interlocked::Decrement(_InterlockedInteger);
			}
		}

		void RunMutex()
		{
			_Mutex.WaitOne();
			Thread::Sleep(TimeSpan::FromSeconds(5));
			_Mutex.ReleaseMutex();
		}

		void RunAutoResetEvent()
		{
			Thread::Sleep(TimeSpan::FromSeconds(5));
			_AutoResetEvent.Set();
		}

		void RunManualResetEvent()
		{
			Thread::Sleep(TimeSpan::FromSeconds(5));
			_ManualResetEvent.Set();
			_ManualResetEvent.Reset();
		}

		void RunSemaphore()
		{
			_Semaphore.Increment();
			Thread::Sleep(TimeSpan::FromSeconds(5));
			_Semaphore.Decrement();
		}
	};
}
