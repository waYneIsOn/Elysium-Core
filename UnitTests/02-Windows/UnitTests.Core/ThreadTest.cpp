#include "CppUnitTest.h"
#include "CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core/DateTime.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core/TimeSpan.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/AutoResetEvent.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/CriticalSection.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/Interlocked.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/ManualResetEvent.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/Mutex.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/Thread.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/Semaphore.hpp"

#include <thread>
#include <Windows.h>

using namespace Elysium::Core;
using namespace Elysium::Core::Template::Container;
using namespace Elysium::Core::Threading;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Threading
{
	TEST_CLASS(ThreadTests)
	{
	public:
		TEST_METHOD(ThreadStartThread)
		{
			_WorkerThreadId = std::this_thread::get_id();

			Thread T = Thread(Delegate<void>::Bind<ThreadTests, &ThreadTests::ZeroParameterThreadStart>(*this));
			T.Start();
			T.Join();
			Assert::AreEqual(25, _CalculatedValue);
			Assert::IsFalse(std::this_thread::get_id() == _WorkerThreadId);
		}
		TEST_METHOD(ParameterizedThreadStartThread)
		{
			_WorkerThreadId = std::this_thread::get_id();

			Thread T = Thread(Delegate<void, void*>::Bind<ThreadTests, &ThreadTests::SingleParameterThreadStart>(*this));
			int Value = 6;
			T.Start(static_cast<void*>(&Value));
			T.Join();
			Assert::AreEqual(36, _CalculatedValue);
			Assert::IsFalse(std::this_thread::get_id() == _WorkerThreadId);
		}

		TEST_METHOD(LongRunningJoin)
		{
			DateTime Start = DateTime::Now();
			Thread T = Thread(Delegate<void>::Bind<ThreadTests, &ThreadTests::LongRunning>(*this));
			T.Start();
			T.Join();
			TimeSpan ElapsedTime = DateTime::Now() - Start;
			double ElapsedSecondsTotal = ElapsedTime.GetTotalSeconds();
			Assert::AreEqual(5, ElapsedTime.GetSeconds());
			Assert::IsTrue(ElapsedSecondsTotal > 5.0 && ElapsedSecondsTotal < 6.0);
		}

		TEST_METHOD(InterlockedIncrementAndDecrement)
		{
			const int NumberOfThreads = 10;
			int NumberOfIncrementsPerThread = 10000;

			Thread IncrementTs[NumberOfThreads] =
			{
				Thread(Delegate<void, void*>::Bind<ThreadTests, &ThreadTests::IncrementInterlocked>(*this)),
				Thread(Delegate<void, void*>::Bind<ThreadTests, &ThreadTests::IncrementInterlocked>(*this)),
				Thread(Delegate<void, void*>::Bind<ThreadTests, &ThreadTests::IncrementInterlocked>(*this)),
				Thread(Delegate<void, void*>::Bind<ThreadTests, &ThreadTests::IncrementInterlocked>(*this)),
				Thread(Delegate<void, void*>::Bind<ThreadTests, &ThreadTests::IncrementInterlocked>(*this)),
				Thread(Delegate<void, void*>::Bind<ThreadTests, &ThreadTests::IncrementInterlocked>(*this)),
				Thread(Delegate<void, void*>::Bind<ThreadTests, &ThreadTests::IncrementInterlocked>(*this)),
				Thread(Delegate<void, void*>::Bind<ThreadTests, &ThreadTests::IncrementInterlocked>(*this)),
				Thread(Delegate<void, void*>::Bind<ThreadTests, &ThreadTests::IncrementInterlocked>(*this)),
				Thread(Delegate<void, void*>::Bind<ThreadTests, &ThreadTests::IncrementInterlocked>(*this))
			};
			for (uint16_t i = 0; i < NumberOfThreads; i++)
			{
				IncrementTs[i].Start(static_cast<void*>(&NumberOfIncrementsPerThread));
			}
			for (uint16_t i = 0; i < NumberOfThreads; i++)
			{
				IncrementTs[i].Join();
			}
			Assert::AreEqual(NumberOfThreads * NumberOfIncrementsPerThread, _InterlockedInteger);

			Thread DecrementTs[NumberOfThreads] =
			{
				Thread(Delegate<void, void*>::Bind<ThreadTests, &ThreadTests::DecrementInterlocked>(*this)),
				Thread(Delegate<void, void*>::Bind<ThreadTests, &ThreadTests::DecrementInterlocked>(*this)),
				Thread(Delegate<void, void*>::Bind<ThreadTests, &ThreadTests::DecrementInterlocked>(*this)),
				Thread(Delegate<void, void*>::Bind<ThreadTests, &ThreadTests::DecrementInterlocked>(*this)),
				Thread(Delegate<void, void*>::Bind<ThreadTests, &ThreadTests::DecrementInterlocked>(*this)),
				Thread(Delegate<void, void*>::Bind<ThreadTests, &ThreadTests::DecrementInterlocked>(*this)),
				Thread(Delegate<void, void*>::Bind<ThreadTests, &ThreadTests::DecrementInterlocked>(*this)),
				Thread(Delegate<void, void*>::Bind<ThreadTests, &ThreadTests::DecrementInterlocked>(*this)),
				Thread(Delegate<void, void*>::Bind<ThreadTests, &ThreadTests::DecrementInterlocked>(*this)),
				Thread(Delegate<void, void*>::Bind<ThreadTests, &ThreadTests::DecrementInterlocked>(*this))
			};
			for (uint16_t i = 0; i < NumberOfThreads; i++)
			{
				DecrementTs[i].Start(static_cast<void*>(&NumberOfIncrementsPerThread));
			}
			for (uint16_t i = 0; i < NumberOfThreads; i++)
			{
				DecrementTs[i].Join();
			}
			Assert::AreEqual(0, _InterlockedInteger);
		}

		TEST_METHOD(MutexLock)
		{
			DateTime Start = DateTime::Now();
			Thread T = Thread(Delegate<void>::Bind<ThreadTests, &ThreadTests::RunMutex>(*this));
			T.Start();

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
			Thread T = Thread(Delegate<void>::Bind<ThreadTests, &ThreadTests::RunMutex>(*this));
			T.Start();

			// sleep for a bit just to make sure T has locked the mutex
			Thread::Sleep(TimeSpan::FromSeconds(1));
			_Mutex.WaitOne();
			_Mutex.Unlock();

			TimeSpan ElapsedTime = DateTime::Now() - Start;
			double ElapsedSecondsTotal = ElapsedTime.GetTotalSeconds();
			Assert::AreEqual(5, ElapsedTime.GetSeconds());
			Assert::IsTrue(ElapsedSecondsTotal > 5.0 && ElapsedSecondsTotal < 6.0);
		}

		TEST_METHOD(CriticalSectionTest)
		{
			DateTime Start = DateTime::Now();
			Thread T = Thread(Delegate<void>::Bind<ThreadTests, &ThreadTests::RunCriticalSection>(*this));
			T.Start();

			// sleep for a bit just to make sure T has entered the critical section
			Thread::Sleep(TimeSpan::FromSeconds(1));
			_CriticalSection.Enter();
			_CriticalSection.Exit();

			TimeSpan ElapsedTime = DateTime::Now() - Start;
			double ElapsedSecondsTotal = ElapsedTime.GetTotalSeconds();
			Assert::AreEqual(5, ElapsedTime.GetSeconds());
			Assert::IsTrue(ElapsedSecondsTotal > 5.0 && ElapsedSecondsTotal < 6.0);
		}

		TEST_METHOD(AutoResetEventWaitOne)
		{
			DateTime Start = DateTime::Now();
			Thread T = Thread(Delegate<void>::Bind<ThreadTests, &ThreadTests::RunAutoResetEvent>(*this));
			T.Start();

			_AutoResetEvent.WaitOne();

			TimeSpan ElapsedTime = DateTime::Now() - Start;
			double ElapsedSecondsTotal = ElapsedTime.GetTotalSeconds();
			Assert::AreEqual(5, ElapsedTime.GetSeconds());
			Assert::IsTrue(ElapsedSecondsTotal > 5.0 && ElapsedSecondsTotal < 6.0);
		}

		TEST_METHOD(ManualResetEventWaitOne)
		{
			DateTime Start = DateTime::Now();
			Thread T = Thread(Delegate<void>::Bind<ThreadTests, &ThreadTests::RunManualResetEvent>(*this));
			T.Start();

			_ManualResetEvent.WaitOne();

			TimeSpan ElapsedTime = DateTime::Now() - Start;
			double ElapsedSecondsTotal = ElapsedTime.GetTotalSeconds();
			Assert::AreEqual(5, ElapsedTime.GetSeconds());
			Assert::IsTrue(ElapsedSecondsTotal > 5.0 && ElapsedSecondsTotal < 6.0);
		}

		TEST_METHOD(SemaphoreWaitOne)
		{
			const int NumberOfThreads = 3;
			
			Thread Ts[NumberOfThreads] = 
			{
				Thread(Delegate<void>::Bind<ThreadTests, &ThreadTests::RunSemaphore>(*this)),
				Thread(Delegate<void>::Bind<ThreadTests, &ThreadTests::RunSemaphore>(*this)),
				Thread(Delegate<void>::Bind<ThreadTests, &ThreadTests::RunSemaphore>(*this))
			};
			DateTime Start = DateTime::Now();
			for (uint16_t i = 0; i < NumberOfThreads; i++)
			{
				Ts[i].Start();
			}

			for (uint16_t i = 0; i < NumberOfThreads; i++)
			{
				Ts[i].Join();
			}

			TimeSpan ElapsedTime = DateTime::Now() - Start;
			double ElapsedSecondsTotal = ElapsedTime.GetTotalSeconds();
			Assert::AreEqual(NumberOfThreads * 5, ElapsedTime.GetSeconds());
			Assert::IsTrue(ElapsedSecondsTotal > NumberOfThreads * 5  && ElapsedSecondsTotal < NumberOfThreads * 5 + 1);
		}
	private:
		int _OriginalValue = 5;
		int _CalculatedValue;
		std::thread::id _WorkerThreadId;

		int32_t _InterlockedInteger = 0;
		Mutex _Mutex = Mutex();
		CriticalSection _CriticalSection = CriticalSection();
		AutoResetEvent _AutoResetEvent = AutoResetEvent(false);
		ManualResetEvent _ManualResetEvent = ManualResetEvent(false);
		Semaphore _Semaphore = Semaphore(1, 1);

		void ZeroParameterThreadStart()
		{
			_CalculatedValue = _OriginalValue * _OriginalValue;
			_WorkerThreadId = std::this_thread::get_id();
		}
		void SingleParameterThreadStart(void* Input)
		{
			int* OriginalValue = static_cast<int*>(Input);

			_CalculatedValue = *OriginalValue * *OriginalValue;
			_WorkerThreadId = std::this_thread::get_id();
		}

		void LongRunning()
		{
			Thread::Sleep(TimeSpan::FromSeconds(5));
		}

		void IncrementInterlocked(void* Input)
		{
			int* NumberOfIncrementsPerThread = static_cast<int*>(Input);
			for (uint16_t i = 0; i < *NumberOfIncrementsPerThread; i++)
			{
				//_InterlockedInteger = _InterlockedInteger + 1;
				Interlocked::Increment(&_InterlockedInteger);
			}
		}
		void DecrementInterlocked(void* Input)
		{
			int* NumberOfIncrementsPerThread = static_cast<int*>(Input);
			for (uint16_t i = 0; i < *NumberOfIncrementsPerThread; i++)
			{
				//_InterlockedInteger = _InterlockedInteger - 1;
				Interlocked::Decrement(&_InterlockedInteger);
			}
		}

		void RunMutex()
		{
			_Mutex.WaitOne();
			Thread::Sleep(TimeSpan::FromSeconds(5));
			_Mutex.Unlock();
		}

		void RunCriticalSection()
		{
			_CriticalSection.Enter();
			Thread::Sleep(TimeSpan::FromSeconds(5));
			_CriticalSection.Exit();
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
			const bool IsSignaled = _Semaphore.WaitOne();
			Thread::Sleep(TimeSpan::FromSeconds(5));
			const int PreviousCount = _Semaphore.Release();
		}
	};
}
