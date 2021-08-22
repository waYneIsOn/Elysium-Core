#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/LinkedList.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Elysium::Core;
using namespace Elysium::Core::Collections::Template;

namespace UnitTests::Core::Collections::Template
{
	TEST_CLASS(LinkedListTest)
	{
	public:
		TEST_METHOD(Pointer)
		{
			const Elysium::Core::uint8_t Size = 5;

			LinkedList<Elysium::Core::uint8_t*> PointerLinkedList = LinkedList<Elysium::Core::uint8_t*>();
			Assert::AreEqual(0_ui64, PointerLinkedList.GetCount());
			Assert::IsNull(PointerLinkedList.GetFirst());
			Assert::IsNull(PointerLinkedList.GetLast());

			Elysium::Core::uint8_t Values[Size];
			for (Elysium::Core::uint8_t i = 0; i < Size; i++)
			{
				Values[i] = i;
				PointerLinkedList.AddLast(&Values[i]);
			}
			Assert::AreEqual(static_cast<Elysium::Core::uint64_t>(Size), PointerLinkedList.GetCount());

			Assert::AreEqual(0_ui8, *PointerLinkedList.GetFirst()->GetValue());
			Assert::AreEqual(4_ui8, *PointerLinkedList.GetLast()->GetValue());
			
			PointerLinkedList.RemoveFirst();
			Assert::AreEqual(static_cast<Elysium::Core::uint64_t>(Size - 1), PointerLinkedList.GetCount());
			Assert::AreEqual(1_ui8, *PointerLinkedList.GetFirst()->GetValue());
			Assert::AreEqual(*PointerLinkedList.FindLast()->GetValue(), *PointerLinkedList.GetLast()->GetValue());
			
			PointerLinkedList.Clear();
			Assert::AreEqual(0_ui64, PointerLinkedList.GetCount());
		}

		TEST_METHOD(FundamentalValue)
		{
			const Elysium::Core::uint8_t Size = 5;

			LinkedList<Elysium::Core::uint8_t> ValueLinkedList = LinkedList<Elysium::Core::uint8_t>();
			Assert::AreEqual(0_ui64, ValueLinkedList.GetCount());
			Assert::IsNull(ValueLinkedList.GetFirst());
			Assert::IsNull(ValueLinkedList.GetLast());

			for (Elysium::Core::uint8_t i = 0; i < Size; i++)
			{
				ValueLinkedList.AddLast(i);
			}
			Assert::AreEqual(static_cast<Elysium::Core::uint64_t>(Size), ValueLinkedList.GetCount());

			Assert::AreEqual(0_ui8, ValueLinkedList.GetFirst()->GetValue());
			Assert::AreEqual(4_ui8, ValueLinkedList.GetLast()->GetValue());
			
			ValueLinkedList.RemoveFirst();
			Assert::AreEqual(static_cast<Elysium::Core::uint64_t>(Size - 1), ValueLinkedList.GetCount());
			Assert::AreEqual(1_ui8, ValueLinkedList.GetFirst()->GetValue());
			Assert::AreEqual(ValueLinkedList.FindLast()->GetValue(), ValueLinkedList.GetLast()->GetValue());
			
			ValueLinkedList.Clear();
			Assert::AreEqual(0_ui64, ValueLinkedList.GetCount());
		}

		TEST_METHOD(Value)
		{
			Assert::Fail();
		}
	};
}
