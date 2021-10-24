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
			LinkedList<String> Instance = LinkedList<String>();
			for (LinkedList<String>::FIterator Iterator = Instance.GetBegin(); Iterator != Instance.GetEnd(); ++Iterator)
			{
				Logger::WriteMessage((char*)&(*Iterator).GetItem()[0]);
				Logger::WriteMessage("\r\n");
			}

			Instance.PushBack(u8"0");
			Instance.PushBack(u8"1");
			Instance.PushBack(u8"2");

			LinkedListNode<String>* Head = Instance.GetHead();
			LinkedListNode<String>* Tail = Instance.GetTail();
			AssertExtended::AreEqual(u8"0", Head->GetItem());
			AssertExtended::AreEqual(u8"1", Head->GetNext()->GetItem());
			AssertExtended::AreEqual(u8"2", Head->GetNext()->GetNext()->GetItem());
			AssertExtended::AreEqual(u8"2", Tail->GetItem());

			Instance.PushFront(u8"-2");
			Head = Instance.GetHead();
			Tail = Instance.GetTail();
			AssertExtended::AreEqual(u8"-2", Head->GetItem());
			AssertExtended::AreEqual(u8"0", Head->GetNext()->GetItem());
			AssertExtended::AreEqual(u8"1", Head->GetNext()->GetNext()->GetItem());
			AssertExtended::AreEqual(u8"2", Head->GetNext()->GetNext()->GetNext()->GetItem());
			AssertExtended::AreEqual(u8"2", Tail->GetItem());

			Instance.PushAfter(u8"3", *Tail);
			Head = Instance.GetHead();
			Tail = Instance.GetTail();
			AssertExtended::AreEqual(u8"-2", Head->GetItem());
			AssertExtended::AreEqual(u8"0", Head->GetNext()->GetItem());
			AssertExtended::AreEqual(u8"1", Head->GetNext()->GetNext()->GetItem());
			AssertExtended::AreEqual(u8"2", Head->GetNext()->GetNext()->GetNext()->GetItem());
			AssertExtended::AreEqual(u8"3", Head->GetNext()->GetNext()->GetNext()->GetNext()->GetItem());
			AssertExtended::AreEqual(u8"3", Tail->GetItem());

			Instance.PushAfter(u8"-1", *Head);
			Head = Instance.GetHead();
			Tail = Instance.GetTail();
			AssertExtended::AreEqual(u8"-2", Head->GetItem());
			AssertExtended::AreEqual(u8"-1", Head->GetNext()->GetItem());
			AssertExtended::AreEqual(u8"0", Head->GetNext()->GetNext()->GetItem());
			AssertExtended::AreEqual(u8"1", Head->GetNext()->GetNext()->GetNext()->GetItem());
			AssertExtended::AreEqual(u8"2", Head->GetNext()->GetNext()->GetNext()->GetNext()->GetItem());
			AssertExtended::AreEqual(u8"3", Head->GetNext()->GetNext()->GetNext()->GetNext()->GetNext()->GetItem());
			AssertExtended::AreEqual(u8"3", Tail->GetItem());
			
			for (LinkedList<String>::FIterator Iterator = Instance.GetBegin(); Iterator != Instance.GetEnd(); ++Iterator)
			{
				Logger::WriteMessage((char*)&(*Iterator).GetItem()[0]);
				Logger::WriteMessage("\r\n");
			}
		}
	};
}