#include "CppUnitTest.h"

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#include "CppUnitTestFrameworkExtension.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../../../Libraries/01-Shared/Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../../../Libraries/01-Shared/Elysium.Core.Text/Encoding.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_UTF8ENCODING
#include "../../../Libraries/01-Shared/Elysium.Core.Text/UTF8Encoding.hpp"
#endif

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsCore
{
	TEST_CLASS(Core_String)
	{
	public:
		TEST_METHOD(Constructors)
		{			
			Elysium::Core::String String1 = Elysium::Core::String(u"text");
			AssertExtended::AreEqual(u"text", String1.GetCharArray());
			Assert::AreEqual((size_t)4, String1.GetLength());
			AssertExtended::AreEqual(u't', String1[0]);
			AssertExtended::AreEqual(u'e', String1[1]);
			AssertExtended::AreEqual(u'x', String1[2]);
			AssertExtended::AreEqual(u't', String1[3]);

			Elysium::Core::String String2 = u"different";
			AssertExtended::AreEqual(u"different", String2.GetCharArray());
			Assert::AreEqual((size_t)9, String2.GetLength());
			AssertExtended::AreEqual(u'd', String2[0]);
			AssertExtended::AreEqual(u'i', String2[1]);
			AssertExtended::AreEqual(u'f', String2[2]);
			AssertExtended::AreEqual(u'f', String2[3]);
			AssertExtended::AreEqual(u'e', String2[4]);
			AssertExtended::AreEqual(u'r', String2[5]);
			AssertExtended::AreEqual(u'e', String2[6]);
			AssertExtended::AreEqual(u'n', String2[7]);
			AssertExtended::AreEqual(u't', String2[8]);

			Elysium::Core::String String3(&u"random"[2], 3);
			AssertExtended::AreEqual(u"ndo", String3.GetCharArray());
			Assert::AreEqual((size_t)3, String3.GetLength());
			AssertExtended::AreEqual(u'n', String3[0]);
			AssertExtended::AreEqual(u'd', String3[1]);
			AssertExtended::AreEqual(u'o', String3[2]);

			Elysium::Core::String EmptyString1(u"");
			AssertExtended::AreEqual(u"", EmptyString1.GetCharArray());
			Assert::AreEqual((size_t)0, EmptyString1.GetLength());
			Assert::IsTrue(Elysium::Core::String::IsNullOrEmtpy(EmptyString1));

			Elysium::Core::String EmptyString2(nullptr);
			//Assert::AreEqual(nullptr, EmptyString2.GetCharArray());
			Assert::AreEqual((size_t)0, EmptyString2.GetLength());
			Assert::IsTrue(Elysium::Core::String::IsNullOrEmtpy(EmptyString2));

			Elysium::Core::String CopiedString(String1);
			AssertExtended::AreEqual(u"text", CopiedString.GetCharArray());
			Assert::AreEqual((size_t)4, CopiedString.GetLength());
			AssertExtended::AreEqual(u't', CopiedString[0]);
			AssertExtended::AreEqual(u'e', CopiedString[1]);
			AssertExtended::AreEqual(u'x', CopiedString[2]);
			AssertExtended::AreEqual(u't', CopiedString[3]);

			Elysium::Core::String MovedString = std::move(String1);
			AssertExtended::AreEqual(u"text", MovedString.GetCharArray());
			Assert::AreEqual((size_t)4, MovedString.GetLength());
			AssertExtended::AreEqual(u't', MovedString[0]);
			AssertExtended::AreEqual(u'e', MovedString[1]);
			AssertExtended::AreEqual(u'x', MovedString[2]);
			AssertExtended::AreEqual(u't', MovedString[3]);
		}
		TEST_METHOD(GetEnumerator)
		{
			Elysium::Core::String String1 = Elysium::Core::String(u"text");
			/*
			Elysium::Core::CharEnumerator Enumerator = String1.GetEnumerator();

			int Count = 0;
			while (Enumerator.MoveNext())
			{
				Count++;
			}

			int x = 324;

			Assert::AreEqual(4, Count);
			*/
			Assert::Fail();
		}
		TEST_METHOD(IndexOf)
		{
			Elysium::Core::String SomeString = u"different";
			Assert::AreEqual((size_t)0, SomeString.IndexOf(u'd'));
			Assert::AreEqual((size_t)1, SomeString.IndexOf(u'i'));
			Assert::AreEqual((size_t)2, SomeString.IndexOf(u'f'));
			Assert::AreEqual((size_t)8, SomeString.IndexOf(u't'));

			Assert::AreEqual((size_t)0, SomeString.IndexOf(u'f', 3));
			Assert::AreEqual((size_t)1, SomeString.IndexOf(u'e', 5));

			Assert::AreEqual((size_t)0, SomeString.IndexOf(u"di"));
			Assert::AreEqual((size_t)3, SomeString.IndexOf(u"fe"));
			Assert::AreEqual((size_t)7, SomeString.IndexOf(u"nt"));
		}
		TEST_METHOD(Split)
		{
			Elysium::Core::String Source = Elysium::Core::String(u"HTTP/1.1 200 OK\r\nDate: Fri, 29 Nov 2019 12:49:19 GMT\r\nContent-Type: text/html; charset=UTF-8\r\nTransfer-Encoding: chunked\r\nConnection: keep-alive\r\nSet-Cookie: __cfduid=d007dcacfb7e13f1ccff76110bae859eb1575031759; expires=Sun, 29-Dec-19 12:49:19 GMT; path=/; domain=.typicode.com; HttpOnly\r\nX-Powered-By: Express\r\nVary: Origin, Accept-Encoding\r\nAccess-Control-Allow-Credentials: true\r\nCache-Control: public, max-age=14400\r\nLast-Modified: Mon, 05 Aug 2019 03:07:14 GMT\r\nVia: 1.1 vegur\r\nCF-Cache-Status: HIT\r\nAge: 6201\r\nServer: cloudflare\r\nCF-RAY: 53d4b3737b75f3fb-LHR");

			Elysium::Core::Collections::Generic::List<Elysium::Core::String> Lines;
			Source.Split(u"\r\n", Lines);

			Assert::AreEqual((size_t)16, Lines.GetCount());
			AssertExtended::AreEqual(u"HTTP/1.1 200 OK", Lines[0].GetCharArray());
			AssertExtended::AreEqual(u"Date: Fri, 29 Nov 2019 12:49:19 GMT", Lines[1].GetCharArray());
			AssertExtended::AreEqual(u"Content-Type: text/html; charset=UTF-8", Lines[2].GetCharArray());
			AssertExtended::AreEqual(u"Transfer-Encoding: chunked", Lines[3].GetCharArray());
			AssertExtended::AreEqual(u"Connection: keep-alive", Lines[4].GetCharArray());
			AssertExtended::AreEqual(u"Set-Cookie: __cfduid=d007dcacfb7e13f1ccff76110bae859eb1575031759; expires=Sun, 29-Dec-19 12:49:19 GMT; path=/; domain=.typicode.com; HttpOnly", Lines[5].GetCharArray());
			AssertExtended::AreEqual(u"X-Powered-By: Express", Lines[6].GetCharArray());
			AssertExtended::AreEqual(u"Vary: Origin, Accept-Encoding", Lines[7].GetCharArray());
			AssertExtended::AreEqual(u"Access-Control-Allow-Credentials: true", Lines[8].GetCharArray());
			AssertExtended::AreEqual(u"Cache-Control: public, max-age=14400", Lines[9].GetCharArray());
			AssertExtended::AreEqual(u"Last-Modified: Mon, 05 Aug 2019 03:07:14 GMT", Lines[10].GetCharArray());
			AssertExtended::AreEqual(u"Via: 1.1 vegur", Lines[11].GetCharArray());
			AssertExtended::AreEqual(u"CF-Cache-Status: HIT", Lines[12].GetCharArray());
			AssertExtended::AreEqual(u"Age: 6201", Lines[13].GetCharArray());
			AssertExtended::AreEqual(u"Server: cloudflare", Lines[14].GetCharArray());
			AssertExtended::AreEqual(u"CF-RAY: 53d4b3737b75f3fb-LHR", Lines[15].GetCharArray());
		}
		TEST_METHOD(Substring)
		{
			Elysium::Core::String Source = Elysium::Core::String(u"this is a string containing some text");
			AssertExtended::AreEqual(u"this is a string containing some text", Source.GetCharArray());
			Elysium::Core::String Substring1;
			Elysium::Core::String Substring2;
			
			Source.Substring(5, &Substring1);
			Assert::AreEqual((size_t)32, Substring1.GetLength());
			AssertExtended::AreEqual(u"is a string containing some text", Substring1.GetCharArray());
			
			Source.Substring(8, 19, &Substring2);
			Assert::AreEqual((size_t)19, Substring2.GetLength());
			AssertExtended::AreEqual(u"a string containing", Substring2.GetCharArray());
		}

		TEST_METHOD(Encoding)
		{
			const Elysium::Core::Text::Encoding& DefaultEncoding = Elysium::Core::Text::Encoding::Default();
			const Elysium::Core::Text::Encoding& UTF8Encoding = Elysium::Core::Text::Encoding::UTF8();
			const Elysium::Core::Text::UTF8Encoding& CastUTF8Encoding = static_cast<const Elysium::Core::Text::UTF8Encoding&>(UTF8Encoding);

			Assert::AreEqual(1252, DefaultEncoding.GetCodePage());
			Assert::AreEqual(65001, UTF8Encoding.GetCodePage());
			Assert::AreEqual(65001, CastUTF8Encoding.GetCodePage());

			Assert::AreEqual(true, DefaultEncoding.GetIsSingleByte());
			Assert::AreEqual(false, UTF8Encoding.GetIsSingleByte());
			Assert::AreEqual(false, CastUTF8Encoding.GetIsSingleByte());

			Elysium::Core::Collections::Generic::List<Elysium::Core::byte> OutputBytes = DefaultEncoding.GetBytes(u'[');
			Assert::AreEqual((size_t)2, OutputBytes.GetCount());
			AssertExtended::AreEqual(u'[', OutputBytes[0]);

			OutputBytes = DefaultEncoding.GetBytes(u'\r');
			Assert::AreEqual((size_t)2, OutputBytes.GetCount());
			AssertExtended::AreEqual(u'\r', OutputBytes[0]);

			Elysium::Core::String OriginalString = u"äöüß";
			OutputBytes = DefaultEncoding.GetBytes(OriginalString, (size_t)0, (size_t)OriginalString.GetLength());
			Assert::AreEqual((size_t)9, OutputBytes.GetCount());
			
			Elysium::Core::String OutputString = DefaultEncoding.GetString(&OutputBytes[0], OutputBytes.GetCount());
			Assert::AreEqual(OriginalString.GetLength(), OutputString.GetLength());
			AssertExtended::AreEqual(OriginalString.GetCharArray(), OutputString.GetCharArray());
			/*
			OutputString = DefaultEncoding.GetString(&OutputBytes[0], -1);
			AssertExtended::AreEqual(OriginalString.GetCharArray(), OutputString.GetCharArray());
			*/
		}
	};
}
