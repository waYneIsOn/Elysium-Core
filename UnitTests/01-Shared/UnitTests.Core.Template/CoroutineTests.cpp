#include "CppUnitTest.h"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Coroutines/Awaiter/SuspendAlways.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Coroutines/Awaiter/SuspendNever.hpp"


#include <coroutine>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Coroutines
{
    struct AsyncTestClass
    {
    public:
        // nomenclatura is important here!
        struct promise_type
        {
            AsyncTestClass get_return_object()
            {
                return {};
            }

            Elysium::Core::Template::Coroutines::Awaiter::SuspendNever initial_suspend()
            {
                return {};
            }

            Elysium::Core::Template::Coroutines::Awaiter::SuspendNever final_suspend() noexcept
            {
                return {};
            }

            void return_void()
            { }

            void unhandled_exception()
            { }
        };
    public:
        inline static AsyncTestClass DoSomething()
        {
            Logger::WriteMessage("Before\r\n");
            co_await Elysium::Core::Template::Coroutines::Awaiter::SuspendAlways{};
            Logger::WriteMessage("After\r\n");
        }
    };
    
	TEST_CLASS(CoroutineTests)
	{
	public:
		TEST_METHOD(SimplestExample)
		{
            AsyncTestClass Result = AsyncTestClass::DoSomething();
		}
	};
}
