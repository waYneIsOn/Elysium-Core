#include "CppUnitTest.h"
#include "../../01-Shared/UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.Threading/Task.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/ThreadPool.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/Thread.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core/DateTime.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core/TimeSpan.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/OperationCanceledException.hpp"

#include <thread>
#include <Windows.h>

using namespace Elysium::Core;
using namespace Elysium::Core::Template::Container;
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

			Task SimpleTask = Task(Delegate<void>::Bind<TaskTests, &TaskTests::ZeroParameterThreadStart>(*this));
			SimpleTask.RunSynchronously();

			Assert::AreEqual(25, _CalculatedValue);
			Assert::IsTrue(std::this_thread::get_id() == _WorkerThreadId);
			Assert::IsTrue(SimpleTask.GetIsCompletedSuccessfully());
		}

		TEST_METHOD(RunSynchronouslyCancelled)
		{
			_WorkerThreadId = std::this_thread::get_id();

			Task SimpleTask = Task(Delegate<void>::Bind<TaskTests, &TaskTests::Cancel>(*this));
			SimpleTask.RunSynchronously();

			Assert::AreEqual(123, _CalculatedValue);
			Assert::IsTrue(std::this_thread::get_id() == _WorkerThreadId);
			Assert::IsTrue(SimpleTask.GetIsCanceled());
		}

		TEST_METHOD(RunSynchronouslyFaulted)
		{
			_WorkerThreadId = std::this_thread::get_id();

			Task SimpleTask = Task(Delegate<void>::Bind<TaskTests, &TaskTests::ThrowException>(*this));
			SimpleTask.RunSynchronously();

			Assert::AreEqual(3, _CalculatedValue);
			Assert::IsTrue(std::this_thread::get_id() == _WorkerThreadId);
			Assert::IsTrue(SimpleTask.GetIsFaulted());
		}

		TEST_METHOD(RunAsynchronously)
		{
			_WorkerThreadId = std::this_thread::get_id();
			
			Task SimpleTask = Task(Delegate<void>::Bind<TaskTests, &TaskTests::ZeroParameterThreadStart>(*this));
			SimpleTask.Start();
			SimpleTask.Wait();

			Assert::AreEqual(25, _CalculatedValue);
			Assert::IsTrue(std::this_thread::get_id() != _WorkerThreadId);
			Assert::IsTrue(SimpleTask.GetIsCompletedSuccessfully());
		}

		TEST_METHOD(RunAsynchronouslyAndAwaitLongRunning)
		{
			_WorkerThreadId = std::this_thread::get_id();
			
			Task SimpleTask = Task(Delegate<void>::Bind<TaskTests, &TaskTests::LongRunning>(*this));
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
