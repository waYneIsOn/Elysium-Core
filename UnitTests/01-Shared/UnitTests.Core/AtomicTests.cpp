#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Vector.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Convert.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Threading/Atomic.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Threading/Thread.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Threading
{
	TEST_CLASS(AtomicTests)
	{
	public:
		TEST_METHOD(IncrementCountersInParallel)
		{
			{
				const Elysium::Core::uint8_t NumberOfThreads = 10;

				Elysium::Core::Template::Container::Delegate<void> ThreadStart =
					Elysium::Core::Template::Container::Delegate<void>::Bind<AtomicTests, &AtomicTests::Increment>(*this);

				Elysium::Core::Template::Container::Vector<Elysium::Core::Threading::Thread> Threads =
					Elysium::Core::Template::Container::Vector<Elysium::Core::Threading::Thread>(NumberOfThreads);
				Threads.Clear();
				for (Elysium::Core::size i = 0; i < NumberOfThreads; i++)
				{
					Threads.PushBack(Elysium::Core::Threading::Thread(ThreadStart));
				}

				for (Elysium::Core::size i = 0; i < NumberOfThreads; i++)
				{
					Threads[i].Start();
				}
			}

			Logger::WriteMessage("Counter: ");
			Logger::WriteMessage(&Elysium::Core::Template::Text::Convert<char>::ToString(_Counter)[0]);
			Logger::WriteMessage("\r\nAtomic counter: ");
			//Logger::WriteMessage(&Elysium::Core::Template::Text::Convert<char>::ToString(_AtomicCounter)[0]);
		}
	private:
		void Increment()
		{
			for (Elysium::Core::Template::System::uint16_t i = 0; i < 10000; i++)
			{
				_Counter++;
				//_AtomicCounter++;
			}
		}
	private:
		Elysium::Core::Template::System::uint32_t _Counter;
		Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::uint32_t> _AtomicCounter;
	};
}
