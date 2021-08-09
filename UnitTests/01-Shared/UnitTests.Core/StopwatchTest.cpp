#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Diagnostics/Stopwatch.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Collections::Template;
using namespace Elysium::Core::Diagnostics;
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
			Watch.Stop();

			const Elysium::Core::TimeSpan ElapsedTime = Watch.GetElapsed();
			const Elysium::Core::int32_t ElapsedSeconds = ElapsedTime.GetSeconds();
		}

	};
}
