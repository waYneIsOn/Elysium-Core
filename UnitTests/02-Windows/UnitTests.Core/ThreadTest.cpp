#include "CppUnitTest.h"

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#include "CppUnitTestFrameworkExtension.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_THREAD
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/Thread.hpp"
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
	private:
		int _OriginalValue = 5;
		int _CalculatedValue;
		std::thread::id _WorkerThreadId;

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
	};
}
