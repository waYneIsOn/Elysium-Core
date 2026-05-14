#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

//#include "../../../Libraries/01-Shared/Elysium.Core.Template/Container/Adopter/PriorityQueue.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Container/PriorityQueue.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/System/Literals.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/System/Primitives.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Template::Container;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Container::Adopter
{
	TEST_CLASS(PriorityQueueTests)
	{
	public:
		TEST_METHOD(SimpleTest)
		{
			PriorityQueue<Elysium::Core::Template::System::uint8_t> InitializerListQueue = { 3_ui8, 1_ui8, 2_ui8 };
			Assert::IsFalse(InitializerListQueue.GetIsEmpty());
			Assert::AreEqual(3_ui64, InitializerListQueue.GetLength());
			const Elysium::Core::Template::System::uint8_t& ILQueueTop = InitializerListQueue.GetTop();
			Assert::AreEqual(1_ui8, ILQueueTop);

			PriorityQueue<Elysium::Core::Template::System::uint8_t> Queue = PriorityQueue<Elysium::Core::Template::System::uint8_t>();
			Assert::IsTrue(Queue.GetIsEmpty());
			Assert::AreEqual(0_ui64, Queue.GetLength());

			Queue.Pop();
			Assert::IsTrue(Queue.GetIsEmpty());
			Assert::AreEqual(0_ui64, Queue.GetLength());

			Queue.Push(3_ui8);
			Queue.Push(2_ui8);
			Queue.Push(1_ui8);
			Assert::IsFalse(Queue.GetIsEmpty());
			Assert::AreEqual(3_ui64, Queue.GetLength());

			const Elysium::Core::Template::System::uint8_t& First = Queue.GetTop();
			Assert::AreEqual(1_ui8, First);
			Queue.Pop();
			Assert::IsFalse(Queue.GetIsEmpty());
			Assert::AreEqual(2_ui64, Queue.GetLength());

			const Elysium::Core::Template::System::uint8_t& Second = Queue.GetTop();
			Assert::AreEqual(2_ui8, First);
			Queue.Pop();
			Assert::IsFalse(Queue.GetIsEmpty());
			Assert::AreEqual(1_ui64, Queue.GetLength());

			const Elysium::Core::Template::System::uint8_t& Third = Queue.GetTop();
			Assert::AreEqual(3_ui8, First);
			Queue.Pop();
			Assert::IsTrue(Queue.GetIsEmpty());
			Assert::AreEqual(0_ui64, Queue.GetLength());

			try
			{
				Elysium::Core::Template::System::uint8_t& CurrentElement = Queue.GetTop();
				Assert::Fail();
			}
			catch (...)
			{ }
		}
	};
}
