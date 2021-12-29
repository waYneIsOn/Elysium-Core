#include "CppUnitTest.h"
#include "CppUnitTestFrameworkExtension.hpp"

#ifndef ELYSIUM_CORE_STRING
#include "../../../Libraries/01-Shared/Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "../../../Libraries/01-Shared/Elysium.Core/List.hpp"
#endif

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core
{
	TEST_CLASS(StringTests)
	{
	public:

		TEST_METHOD(Constructors)
		{
			Elysium::Core::Utf8String NullString1 = Elysium::Core::Utf8String();
			//Assert::IsNull(&NullString1[0]);
			Assert::AreEqual((Elysium::Core::size)0, NullString1.GetLength());
			Assert::IsTrue(Elysium::Core::Utf8String::IsNull(NullString1));
			Assert::IsFalse(Elysium::Core::Utf8String::IsEmpty(NullString1));
			Assert::IsTrue(Elysium::Core::Utf8String::IsNullOrEmtpy(NullString1));

			Elysium::Core::Utf8String LString = Elysium::Core::Utf8String(5);
			Assert::AreEqual((Elysium::Core::size)5, LString.GetLength());
			
			Elysium::Core::Utf8String EmptyString(u8"");
			//Assert::IsNull(&EmptyString[0]);
			Assert::AreEqual((Elysium::Core::size)0, EmptyString.GetLength());
			Assert::IsTrue(Elysium::Core::Utf8String::IsNull(EmptyString));
			Assert::IsFalse(Elysium::Core::Utf8String::IsEmpty(EmptyString));
			Assert::IsTrue(Elysium::Core::Utf8String::IsNullOrEmtpy(EmptyString));
			
			Elysium::Core::Utf8String String1 = Elysium::Core::Utf8String(u8"text");
			AssertExtended::AreEqual(u8"text", &String1[0]);
			Assert::AreEqual((Elysium::Core::size)4, String1.GetLength());
			Assert::AreEqual(u8't', String1[0]);
			Assert::AreEqual(u8'e', String1[1]);
			Assert::AreEqual(u8'x', String1[2]);
			Assert::AreEqual(u8't', String1[3]);
			
			Elysium::Core::Utf8String String2 = u8"different";
			AssertExtended::AreEqual(u8"different", &String2[0]);
			Assert::AreEqual((Elysium::Core::size)9, String2.GetLength());
			Assert::AreEqual(u8'd', String2[0]);
			Assert::AreEqual(u8'i', String2[1]);
			Assert::AreEqual(u8'f', String2[2]);
			Assert::AreEqual(u8'f', String2[3]);
			Assert::AreEqual(u8'e', String2[4]);
			Assert::AreEqual(u8'r', String2[5]);
			Assert::AreEqual(u8'e', String2[6]);
			Assert::AreEqual(u8'n', String2[7]);
			Assert::AreEqual(u8't', String2[8]);
			
			Elysium::Core::Utf8String String3(&u8"random"[2], 3);
			AssertExtended::AreEqual(u8"ndo", &String3[0]);
			Assert::AreEqual((Elysium::Core::size)3, String3.GetLength());
			Assert::AreEqual(u8'n', String3[0]);
			Assert::AreEqual(u8'd', String3[1]);
			Assert::AreEqual(u8'o', String3[2]);
			
			Elysium::Core::Utf8String NullString2(nullptr);
			//Assert::IsNull(&NullString2[0]);
			Assert::AreEqual((Elysium::Core::size)0, NullString2.GetLength());
			Assert::IsTrue(Elysium::Core::Utf8String::IsNull(NullString2));
			Assert::IsFalse(Elysium::Core::Utf8String::IsEmpty(NullString2));
			Assert::IsTrue(Elysium::Core::Utf8String::IsNullOrEmtpy(NullString2));
			
			Elysium::Core::Utf8String CopiedString(String1);
			AssertExtended::AreEqual(u8"text", &CopiedString[0]);
			Assert::AreEqual((Elysium::Core::size)4, CopiedString.GetLength());
			Assert::AreEqual(u8't', CopiedString[0]);
			Assert::AreEqual(u8'e', CopiedString[1]);
			Assert::AreEqual(u8'x', CopiedString[2]);
			Assert::AreEqual(u8't', CopiedString[3]);
			
			Elysium::Core::Utf8String MovedString = Elysium::Core::Template::Functional::Move(String1);
			AssertExtended::AreEqual(u8"text", &MovedString[0]);
			Assert::AreEqual((Elysium::Core::size)4, MovedString.GetLength());
			Assert::AreEqual(u8't', MovedString[0]);
			Assert::AreEqual(u8'e', MovedString[1]);
			Assert::AreEqual(u8'x', MovedString[2]);
			Assert::AreEqual(u8't', MovedString[3]);
			//Assert::IsNull(&String1[0]);
			Assert::AreEqual((Elysium::Core::size)0, String1.GetLength());
			Assert::IsTrue(Elysium::Core::Utf8String::IsNull(String1));
			Assert::IsFalse(Elysium::Core::Utf8String::IsEmpty(String1));
			Assert::IsTrue(Elysium::Core::Utf8String::IsNullOrEmtpy(String1));
		}

		TEST_METHOD(Operators)
		{
			Elysium::Core::Utf8String Source = u8"some text";
			Elysium::Core::Utf8String Copy = Source;

			AssertExtended::AreEqual(u8"some text", &Source[0]);
			Assert::AreEqual((Elysium::Core::size)9, Source.GetLength());
			AssertExtended::AreEqual(u8"some text", &Copy[0]);
			Assert::AreEqual((Elysium::Core::size)9, Copy.GetLength());

			Elysium::Core::Utf8String Move = Elysium::Core::Template::Functional::Move(Source);
			//Assert::IsNull(&Source[0]);
			Assert::AreEqual((Elysium::Core::size)0, Source.GetLength());
			AssertExtended::AreEqual(u8"some text", &Move[0]);
			Assert::AreEqual((Elysium::Core::size)9, Move.GetLength());
		}

		TEST_METHOD(IndexOf)
		{
			Elysium::Core::Utf8String SomeString = u8"different";
			Assert::AreEqual((Elysium::Core::size)0, SomeString.IndexOf(u8'd'));
			Assert::AreEqual((Elysium::Core::size)1, SomeString.IndexOf(u8'i'));
			Assert::AreEqual((Elysium::Core::size)2, SomeString.IndexOf(u8'f'));
			Assert::AreEqual((Elysium::Core::size)8, SomeString.IndexOf(u8't'));

			Assert::AreEqual((Elysium::Core::size)0, SomeString.IndexOf(u8'f', 3));
			Assert::AreEqual((Elysium::Core::size)1, SomeString.IndexOf(u8'e', 5));

			Assert::AreEqual((Elysium::Core::size)0, SomeString.IndexOf(u8"di"));
			Assert::AreEqual((Elysium::Core::size)3, SomeString.IndexOf(u8"fe"));
			Assert::AreEqual((Elysium::Core::size)7, SomeString.IndexOf(u8"nt"));
		}

		TEST_METHOD(Split)
		{
			Elysium::Core::Utf8String Source = Elysium::Core::Utf8String(u8"HTTP/1.1 200 OK\r\nDate: Fri, 29 Nov 2019 12:49:19 GMT\r\nContent-Type: text/html; charset=UTF-8\r\nTransfer-Encoding: chunked\r\nConnection: keep-alive\r\nSet-Cookie: __cfduid=d007dcacfb7e13f1ccff76110bae859eb1575031759; expires=Sun, 29-Dec-19 12:49:19 GMT; path=/; domain=.typicode.com; HttpOnly\r\nX-Powered-By: Express\r\nVary: Origin, Accept-Encoding\r\nAccess-Control-Allow-Credentials: true\r\nCache-Control: public, max-age=14400\r\nLast-Modified: Mon, 05 Aug 2019 03:07:14 GMT\r\nVia: 1.1 vegur\r\nCF-Cache-Status: HIT\r\nAge: 6201\r\nServer: cloudflare\r\nCF-RAY: 53d4b3737b75f3fb-LHR");

			Elysium::Core::Collections::Template::List<Elysium::Core::Utf8String> Lines;
			Source.Split(u8"\r\n", Lines);

			Assert::AreEqual((Elysium::Core::size)16, Lines.GetCount());
			Assert::AreEqual(u8'H', Lines[0][0]);
			AssertExtended::AreEqual(u8"HTTP/1.1 200 OK", &Lines[0][0]);
			AssertExtended::AreEqual(u8"Date: Fri, 29 Nov 2019 12:49:19 GMT", &Lines[1][0]);
			AssertExtended::AreEqual(u8"Content-Type: text/html; charset=UTF-8", &Lines[2][0]);
			AssertExtended::AreEqual(u8"Transfer-Encoding: chunked", &Lines[3][0]);
			AssertExtended::AreEqual(u8"Connection: keep-alive", &Lines[4][0]);
			AssertExtended::AreEqual(u8"Set-Cookie: __cfduid=d007dcacfb7e13f1ccff76110bae859eb1575031759; expires=Sun, 29-Dec-19 12:49:19 GMT; path=/; domain=.typicode.com; HttpOnly", &Lines[5][0]);
			AssertExtended::AreEqual(u8"X-Powered-By: Express", &Lines[6][0]);
			AssertExtended::AreEqual(u8"Vary: Origin, Accept-Encoding", &Lines[7][0]);
			AssertExtended::AreEqual(u8"Access-Control-Allow-Credentials: true", &Lines[8][0]);
			AssertExtended::AreEqual(u8"Cache-Control: public, max-age=14400", &Lines[9][0]);
			AssertExtended::AreEqual(u8"Last-Modified: Mon, 05 Aug 2019 03:07:14 GMT", &Lines[10][0]);
			AssertExtended::AreEqual(u8"Via: 1.1 vegur", &Lines[11][0]);
			AssertExtended::AreEqual(u8"CF-Cache-Status: HIT", &Lines[12][0]);
			AssertExtended::AreEqual(u8"Age: 6201", &Lines[13][0]);
			AssertExtended::AreEqual(u8"Server: cloudflare", &Lines[14][0]);
			AssertExtended::AreEqual(u8"CF-RAY: 53d4b3737b75f3fb-LHR", &Lines[15][0]);
		}

		TEST_METHOD(Substring)
		{
			Elysium::Core::Utf8String Source = Elysium::Core::Utf8String(u8"this is a string containing some text");
			AssertExtended::AreEqual(u8"this is a string containing some text", &Source[0]);
			Elysium::Core::Utf8String Substring1;
			Elysium::Core::Utf8String Substring2;
			
			Substring1 = Source.Substring(5);
			Assert::AreEqual((Elysium::Core::size)32, Substring1.GetLength());
			AssertExtended::AreEqual(u8"is a string containing some text", &Substring1[0]);
			
			Substring2 = Source.Substring(8, 19);
			Assert::AreEqual((Elysium::Core::size)19, Substring2.GetLength());
			AssertExtended::AreEqual(u8"a string containing", &Substring2[0]);
		}
	};
}
