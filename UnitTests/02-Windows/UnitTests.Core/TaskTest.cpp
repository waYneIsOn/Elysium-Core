#include "CppUnitTest.h"

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#include "CppUnitTestFrameworkExtension.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_TASKS_TASK
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/Task.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_THREADPOOL
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/ThreadPool.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_THREAD
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/Thread.hpp"
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

#ifndef ELYSIUM_CORE_THREADING_TASKS_OPERATIONCANCELEDEXCEPTION
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/OperationCanceledException.hpp"
#endif

#ifndef _THREAD_
#include <thread>
#endif

using namespace Elysium::Core;
using namespace Elysium::Core::Threading;
using namespace Elysium::Core::Threading::Tasks;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Threading
{
	TEST_CLASS(TaskTests)
	{
	public:
		TEST_METHOD(RunSynchronouslySuccessfully)
		{
			_WorkerThreadId = std::this_thread::get_id();

			Task SimpleTask = Task(Delegate<void>::CreateDelegate<TaskTests, &TaskTests::ZeroParameterThreadStart>(*this));
			SimpleTask.RunSynchronously();

			Assert::AreEqual(25, _CalculatedValue);
			Assert::IsTrue(std::this_thread::get_id() == _WorkerThreadId);
			Assert::IsTrue(SimpleTask.GetIsCompletedSuccessfully());
		}
		TEST_METHOD(RunSynchronouslyCancelled)
		{
			_WorkerThreadId = std::this_thread::get_id();

			Task SimpleTask = Task(Delegate<void>::CreateDelegate<TaskTests, &TaskTests::Cancel>(*this));
			SimpleTask.RunSynchronously();

			Assert::AreEqual(123, _CalculatedValue);
			Assert::IsTrue(std::this_thread::get_id() == _WorkerThreadId);
			Assert::IsTrue(SimpleTask.GetIsCanceled());
		}
		TEST_METHOD(RunSynchronouslyFaulted)
		{
			_WorkerThreadId = std::this_thread::get_id();

			Task SimpleTask = Task(Delegate<void>::CreateDelegate<TaskTests, &TaskTests::ThrowException>(*this));
			SimpleTask.RunSynchronously();

			Assert::AreEqual(3, _CalculatedValue);
			Assert::IsTrue(std::this_thread::get_id() == _WorkerThreadId);
			Assert::IsTrue(SimpleTask.GetIsFaulted());
		}

		TEST_METHOD(RunAsynchronously)
		{
			_WorkerThreadId = std::this_thread::get_id();
			
			Task SimpleTask = Task(Delegate<void>::CreateDelegate<TaskTests, &TaskTests::ZeroParameterThreadStart>(*this));
			SimpleTask.Start();
			SimpleTask.Wait();

			Assert::AreEqual(25, _CalculatedValue);
			Assert::IsTrue(std::this_thread::get_id() != _WorkerThreadId);
			Assert::IsTrue(SimpleTask.GetIsCompletedSuccessfully());
		}
		TEST_METHOD(RunAsynchronouslyAndAwaitLongRunning)
		{
			_WorkerThreadId = std::this_thread::get_id();
			
			Task SimpleTask = Task(Delegate<void>::CreateDelegate<TaskTests, &TaskTests::LongRunning>(*this));
			DateTime Start = DateTime::Now();
			SimpleTask.Start();
			SimpleTask.Wait();
			TimeSpan ElapsedTime = DateTime::Now() - Start;

			Assert::IsTrue(ElapsedTime.GetTotalSeconds() > 5.0);
			Assert::IsTrue(std::this_thread::get_id() != _WorkerThreadId);
			Assert::IsTrue(SimpleTask.GetIsCompletedSuccessfully());
		}
	private:
		int _OriginalValue = 5;
		int _CalculatedValue;
		std::thread::id _WorkerThreadId;

		void ZeroParameterThreadStart()
		{
			_CalculatedValue = _OriginalValue * _OriginalValue;
			_WorkerThreadId = std::this_thread::get_id();
		}
		void Cancel()
		{
			_CalculatedValue = 123;
			_WorkerThreadId = std::this_thread::get_id();
			throw OperationCanceledException();
		}
		void ThrowException()
		{
			_CalculatedValue = 3;
			_WorkerThreadId = std::this_thread::get_id();
			throw Exception(u8"any exception");
		}

		void LongRunning()
		{
			_WorkerThreadId = std::this_thread::get_id();
			Thread::Sleep(TimeSpan::FromSeconds(5));
		}
	};
}
