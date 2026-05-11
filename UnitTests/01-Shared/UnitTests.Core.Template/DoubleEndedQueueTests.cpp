#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.Template/Container/DoubleEndedQueue.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/System/Literals.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/System/Primitives.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Template::Container;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Container
{
	TEST_CLASS(DoubleEndedQueueTests)
	{
	public:
		TEST_METHOD(SimpleTest)
		{
			DoubleEndedQueue<Elysium::Core::Template::System::uint8_t> InitializerListQueue = { 1_ui8, 2_ui8, 3_ui8 };
			Assert::IsFalse(InitializerListQueue.GetIsEmpty());
			Assert::AreEqual(3_ui64, InitializerListQueue.GetLength());
			const Elysium::Core::Template::System::uint8_t& Firstsdf = InitializerListQueue.GetFront();

			DoubleEndedQueue<Elysium::Core::Template::System::uint8_t> Queue = DoubleEndedQueue<Elysium::Core::Template::System::uint8_t>();
			Assert::IsFalse(Queue.GetIsEmpty());
			Assert::AreEqual(1_ui64, Queue.GetLength());

			Queue.PopFront();
			Assert::IsTrue(Queue.GetIsEmpty());
			Assert::AreEqual(0_ui64, Queue.GetLength());

			Queue.PushBack(3_ui8);
			Queue.PushBack(2_ui8);
			Queue.PushBack(1_ui8);
			Assert::IsFalse(Queue.GetIsEmpty());
			Assert::AreEqual(3_ui64, Queue.GetLength());

			const Elysium::Core::Template::System::uint8_t& First = Queue.GetFront();
			Assert::AreEqual(3_ui8, First);
			Queue.PopFront();
			Assert::IsFalse(Queue.GetIsEmpty());
			Assert::AreEqual(2_ui64, Queue.GetLength());

			const Elysium::Core::Template::System::uint8_t& Second = Queue.GetFront();
			Assert::AreEqual(2_ui8, First);
			Queue.PopFront();
			Assert::IsFalse(Queue.GetIsEmpty());
			Assert::AreEqual(1_ui64, Queue.GetLength());

			const Elysium::Core::Template::System::uint8_t& Third = Queue.GetFront();
			Assert::AreEqual(1_ui8, First);
			Queue.PopFront();
			Assert::IsTrue(Queue.GetIsEmpty());
			Assert::AreEqual(0_ui64, Queue.GetLength());

			try
			{
				Elysium::Core::Template::System::uint8_t& CurrentElement = Queue.GetFront();
				Assert::Fail();
			}
			catch (...)
			{ }
		}
	};
}