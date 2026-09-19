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
            Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t> Task = PerformMostInternalTask();
            Task.Wait();
            Assert::AreEqual(1_ui8, Task.GetResult());
        }

        TEST_METHOD(ChainedLoopedTaskTest)
        {
            Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t> Task1 = PerformOuterLoopedTask(3_ui8);
            Task1.Wait();
            Assert::AreEqual(3_ui8, Task1.GetResult());
            
            Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t> Task2 = PerformOuterLoopedTask(24_ui8);
            Task2.Wait();
            Assert::AreEqual(24_ui8, Task2.GetResult());
        }

        TEST_METHOD(ChainedRecursiveTaskTest)
        {
            Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t> Task1 = PerformOuterRecursiveTask(3_ui8);
            Task1.Wait();
            Assert::AreEqual(3_ui8, Task1.GetResult());

            Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t> Task2 = PerformOuterRecursiveTask(24_ui8);
            Task2.Wait();
            Assert::AreEqual(24_ui8, Task2.GetResult());
        }
    private:
        Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t> PerformMostInternalTask()
        {
            co_return 1;
        }

        Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t> PerformOuterRecursiveTask(Elysium::Core::Template::System::uint8_t Iterations)
        {
            if (Iterations > 1)
            {
                Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t> Task = PerformOuterRecursiveTask(--Iterations);
                co_await Task;

                co_return Task.GetResult() + 1;
            }
            else
            {
                Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t> Task = PerformMostInternalTask();
                co_await Task;

                co_return Task.GetResult();
            }
        }

        Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t> PerformOuterLoopedTask(Elysium::Core::Template::System::uint8_t Iterations)
        {
            Elysium::Core::Template::System::uint8_t Result{};

            for (Elysium::Core::Template::System::uint8_t i = 0; i < Iterations; ++i)
            {
                Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t> Task = PerformMostInternalTask();
                co_await Task;

                Result += Task.GetResult();
            }

            co_return Result;
        }
    };
}
