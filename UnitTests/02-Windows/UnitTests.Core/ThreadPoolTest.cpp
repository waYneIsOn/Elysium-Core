#include "CppUnitTest.h"

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#include "CppUnitTestFrameworkExtension.hpp"
#endif

#ifndef ELYSIUM_CORE_ENVIRONMENT
#include "../../../Libraries/01-Shared/Elysium.Core/Environment.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_THREADPOOL
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/ThreadPool.hpp"
#endif

using namespace Elysium::Core;
using namespace Elysium::Core::Threading;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Threading
{
	TEST_CLASS(ThreadPoolTest)
	{
	public:
		TEST_METHOD(ReadProperties)
		{
			Elysium::Core::uint32_t WorkerThreads;
			Elysium::Core::uint32_t IOThreads;

			ThreadPool::GetAvailableThreads(WorkerThreads, IOThreads);

			Assert::AreEqual((const Elysium::Core::uint32_t)2047, WorkerThreads);
			Assert::AreEqual((const Elysium::Core::uint32_t)1000, IOThreads);
		}
	};
}
