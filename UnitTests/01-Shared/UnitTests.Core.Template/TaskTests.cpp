#include "CppUnitTest.h"
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/Atomic.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Threading/Tasks/Task.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/System/Literals.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/System/Primitives.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Threading::Tasks
{
    TEST_CLASS(TaskTests)
    {
    public:
        TEST_METHOD(SinglularTaskTest)
        {
            Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t> Task = PerformTaskDepthZero();
            Task.Wait();
            Assert::AreEqual(0_ui8, Task.GetResult());
        }

        TEST_METHOD(ChainedTaskTest)
        {
            Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t> Task1 = PerformTaskDepthOne();
            Task1.Wait();
            Assert::AreEqual(1_ui8, Task1.GetResult());

            Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t> Task2 = PerformTaskDepthTwo();
            Task2.Wait();
            Assert::AreEqual(2_ui8, Task2.GetResult());
        }
    private:
        Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t> PerformTaskDepthZero()
        {
            co_return 0;
        }

        Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t> PerformTaskDepthOne()
        {
            Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t> Task = PerformTaskDepthZero();
            co_await Task;

            co_return Task.GetResult() + 1;
        }

        Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t> PerformTaskDepthTwo()
        {
            Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t> Task = PerformTaskDepthOne();
            co_await Task;

            co_return Task.GetResult() + 1;
        }
    };
}
