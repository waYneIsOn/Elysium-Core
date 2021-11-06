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
			String Wordpad = u8"wordpad.exe";
			String Paint = u8"paint.exe";
			String Notepad = u8"notepad.exe";
			String Notepadpp = u8"notepad++.exe";

			HashTable<String, String*> Instance =
			{
				{ u8"rtf", &Wordpad },
				{ u8"bmp", &Paint },
				{ u8"dib", &Paint },
			};

			Elysium::Core::size i = 0;
			for (HashTable<String, String*>::FIterator Iterator = Instance.GetBegin(); Iterator != Instance.GetEnd(); ++Iterator)
			{
				LinkedListNode<KeyValuePair<String, String*>>* Node = *Iterator;
				KeyValuePair<String, String*>& Item = Node->GetItem();
				Logger::WriteMessage((char*)&Item.GetKey()[0]);
				Logger::WriteMessage(" - ");
				Logger::WriteMessage((char*)&Item.GetValue()->operator[](0));
				Logger::WriteMessage("\r\n");
				i++;
			}
			Assert::AreEqual(static_cast<Elysium::Core::size>(3), i);
			Logger::WriteMessage("\r\n");

			// ...
			Instance.Set(u8"txt", &Notepad);
			i = 0;
			for (HashTable<String, String*>::FIterator Iterator = Instance.GetBegin(); Iterator != Instance.GetEnd(); ++Iterator)
			{
				LinkedListNode<KeyValuePair<String, String*>>* Node = *Iterator;
				KeyValuePair<String, String*>& Item = Node->GetItem();
				Logger::WriteMessage((char*)&Item.GetKey()[0]);
				Logger::WriteMessage(" - ");
				Logger::WriteMessage((char*)&Item.GetValue()->operator[](0));
				Logger::WriteMessage("\r\n");
				i++;
			}
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), i);
			Logger::WriteMessage("\r\n");

			// ...
			Instance.Set(u8"txt", &Notepadpp);
			i = 0;
			for (HashTable<String, String*>::FIterator Iterator = Instance.GetBegin(); Iterator != Instance.GetEnd(); ++Iterator)
			{
				LinkedListNode<KeyValuePair<String, String*>>* Node = *Iterator;
				KeyValuePair<String, String*>& Item = Node->GetItem();
				Logger::WriteMessage((char*)&Item.GetKey()[0]);
				Logger::WriteMessage(" - ");
				Logger::WriteMessage((char*)&Item.GetValue()->operator[](0));
				Logger::WriteMessage("\r\n");
				i++;
			}
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), i);
		}
		
		TEST_METHOD(ValueValue)
		{
			HashTable<String, String> Instance = HashTable<String, String>();
			Instance.Add(u8"rtf", u8"wordpad.exe");
			Instance.Add(u8"bmp", u8"paint.exe");
			Instance.Add(u8"dib", u8"paint.exe");

			Elysium::Core::size i = 0;
			for (HashTable<String, String>::FIterator Iterator = Instance.GetBegin(); Iterator != Instance.GetEnd(); ++Iterator)
			{
				LinkedListNode<KeyValuePair<String, String>>* Node = *Iterator;
				KeyValuePair<String, String>& Item = Node->GetItem();
				Logger::WriteMessage((char*)&Item.GetKey()[0]);
				Logger::WriteMessage(" - ");
				Logger::WriteMessage((char*)&Item.GetValue()[0]);
				Logger::WriteMessage("\r\n");
				i++;
			}
			Assert::AreEqual(static_cast<Elysium::Core::size>(3), i);
			Logger::WriteMessage("\r\n");
			
			// add another key/value to cause collision and an ArgumentException
			try
			{
				Instance.Add(u8"txt", u8"notepad.exe");
				Assert::Fail();
			}
			catch(ArgumentException&)
			{ }

			// perform the same operation but add the item through Set(...) NOT causing an ArgumentException (while still causing a collision)
			Instance.Set(u8"txt", u8"notepad.exe");

			i = 0;
			for (HashTable<String, String>::FIterator Iterator = Instance.GetBegin(); Iterator != Instance.GetEnd(); ++Iterator)
			{
				LinkedListNode<KeyValuePair<String, String>>* Node = *Iterator;
				KeyValuePair<String, String>& Item = Node->GetItem();
				Logger::WriteMessage((char*)&Item.GetKey()[0]);
				Logger::WriteMessage(" - ");
				Logger::WriteMessage((char*)&Item.GetValue()[0]);
				Logger::WriteMessage("\r\n");
				i++;
			}
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), i);
			Logger::WriteMessage("\r\n");
			
			// update/change a value associated with an already inserted key
			Instance.Set(u8"txt", u8"notepad++.exe");

			i = 0;
			for (HashTable<String, String>::FIterator Iterator = Instance.GetBegin(); Iterator != Instance.GetEnd(); ++Iterator)
			{
				LinkedListNode<KeyValuePair<String, String>>* Node = *Iterator;
				KeyValuePair<String, String>& Item = Node->GetItem();
				Logger::WriteMessage((char*)&Item.GetKey()[0]);
				Logger::WriteMessage(" - ");
				Logger::WriteMessage((char*)&Item.GetValue()[0]);
				Logger::WriteMessage("\r\n");
				i++;
			}
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), i);
		}
	};
}