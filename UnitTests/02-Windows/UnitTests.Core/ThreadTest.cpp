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

using namespace Elysium::Core::Globalization;
using namespace Elysium::Core::Threading;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsCore
{
	TEST_CLASS(Core_Threading_Thread)
	{
	public:
		TEST_METHOD(ThreadStart)
		{

		}
		TEST_METHOD(ParameterizedThreadStart)
		{

		}
		TEST_METHOD(Culture)
		{
			CultureInfo CurrentCulture;
			Assert::AreEqual((int)GetSystemDefaultLCID(), CurrentCulture.GetLCID());

			//Thread::GetCurrentCulture(&CurrentCulture);
			//Assert::AreEqual((int)GetSystemDefaultLCID(), CurrentCulture.GetLCID());
		}
	};
}
