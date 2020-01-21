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

namespace UnitTestsCore
{
	TEST_CLASS(Core_Threading_Tasks_Task)
	{
	public:
		TEST_METHOD(RunSynchronouslySuccessfully)
		{
			_WorkerThreadId = std::this_thread::get_id();

			Task SimpleTask = Task(Delegate<void>::CreateDelegate<Core_Threading_Tasks_Task, &Core_Threading_Tasks_Task::ZeroParameterThreadStart>(*this));
			SimpleTask.RunSynchronously();

			Assert::AreEqual(25, _CalculatedValue);
			Assert::IsTrue(std::this_thread::get_id() == _WorkerThreadId);
			Assert::IsTrue(SimpleTask.GetIsCompletedSuccessfully());
		}
		TEST_METHOD(RunSynchronouslyCancelled)
		{
			_WorkerThreadId = std::this_thread::get_id();

			Task SimpleTask = Task(Delegate<void>::CreateDelegate<Core_Threading_Tasks_Task, &Core_Threading_Tasks_Task::Cancel>(*this));
			SimpleTask.RunSynchronously();

			Assert::AreEqual(123, _CalculatedValue);
			Assert::IsTrue(std::this_thread::get_id() == _WorkerThreadId);
			Assert::IsTrue(SimpleTask.GetIsCanceled());
		}
		TEST_METHOD(RunSynchronouslyFaulted)
		{
			_WorkerThreadId = std::this_thread::get_id();

			Task SimpleTask = Task(Delegate<void>::CreateDelegate<Core_Threading_Tasks_Task, &Core_Threading_Tasks_Task::ThrowException>(*this));
			SimpleTask.RunSynchronously();

			Assert::AreEqual(3, _CalculatedValue);
			Assert::IsTrue(std::this_thread::get_id() == _WorkerThreadId);
			Assert::IsTrue(SimpleTask.GetIsFaulted());
		}

		TEST_METHOD(RunAsynchronously)
		{
			_WorkerThreadId = std::this_thread::get_id();

			Elysium::Core::Threading::ThreadPool Pool = Elysium::Core::Threading::ThreadPool(1);
			Pool.Start();
			Task SimpleTask = Task(Delegate<void>::CreateDelegate<Core_Threading_Tasks_Task, &Core_Threading_Tasks_Task::ZeroParameterThreadStart>(*this));
			SimpleTask.Start(Pool);
			SimpleTask.Wait();
			Pool.Stop();

			Assert::AreEqual(25, _CalculatedValue);
			Assert::IsFalse(std::this_thread::get_id() == _WorkerThreadId);
			Assert::IsTrue(SimpleTask.GetIsCompletedSuccessfully());
		}
		TEST_METHOD(RunAsynchronouslyAndAwaitLongRunning)
		{
			_WorkerThreadId = std::this_thread::get_id();

			Elysium::Core::Threading::ThreadPool Pool = Elysium::Core::Threading::ThreadPool(1);
			Pool.Start();
			Task SimpleTask = Task(Delegate<void>::CreateDelegate<Core_Threading_Tasks_Task, &Core_Threading_Tasks_Task::LongRunning>(*this));
			DateTime Start = DateTime::Now();
			SimpleTask.Start(Pool);
			SimpleTask.Wait();
			TimeSpan ElapsedTime = DateTime::Now() - Start;
			Pool.Stop();

			Assert::IsTrue(ElapsedTime.GetTotalSeconds() > 5.0);
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
			throw Exception(u"any exception");
		}

		void LongRunning()
		{
			Thread::Sleep(TimeSpan::FromSeconds(5));
		}
	};
}
