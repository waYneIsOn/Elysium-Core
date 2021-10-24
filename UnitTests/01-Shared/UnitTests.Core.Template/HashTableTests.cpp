#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/String.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/HashTable.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Template::Container;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Container
{
	TEST_CLASS(HashTableTests)
	{
	public:
		TEST_METHOD(PointerPointer)
		{
			Assert::Fail();
		}

		TEST_METHOD(PointerValue)
		{
			Assert::Fail();
		}

		TEST_METHOD(ValuePointer)
		{
			Assert::Fail();
		}
		
		TEST_METHOD(ValueValue)
		{
			HashTable<String, String> Instance = HashTable<String, String>();
			Instance.Add(u8"rtf", u8"wordpad.exe");
			Instance.Add(u8"bmp", u8"paint.exe");
			Instance.Add(u8"dib", u8"paint.exe");
			
			// add another key/value to cause collision and an ArgumentException
			try
			{
				Instance.Add(u8"txt", u8"notepad.exe");
				Assert::Fail();
			}
			catch(ArgumentException&)
			{ }

			// perform the same operation but add the item through operator NOT causing an ArgumentException (while still causing a collision)
			//Instance[u8"txt"] = u8"notepad.exe";
			/*
			for (HashTable<String, String>::FIterator Iterator = Instance.GetBegin(); Iterator != Instance.GetEnd(); ++Iterator)
			{
				LinkedList<HashTableEntry<String, String>>& Bucket = *Iterator;
				LinkedListNode<HashTableEntry<String, String>>* Node = Bucket.GetHead();

				if (Node == nullptr)
				{
					Logger::WriteMessage(". - .\r\n");
				}
				else
				{
					HashTableEntry<String, String>& Item = Node->GetItem();
					Logger::WriteMessage((char*)&Item.Key[0]);
					Logger::WriteMessage(" - ");
					Logger::WriteMessage((char*)&Item.Value[0]);
					Logger::WriteMessage("\r\n");

					LinkedListNode<HashTableEntry<String, String>>* NextNode = Node->GetNext();
					if (NextNode != nullptr)
					{
						HashTableEntry<String, String>& NextItem = NextNode->GetItem();
						Logger::WriteMessage((char*)&NextItem.Key[0]);
						Logger::WriteMessage(" - ");
						Logger::WriteMessage((char*)&NextItem.Value[0]);
						Logger::WriteMessage("\r\n");
					}
				}
			}
			*/
		}
	};
}
