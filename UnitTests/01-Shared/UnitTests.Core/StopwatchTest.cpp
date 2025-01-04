#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Diagnostics/Stopwatch.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Threading/Thread.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Diagnostics;
using namespace Elysium::Core::Threading;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Diagnostics
{
	TEST_CLASS(StopwatchTest)
	{
	public:
		TEST_METHOD(Bla)
		{
			const bool IsHighResolution = Stopwatch::IsHighResolution;
			Elysium::Core::int64_t Frequency = Stopwatch::Frequency;

			Stopwatch Watch = Stopwatch();
			Watch.Start();

			Thread::Sleep(TimeSpan::FromSeconds(1));
			const Elysium::Core::TimeSpan ElapsedTimeWhileRunning = Watch.GetElapsed();
			Assert::IsTrue(ElapsedTimeWhileRunning.GetTotalMilliseconds() > 1000);

			Thread::Sleep(TimeSpan::FromSeconds(1));
			Watch.Stop();

			const Elysium::Core::TimeSpan ElapsedTimeAfterStop = Watch.GetElapsed();
			Assert::IsTrue(ElapsedTimeAfterStop.GetTotalMilliseconds() > 2000);
		}

	};
}
