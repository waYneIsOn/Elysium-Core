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
				Elysium::Core::Template::Container::Delegate<void> ThreadStart =
					Elysium::Core::Template::Container::Delegate<void>::Bind<AtomicTests, &AtomicTests::Increment>(*this);

				Elysium::Core::Template::Container::Vector<Elysium::Core::Threading::Thread> Threads =
					Elysium::Core::Template::Container::Vector<Elysium::Core::Threading::Thread>(_NumberOfThreads);
				Threads.Clear();
				for (Elysium::Core::size i = 0; i < _NumberOfThreads; i++)
				{
					Threads.PushBack(Elysium::Core::Threading::Thread(ThreadStart));
				}

				for (Elysium::Core::size i = 0; i < _NumberOfThreads; i++)
				{
					Threads[i].Start();
				}
			}

			Logger::WriteMessage("Counter: ");
			Logger::WriteMessage(&Elysium::Core::Template::Text::Convert<char>::ToString(_Counter)[0]);
			Logger::WriteMessage("\r\nAtomic counter: ");
			Logger::WriteMessage(&Elysium::Core::Template::Text::Convert<char>::ToString(_AtomicCounter)[0]);

			Assert::IsTrue(_Counter < _NumberOfThreads * _NumberOfIncrements);
			Assert::IsTrue(_AtomicCounter == _NumberOfThreads* _NumberOfIncrements);
		}
	private:
		void Increment()
		{
			for (Elysium::Core::Template::System::size i = 0; i < _NumberOfIncrements; i++)
			{
				_Counter++;

				//_AtomicCounter++;	// @ToDo: why isn't this available? inheritance?
				_AtomicCounter.operator++();
			}
		}
	private:
		const Elysium::Core::uint32_t _NumberOfThreads = 10;
		const Elysium::Core::uint32_t _NumberOfIncrements = 100000;

		Elysium::Core::Template::System::uint32_t _Counter;
		Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::uint32_t> _AtomicCounter;
		Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::byte*> _AtomicPointer;
	};
}
