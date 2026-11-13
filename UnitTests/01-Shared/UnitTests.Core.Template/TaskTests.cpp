#include "CppUnitTest.h"

#include "../../../Libraries/01-Shared/Elysium.Core/String.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/Atomic.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.Template/Coroutines/Awaiter/DelegateAwaiter.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Coroutines/Awaiter/GetCurrentPromiseAwaiter.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Exceptions/Exception.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Threading/Thread.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Threading/Tasks/Task.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/System/Literals.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/System/Primitives.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Threading::Tasks
{
    TEST_CLASS(TaskTests)
    {
    public:
        TEST_METHOD(AwaitNothing)
        {
            //for (Elysium::Core::Template::System::size i = 0; i < 100000; ++i)
            for (Elysium::Core::Template::System::size i = 0; i < 100; ++i)
            {
                Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size> Task = PerformMostInternalTaskThroughDelegate(0 == i % 2);
            }
        }
    public:
        TEST_METHOD(ExceptionThrowingCoroutineTest)
        {
            Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::int32_t> ExceptionTask = ThrowException();
            ExceptionTask.Wait();
            Assert::AreEqual(0, ExceptionTask.GetResult());
        }
    private:
        inline Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::int32_t> ThrowException()
        {
            throw Elysium::Core::Template::Exceptions::Exception(u8"ThrowException");

            co_return 1;
        }
    public:
        TEST_METHOD(ExternallyManagedDelegateSinglularTaskTest)
        {
            Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size> TaskT = PerformMostInternalTaskThroughDelegate(true);
            TaskT.Wait();
            Assert::AreEqual(1_ui64, TaskT.GetResult());
        }

        TEST_METHOD(ExternallyManagedDelegateChainedLoopedTaskTest)
        {
            Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size> TaskT1 = PerformOuterLoopedTaskThroughDelegate(3, true);
            TaskT1.Wait();
            Assert::AreEqual(3_ui64, TaskT1.GetResult());

            Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size> TaskT2 = PerformOuterLoopedTaskThroughDelegate(24, true);
            TaskT2.Wait();
            Assert::AreEqual(24_ui64, TaskT2.GetResult());
            /*
            Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size> TaskT3 = PerformOuterLoopedTaskThroughDelegate(6000, true);
            TaskT3.Wait();
            Assert::AreEqual(6000_ui64, TaskT3.GetResult());
            */
        }

        TEST_METHOD(ExternallyManagedDelegateChainedRecursiveTaskTest)
        {
            Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size> TaskT1 = PerformOuterRecursiveTaskThroughDelegate(3, true);
            TaskT1.Wait();
            Assert::AreEqual(3_ui64, TaskT1.GetResult());

            Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size> TaskT2 = PerformOuterRecursiveTaskThroughDelegate(24, true);
            TaskT2.Wait();
            Assert::AreEqual(24_ui64, TaskT2.GetResult());
        }

        TEST_METHOD(DelegateSinglularTaskTest)
        {
            Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size> TaskF = PerformMostInternalTaskThroughDelegate(false);
            TaskF.Wait();
            Assert::AreEqual(1_ui64, TaskF.GetResult());
        }

        TEST_METHOD(DelegateChainedLoopedTaskTest)
        {
            Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size> TaskF1 = PerformOuterLoopedTaskThroughDelegate(3_ui8, false);
            TaskF1.Wait();
            Assert::AreEqual(3_ui64, TaskF1.GetResult());

            Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size> TaskF2 = PerformOuterLoopedTaskThroughDelegate(24_ui8, false);
            TaskF2.Wait();
            Assert::AreEqual(24_ui64, TaskF2.GetResult());
        }

        TEST_METHOD(DelegateChainedRecursiveTaskTest)
        {
            Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size> TaskF1 = PerformOuterRecursiveTaskThroughDelegate(3, false);
            TaskF1.Wait();
            Assert::AreEqual(3_ui64, TaskF1.GetResult());

            Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size> TaskF2 = PerformOuterRecursiveTaskThroughDelegate(24, false);
            TaskF2.Wait();
            Assert::AreEqual(24_ui64, TaskF2.GetResult());
        }
    private:
        inline void Start(Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size>::PromiseType& Promise, const bool ManagedExternally)
        {
            using PromiseType = Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size>::PromiseType;

            //Elysium::Core::Template::Threading::Thread::Sleep(5000);

            if (ManagedExternally)
            {   // this simulates IOCP running asynchronously through a callback
                Elysium::Core::Template::Container::Function Lambda = [](Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size>::PromiseType* Promise)
                {
                    //OutputDebugStringA("callback\r\n");
                    //Elysium::Core::Template::Threading::Thread::Sleep(50);
                    //Elysium::Core::Template::Threading::Thread::Sleep(500);
                    Elysium::Core::Template::Coroutines::CoroutineHandle<PromiseType> CoroutineFrameHandle = 
                        Elysium::Core::Template::Coroutines::CoroutineHandle<PromiseType>::FromPromise(*Promise);
                    CoroutineFrameHandle.resume();
                    // do NOT touch coroutine frame or promise after resume!!!!
                };

                Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size>::PromiseType& InternalPromise = Promise;

                Elysium::Core::Template::Threading::Thread SetSignalThread{};
                SetSignalThread.Start(Elysium::Core::Template::Functional::Move(Lambda), &InternalPromise);
            }
            else
            {   // this simulates IOCP running synchronously and returning right away
                //OutputDebugStringA("Delegate -> managed INTERNALLY -> resuming\r\n");
            }
        }

        inline Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size> PerformMostInternalTaskThroughDelegate(const bool ManagedExternally)
        {
            using AsyncPromiseType = Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size>::PromiseType;

            AsyncPromiseType& Promise = co_await Elysium::Core::Template::Coroutines::Awaiter::GetCurrentPromiseAwaiter<AsyncPromiseType>{};
            Promise._ManagedExternally = ManagedExternally;
            Promise._Name = "PerformMostInternalTaskThroughDelegate";

            using DelegateType = Elysium::Core::Template::Container::Delegate<void, AsyncPromiseType&, const bool>;
            using DelegateAwaiterType = Elysium::Core::Template::Coroutines::Awaiter::DelegateAwaiter<AsyncPromiseType, void, AsyncPromiseType&, const bool>;
            co_await DelegateAwaiterType(DelegateType::Bind<TaskTests, &TaskTests::Start>(*this), Promise, ManagedExternally);

            //Elysium::Core::Template::Threading::Thread::Sleep(500);

            co_return 1;
        }

        inline Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size> PerformOuterRecursiveTaskThroughDelegate(
            Elysium::Core::Template::System::size Iterations, const bool ManagedExternally)
        {
            using AsyncPromiseType = Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size>::PromiseType;

            AsyncPromiseType& Promise = co_await Elysium::Core::Template::Coroutines::Awaiter::GetCurrentPromiseAwaiter<AsyncPromiseType>{};
            Promise._Name = "PerformOuterRecursiveTaskThroughDelegate";

            if (Iterations > 1)
            {
                Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size> Task = PerformOuterRecursiveTaskThroughDelegate(--Iterations, ManagedExternally);
                co_await Task;

                co_return Task.GetResult() + 1;
            }
            else
            {
                Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size> Task = PerformMostInternalTaskThroughDelegate(ManagedExternally);
                co_await Task;

                co_return Task.GetResult();
            }
        }

        inline Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size> PerformOuterLoopedTaskThroughDelegate(
            Elysium::Core::Template::System::size Iterations, const bool ManagedExternally)
        {
            using AsyncPromiseType = Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size>::PromiseType;

            AsyncPromiseType& Promise = co_await Elysium::Core::Template::Coroutines::Awaiter::GetCurrentPromiseAwaiter<AsyncPromiseType>{};
            Promise._Name = "PerformOuterLoopedTaskThroughDelegate";

            Elysium::Core::Template::System::size Result{};

            for (Elysium::Core::Template::System::size i = 0; i < Iterations; ++i)
            {
                Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size> Task = PerformMostInternalTaskThroughDelegate(ManagedExternally);
                //OutputDebugStringA("PerformOuterLoopedTaskThroughDelegate(...) waiting on Task\r\n");
                co_await Task;
                //OutputDebugStringA("PerformOuterLoopedTaskThroughDelegate(...) awaited Task\r\n");

                Result += Task.GetResult();
            }

            co_return Result;
        }
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
        inline Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t> PerformMostInternalTask()
        {
            using AsyncPromiseType = Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t>::PromiseType;

            AsyncPromiseType& Promise = co_await Elysium::Core::Template::Coroutines::Awaiter::GetCurrentPromiseAwaiter<AsyncPromiseType>{};
            Promise._Name = "PerformMostInternalTask";

            co_return 1;
        }

        inline Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t> PerformOuterRecursiveTask(Elysium::Core::Template::System::uint8_t Iterations)
        {
            using AsyncPromiseType = Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t>::PromiseType;

            AsyncPromiseType& Promise = co_await Elysium::Core::Template::Coroutines::Awaiter::GetCurrentPromiseAwaiter<AsyncPromiseType>{};
            Promise._Name = "PerformOuterRecursiveTask";

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

        inline Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t> PerformOuterLoopedTask(Elysium::Core::Template::System::uint8_t Iterations)
        {
            using AsyncPromiseType = Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t>::PromiseType;

            AsyncPromiseType& Promise = co_await Elysium::Core::Template::Coroutines::Awaiter::GetCurrentPromiseAwaiter<AsyncPromiseType>{};
            Promise._Name = "PerformOuterLoopedTask";

            Elysium::Core::Template::System::uint8_t Result{};

            for (Elysium::Core::Template::System::uint8_t i = 0; i < Iterations; ++i)
            {
                Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t> Task = PerformMostInternalTask();
                co_await Task;

                Result += Task.GetResult();
            }

            co_return Result;
        }
    public:
        TEST_METHOD(SimpleFixedChainTest)
        {
            Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t> Task1 = D();
            Task1.Wait();
            Assert::AreEqual(4_ui8, Task1.GetResult());
        }
    private:
        inline Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t> A()
        {
            using AsyncPromiseType = Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t>::PromiseType;

            AsyncPromiseType& Promise = co_await Elysium::Core::Template::Coroutines::Awaiter::GetCurrentPromiseAwaiter<AsyncPromiseType>{};
            Promise._Name = "A";

            co_return 1;
        }

        inline Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t> B()
        {
            using AsyncPromiseType = Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t>::PromiseType;

            AsyncPromiseType& Promise = co_await Elysium::Core::Template::Coroutines::Awaiter::GetCurrentPromiseAwaiter<AsyncPromiseType>{};
            Promise._Name = "B";

            Elysium::Core::Template::System::uint8_t InnerResult = co_await A();

            Elysium::Core::Template::Threading::Thread::Sleep(700);

            co_return InnerResult + 1;
        }

        inline Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t> C()
        {
            using AsyncPromiseType = Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t>::PromiseType;

            AsyncPromiseType& Promise = co_await Elysium::Core::Template::Coroutines::Awaiter::GetCurrentPromiseAwaiter<AsyncPromiseType>{};
            Promise._Name = "C";

            Elysium::Core::Template::System::uint8_t InnerResult = co_await B();

            Elysium::Core::Template::Threading::Thread::Sleep(700);

            co_return InnerResult + 1;
        }

        inline Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t> D()
        {
            using AsyncPromiseType = Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::uint8_t>::PromiseType;

            AsyncPromiseType& Promise = co_await Elysium::Core::Template::Coroutines::Awaiter::GetCurrentPromiseAwaiter<AsyncPromiseType>{};
            Promise._Name = "D";

            Elysium::Core::Template::System::uint8_t InnerResult = co_await C();

            Elysium::Core::Template::Threading::Thread::Sleep(700);

            co_return InnerResult + 1;
        }
    };
}
