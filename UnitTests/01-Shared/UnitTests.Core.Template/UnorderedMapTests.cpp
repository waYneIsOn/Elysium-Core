#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/String.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/UnorderedMap.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Template::Container;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Container
{
	TEST_CLASS(UnorderedMapTests)
	{
	public:
		TEST_METHOD(PointerPointer)
		{
			Elysium::Core::Utf8String Rtf = u8"rtf";
			Elysium::Core::Utf8String Bmp = u8"bmp";
			Elysium::Core::Utf8String Dib = u8"dib";

			Elysium::Core::Utf8String Wordpad = u8"wordpad.exe";
			Elysium::Core::Utf8String Paint = u8"paint.exe";

			UnorderedMap<Elysium::Core::Utf8String*, Elysium::Core::Utf8String*> Instance =
			{
				{ &Rtf, &Wordpad },
				{ &Bmp, &Paint },
				{ &Dib, &Paint },
			};
			
			Elysium::Core::size i = 0;
			for (UnorderedMap<Elysium::Core::Utf8String*, Elysium::Core::Utf8String*>::FIterator Iterator = Instance.GetBegin(); Iterator != Instance.GetEnd(); ++Iterator)
			{
				LinkedListNode<KeyValuePair<Elysium::Core::Utf8String*, Elysium::Core::Utf8String*>>* Node = *Iterator;
				KeyValuePair<Elysium::Core::Utf8String*, Elysium::Core::Utf8String*>& Item = Node->GetItem();
				Logger::WriteMessage((char*)&Item.GetKey()->operator[](0));
				Logger::WriteMessage(" - ");
				Logger::WriteMessage((char*)&Item.GetValue()->operator[](0));
				Logger::WriteMessage("\r\n");
				i++;
			}
			Assert::AreEqual(static_cast<Elysium::Core::size>(3), i);
			Logger::WriteMessage("\r\n");
		}

		TEST_METHOD(PointerValue)
		{
			Elysium::Core::Utf8String Rtf = u8"rtf";
			Elysium::Core::Utf8String Bmp = u8"bmp";
			Elysium::Core::Utf8String Dib = u8"dib";

			UnorderedMap<Elysium::Core::Utf8String*, Elysium::Core::Utf8String> Instance =
			{
				{ &Rtf, u8"wordpad.exe" },
				{ &Bmp, u8"paint.exe" },
				{ &Dib, u8"paint.exe" },
			};

			Elysium::Core::size i = 0;
			for (UnorderedMap<Elysium::Core::Utf8String*, Elysium::Core::Utf8String>::FIterator Iterator = Instance.GetBegin(); Iterator != Instance.GetEnd(); ++Iterator)
			{
				LinkedListNode<KeyValuePair<Elysium::Core::Utf8String*, Elysium::Core::Utf8String>>* Node = *Iterator;
				KeyValuePair<Elysium::Core::Utf8String*, Elysium::Core::Utf8String>& Item = Node->GetItem();
				Logger::WriteMessage((char*)&Item.GetKey()->operator[](0));
				Logger::WriteMessage(" - ");
				Logger::WriteMessage((char*)&Item.GetValue()[0]);
				Logger::WriteMessage("\r\n");
				i++;
			}
			Assert::AreEqual(static_cast<Elysium::Core::size>(3), i);
			Logger::WriteMessage("\r\n");
		}

		TEST_METHOD(ValuePointer)
		{
			Elysium::Core::Utf8String Wordpad = u8"wordpad.exe";
			Elysium::Core::Utf8String Paint = u8"paint.exe";
			Elysium::Core::Utf8String Notepad = u8"notepad.exe";
			Elysium::Core::Utf8String Notepadpp = u8"notepad++.exe";

			UnorderedMap<Elysium::Core::Utf8String, Elysium::Core::Utf8String*> Instance =
			{
				{ u8"rtf", &Wordpad },
				{ u8"bmp", &Paint },
				{ u8"dib", &Paint },
			};

			Elysium::Core::size i = 0;
			for (UnorderedMap<Elysium::Core::Utf8String, Elysium::Core::Utf8String*>::FIterator Iterator = Instance.GetBegin(); Iterator != Instance.GetEnd(); ++Iterator)
			{
				LinkedListNode<KeyValuePair<Elysium::Core::Utf8String, Elysium::Core::Utf8String*>>* Node = *Iterator;
				KeyValuePair<Elysium::Core::Utf8String, Elysium::Core::Utf8String*>& Item = Node->GetItem();
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
			for (UnorderedMap<Elysium::Core::Utf8String, Elysium::Core::Utf8String*>::FIterator Iterator = Instance.GetBegin(); Iterator != Instance.GetEnd(); ++Iterator)
			{
				LinkedListNode<KeyValuePair<Elysium::Core::Utf8String, Elysium::Core::Utf8String*>>* Node = *Iterator;
				KeyValuePair<Elysium::Core::Utf8String, Elysium::Core::Utf8String*>& Item = Node->GetItem();
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
			for (UnorderedMap<Elysium::Core::Utf8String, Elysium::Core::Utf8String*>::FIterator Iterator = Instance.GetBegin(); Iterator != Instance.GetEnd(); ++Iterator)
			{
				LinkedListNode<KeyValuePair<Elysium::Core::Utf8String, Elysium::Core::Utf8String*>>* Node = *Iterator;
				KeyValuePair<Elysium::Core::Utf8String, Elysium::Core::Utf8String*>& Item = Node->GetItem();
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
			Elysium::Core::size i = 0;
			UnorderedMap<Elysium::Core::Utf8String, Elysium::Core::Utf8String> Instance = UnorderedMap<Elysium::Core::Utf8String, Elysium::Core::Utf8String>();
			
			const UnorderedMap<Elysium::Core::Utf8String, Elysium::Core::Utf8String>& ConstInstance = Instance;
			for (UnorderedMap<Elysium::Core::Utf8String, Elysium::Core::Utf8String>::FIterator Iterator = Instance.GetBegin(); Iterator != Instance.GetEnd(); ++Iterator)
			{
				Assert::Fail();
			}
			Instance.Add(u8"rtf", u8"wordpad.exe");
			Instance.Add(u8"bmp", u8"paint.exe");
			Instance.Add(u8"dib", u8"paint.exe");

			for (UnorderedMap<Elysium::Core::Utf8String, Elysium::Core::Utf8String>::FIterator Iterator = Instance.GetBegin(); Iterator != Instance.GetEnd(); ++Iterator)
			{
				LinkedListNode<KeyValuePair<Elysium::Core::Utf8String, Elysium::Core::Utf8String>>* Node = *Iterator;
				KeyValuePair<Elysium::Core::Utf8String, Elysium::Core::Utf8String>& Item = Node->GetItem();
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
			for (UnorderedMap<Elysium::Core::Utf8String, Elysium::Core::Utf8String>::FIterator Iterator = Instance.GetBegin(); Iterator != Instance.GetEnd(); ++Iterator)
			{
				LinkedListNode<KeyValuePair<Elysium::Core::Utf8String, Elysium::Core::Utf8String>>* Node = *Iterator;
				KeyValuePair<Elysium::Core::Utf8String, Elysium::Core::Utf8String>& Item = Node->GetItem();
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
			for (UnorderedMap<Elysium::Core::Utf8String, Elysium::Core::Utf8String>::FIterator Iterator = Instance.GetBegin(); Iterator != Instance.GetEnd(); ++Iterator)
			{
				LinkedListNode<KeyValuePair<Elysium::Core::Utf8String, Elysium::Core::Utf8String>>* Node = *Iterator;
				KeyValuePair<Elysium::Core::Utf8String, Elysium::Core::Utf8String>& Item = Node->GetItem();
				Logger::WriteMessage((char*)&Item.GetKey()[0]);
				Logger::WriteMessage(" - ");
				Logger::WriteMessage((char*)&Item.GetValue()[0]);
				Logger::WriteMessage("\r\n");
				i++;
			}
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), i);
			Logger::WriteMessage("\r\n");

			// ...
			Instance.Clear();
			i = 0;
			for (UnorderedMap<Elysium::Core::Utf8String, Elysium::Core::Utf8String>::FIterator Iterator = Instance.GetBegin(); Iterator != Instance.GetEnd(); ++Iterator)
			{
				Assert::Fail();
			}
			Assert::AreEqual(static_cast<Elysium::Core::size>(0), i);
			
			Instance.Add(u8"123", u8"123.exe");
			Instance.Add(u8"456", u8"456.exe");
			Instance.Set(u8"789", u8"789.exe");
			i = 0;
			for (UnorderedMap<Elysium::Core::Utf8String, Elysium::Core::Utf8String>::FIterator Iterator = Instance.GetBegin(); Iterator != Instance.GetEnd(); ++Iterator)
			{
				LinkedListNode<KeyValuePair<Elysium::Core::Utf8String, Elysium::Core::Utf8String>>* Node = *Iterator;
				KeyValuePair<Elysium::Core::Utf8String, Elysium::Core::Utf8String>& Item = Node->GetItem();
				Logger::WriteMessage((char*)&Item.GetKey()[0]);
				Logger::WriteMessage(" - ");
				Logger::WriteMessage((char*)&Item.GetValue()[0]);
				Logger::WriteMessage("\r\n");
				i++;
			}
			Assert::AreEqual(static_cast<Elysium::Core::size>(3), i);
			Logger::WriteMessage("\r\n");

			// ...
			Elysium::Core::Utf8String& AssociatedValue = Instance[u8"123"];
			AssertExtended::AreEqual(u8"123.exe", AssociatedValue);

			//const String& ConstAssociatedValue = ConstInstance[u8"456"];
			//AssertExtended::AreEqual(u8"456.exe", ConstAssociatedValue);

			// ...
			//Instance.Set(u8"025", u8"025.exe");
			//Instance.Remove(u8"789");
		}
	};
}
