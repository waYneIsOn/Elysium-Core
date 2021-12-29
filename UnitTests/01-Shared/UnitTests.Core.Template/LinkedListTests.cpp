#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/String.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/LinkedList.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Template::Container;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Container
{
	TEST_CLASS(LinkedListTests)
	{
	public:
		TEST_METHOD(StringTest)
		{
			LinkedList<Elysium::Core::Utf8String> Instance = LinkedList<Elysium::Core::Utf8String>();
			for (LinkedList<Elysium::Core::Utf8String>::FIterator Iterator = Instance.GetBegin(); Iterator != Instance.GetEnd(); ++Iterator)
			{
				Assert::Fail();
			}

			Instance.PushBack(u8"0\r\n");
			Instance.PushBack(u8"1\r\n");
			Instance.PushBack(u8"2\r\n");

			LinkedListNode<Elysium::Core::Utf8String>* Head = Instance.GetHead();
			LinkedListNode<Elysium::Core::Utf8String>* Tail = Instance.GetTail();
			AssertExtended::AreEqual(u8"0\r\n", Head->GetItem());
			AssertExtended::AreEqual(u8"1\r\n", Head->GetNext()->GetItem());
			AssertExtended::AreEqual(u8"2\r\n", Head->GetNext()->GetNext()->GetItem());
			AssertExtended::AreEqual(u8"2\r\n", Tail->GetItem());
			Assert::IsNull(Tail->GetNext());

			Instance.PushFront(u8"-2\r\n");
			Head = Instance.GetHead();
			Tail = Instance.GetTail();
			AssertExtended::AreEqual(u8"-2\r\n", Head->GetItem());
			AssertExtended::AreEqual(u8"0\r\n", Head->GetNext()->GetItem());
			AssertExtended::AreEqual(u8"1\r\n", Head->GetNext()->GetNext()->GetItem());
			AssertExtended::AreEqual(u8"2\r\n", Head->GetNext()->GetNext()->GetNext()->GetItem());
			AssertExtended::AreEqual(u8"2\r\n", Tail->GetItem());
			Assert::IsNull(Tail->GetNext());

			Instance.PushAfter(u8"3\r\n", *Tail);
			Head = Instance.GetHead();
			Tail = Instance.GetTail();
			AssertExtended::AreEqual(u8"-2\r\n", Head->GetItem());
			AssertExtended::AreEqual(u8"0\r\n", Head->GetNext()->GetItem());
			AssertExtended::AreEqual(u8"1\r\n", Head->GetNext()->GetNext()->GetItem());
			AssertExtended::AreEqual(u8"2\r\n", Head->GetNext()->GetNext()->GetNext()->GetItem());
			AssertExtended::AreEqual(u8"3\r\n", Head->GetNext()->GetNext()->GetNext()->GetNext()->GetItem());
			AssertExtended::AreEqual(u8"3\r\n", Tail->GetItem());
			Assert::IsNull(Tail->GetNext());

			Instance.PushAfter(u8"-1\r\n", *Head);
			Head = Instance.GetHead();
			Tail = Instance.GetTail();
			AssertExtended::AreEqual(u8"-2\r\n", Head->GetItem());
			AssertExtended::AreEqual(u8"-1\r\n", Head->GetNext()->GetItem());
			AssertExtended::AreEqual(u8"0\r\n", Head->GetNext()->GetNext()->GetItem());
			AssertExtended::AreEqual(u8"1\r\n", Head->GetNext()->GetNext()->GetNext()->GetItem());
			AssertExtended::AreEqual(u8"2\r\n", Head->GetNext()->GetNext()->GetNext()->GetNext()->GetItem());
			AssertExtended::AreEqual(u8"3\r\n", Head->GetNext()->GetNext()->GetNext()->GetNext()->GetNext()->GetItem());
			AssertExtended::AreEqual(u8"3\r\n", Tail->GetItem());
			Assert::IsNull(Tail->GetNext());

			Instance.RemoveHead();
			Head = Instance.GetHead();
			Tail = Instance.GetTail();
			AssertExtended::AreEqual(u8"-1\r\n", Head->GetItem());
			AssertExtended::AreEqual(u8"0\r\n", Head->GetNext()->GetItem());
			AssertExtended::AreEqual(u8"1\r\n", Head->GetNext()->GetNext()->GetItem());
			AssertExtended::AreEqual(u8"2\r\n", Head->GetNext()->GetNext()->GetNext()->GetItem());
			AssertExtended::AreEqual(u8"3\r\n", Head->GetNext()->GetNext()->GetNext()->GetNext()->GetItem());
			AssertExtended::AreEqual(u8"3\r\n", Tail->GetItem());
			Assert::IsNull(Tail->GetNext());

			Assert::IsTrue(Instance.Contains(u8"0\r\n"));
			Assert::IsFalse(Instance.Contains(u8"4\r\n"));

			const LinkedList<Elysium::Core::Utf8String>& ConstInstance = Instance;
			for (LinkedList<Elysium::Core::Utf8String>::ConstIterator Iterator = ConstInstance.GetBegin(); Iterator != ConstInstance.GetEnd(); ++Iterator)
			{
				const LinkedListNode<Elysium::Core::Utf8String>& Node = *Iterator;
				Logger::WriteMessage((char*)&Node.GetItem()[0]);
			}
			Logger::WriteMessage("\r\n");
			
			Instance.Clear();
			for (LinkedList<Elysium::Core::Utf8String>::FIterator Iterator = Instance.GetBegin(); Iterator != Instance.GetEnd(); ++Iterator)
			{
				Assert::Fail();
			}
		}
	};
}