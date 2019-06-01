#include "CppUnitTest.h"

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#include "CppUnitTestFrameworkExtension.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../../../Libraries/01-Shared/Elysium.Core/String.hpp"
#endif

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsCore
{
	TEST_CLASS(Core_String)
	{
	public:
		TEST_METHOD(Constructors)
		{
			Elysium::Core::String String1 = Elysium::Core::String(L"text");
			Assert::AreEqual(L"text", String1.GetCharArray());
			Assert::AreEqual((size_t)4, String1.GetLength());
			Assert::AreEqual(L't', String1[0]);
			Assert::AreEqual(L'e', String1[1]);
			Assert::AreEqual(L'x', String1[2]);
			Assert::AreEqual(L't', String1[3]);

			Elysium::Core::String String2 = L"different";
			Assert::AreEqual(L"different", String2.GetCharArray());
			Assert::AreEqual((size_t)9, String2.GetLength());
			Assert::AreEqual(L'd', String2[0]);
			Assert::AreEqual(L'i', String2[1]);
			Assert::AreEqual(L'f', String2[2]);
			Assert::AreEqual(L'f', String2[3]);
			Assert::AreEqual(L'e', String2[4]);
			Assert::AreEqual(L'r', String2[5]);
			Assert::AreEqual(L'e', String2[6]);
			Assert::AreEqual(L'n', String2[7]);
			Assert::AreEqual(L't', String2[8]);

			Elysium::Core::String String3(&L"random"[2], 3);
			Assert::AreEqual(L"ndo", String3.GetCharArray());
			Assert::AreEqual((size_t)3, String3.GetLength());
			Assert::AreEqual(L'n', String3[0]);
			Assert::AreEqual(L'd', String3[1]);
			Assert::AreEqual(L'o', String3[2]);

			Elysium::Core::String EmptyString1(L"");
			Assert::AreEqual(L"", EmptyString1.GetCharArray());
			Assert::AreEqual((size_t)0, EmptyString1.GetLength());
			Assert::IsTrue(Elysium::Core::String::IsNullOrEmtpy(EmptyString1));

			Elysium::Core::String EmptyString2(nullptr);
			//Assert::AreEqual(nullptr, EmptyString2.GetCharArray());
			Assert::AreEqual((size_t)0, EmptyString2.GetLength());
			Assert::IsTrue(Elysium::Core::String::IsNullOrEmtpy(EmptyString2));

			Elysium::Core::String CopiedString(String1);
			Assert::AreEqual(L"text", CopiedString.GetCharArray());
			Assert::AreEqual((size_t)4, CopiedString.GetLength());
			Assert::AreEqual(L't', CopiedString[0]);
			Assert::AreEqual(L'e', CopiedString[1]);
			Assert::AreEqual(L'x', CopiedString[2]);
			Assert::AreEqual(L't', CopiedString[3]);

			InputString(L"test");
		}
		TEST_METHOD(Substring)
		{
			Elysium::Core::String Source = Elysium::Core::String(L"this is a string containing some text");
			Assert::AreEqual(L"this is a string containing some text", Source.GetCharArray());
			Elysium::Core::String Substring1;
			Elysium::Core::String Substring2;
			
			Source.Substring(5, &Substring1);
			Assert::AreEqual((size_t)32, Substring1.GetLength());
			Assert::AreEqual(L"is a string containing some text", Substring1.GetCharArray());
			
			Source.Substring(8, 19, &Substring2);
			Assert::AreEqual((size_t)19, Substring2.GetLength());
			Assert::AreEqual(L"a string containing", Substring2.GetCharArray());
		}
	private:
		void InputString(const Elysium::Core::String& Value)
		{
			Assert::AreEqual((size_t)4, Value.GetLength());
			Assert::AreEqual(L't', Value[0]);
			Assert::AreEqual(L'e', Value[1]);
			Assert::AreEqual(L's', Value[2]);
			Assert::AreEqual(L't', Value[3]);
		}
	};
}
