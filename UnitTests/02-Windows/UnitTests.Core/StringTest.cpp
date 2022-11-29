#include "CppUnitTest.h"
#include "CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core/Environment.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core/String.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core/StringView.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Encoding.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core
{
	TEST_CLASS(StringTests)
	{
	public:
		TEST_METHOD(Constructors)
		{
			Elysium::Core::Utf8String EmptyString1 = Elysium::Core::Utf8String();
			Assert::AreEqual((Elysium::Core::size)0, EmptyString1.GetLength());
			Assert::IsTrue(Elysium::Core::Utf8String::IsEmpty(EmptyString1));

			Elysium::Core::Utf8String EmptyString2 = u8"";
			Assert::AreEqual((Elysium::Core::size)0, EmptyString2.GetLength());
			Assert::IsTrue(Elysium::Core::Utf8String::IsEmpty(EmptyString2));

			Elysium::Core::Utf8String LString = Elysium::Core::Utf8String(5);
			Assert::AreEqual(5_ui64, LString.GetLength());
			
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
		}

		TEST_METHOD(EncodingToToANSIString)
		{
			Assert::Fail();
		}

		TEST_METHOD(EncodingToToASCIIString)
		{
			Elysium::Core::String CharStackString = "φί~";
			Elysium::Core::Utf8String Char8StackString = u8"φί~";
			Elysium::Core::Utf16String Char16StackString = u"φί~";
			Elysium::Core::Utf32String Char32StackString = U"φί~";
			Elysium::Core::WideString WCharStackString = L"φί~";

			Elysium::Core::String ConvertedCharStackString1 = Elysium::Core::Template::Text::Encoding::ToASCIIString<char>(CharStackString);
			Elysium::Core::String ConvertedCharStackString2 = Elysium::Core::Template::Text::Encoding::ToASCIIString<char8_t>(Char8StackString);
			Elysium::Core::String ConvertedCharStackString3 = Elysium::Core::Template::Text::Encoding::ToASCIIString<char16_t>(Char16StackString);
			Elysium::Core::String ConvertedCharStackString4 = Elysium::Core::Template::Text::Encoding::ToASCIIString<char32_t>(Char32StackString);
			Elysium::Core::String ConvertedCharStackString5 = Elysium::Core::Template::Text::Encoding::ToASCIIString<wchar_t>(WCharStackString);

			Elysium::Core::String ASCIIStackString = "??~";
			AssertExtended::AreEqual(ASCIIStackString, ConvertedCharStackString1);
			AssertExtended::AreEqual(ASCIIStackString, ConvertedCharStackString2);
			AssertExtended::AreEqual(ASCIIStackString, ConvertedCharStackString3);
			AssertExtended::AreEqual(ASCIIStackString, ConvertedCharStackString4);
			AssertExtended::AreEqual(ASCIIStackString, ConvertedCharStackString5);

			Elysium::Core::String CharHeapString = "this string is a bit longer to force it onto the heap";
			Elysium::Core::Utf8String Char8HeapString = u8"this string is a bit longer to force it onto the heap";
			Elysium::Core::Utf16String Char16HeapString = u"this string is a bit longer to force it onto the heap";
			Elysium::Core::Utf32String Char32HeapString = U"this string is a bit longer to force it onto the heap";
			Elysium::Core::WideString WCharHeapString = L"this string is a bit longer to force it onto the heap";

			Elysium::Core::String ConvertedCharHeapString1 = Elysium::Core::Template::Text::Encoding::ToASCIIString<char>(CharHeapString);
			Elysium::Core::String ConvertedCharHeapString2 = Elysium::Core::Template::Text::Encoding::ToASCIIString<char8_t>(Char8HeapString);
			Elysium::Core::String ConvertedCharHeapString3 = Elysium::Core::Template::Text::Encoding::ToASCIIString<char16_t>(Char16HeapString);
			Elysium::Core::String ConvertedCharHeapString4 = Elysium::Core::Template::Text::Encoding::ToASCIIString<char32_t>(Char32HeapString);
			Elysium::Core::String ConvertedCharHeapString5 = Elysium::Core::Template::Text::Encoding::ToASCIIString<wchar_t>(WCharHeapString);

			AssertExtended::AreEqual(&CharHeapString[0], &ConvertedCharHeapString1[0]);
			AssertExtended::AreEqual(&CharHeapString[0], &ConvertedCharHeapString2[0]);
			AssertExtended::AreEqual(&CharHeapString[0], &ConvertedCharHeapString3[0]);
			AssertExtended::AreEqual(&CharHeapString[0], &ConvertedCharHeapString4[0]);
			AssertExtended::AreEqual(&CharHeapString[0], &ConvertedCharHeapString5[0]);
		}

		TEST_METHOD(EncodingToUtf8String)
		{
			Elysium::Core::String CharStackString = "φί~";
			Elysium::Core::Utf8String Char8StackString = u8"φί~";
			Elysium::Core::Utf16String Char16StackString = u"φί~";
			Elysium::Core::Utf32String Char32StackString = U"φί~";
			Elysium::Core::WideString WCharStackString = L"φί~";
			Assert::Fail();
			/*
			Elysium::Core::Utf8String ConvertedUtf8CharStackString1 = Elysium::Core::Template::Text::Encoding::ToUtf8String<char>(CharStackString);
			Elysium::Core::Utf8String ConvertedUtf8CharStackString2 = Elysium::Core::Template::Text::Encoding::ToUtf8String<char8_t>(Char8StackString);
			//Elysium::Core::Utf8String ConvertedUtf8CharStackString3 = Elysium::Core::Template::Text::Encoding::ToUtf8String<char16_t>(Char16StackString);
			//Elysium::Core::Utf8String ConvertedUtf8CharStackString4 = Elysium::Core::Template::Text::Encoding::ToUtf8String<char32_t>(Char32StackString);
			Elysium::Core::Utf8String ConvertedUtf8CharStackString5 = Elysium::Core::Template::Text::Encoding::ToUtf8String<wchar_t>(WCharStackString);

			AssertExtended::AreEqual(&Char8StackString[0], &ConvertedUtf8CharStackString1[0]);
			AssertExtended::AreEqual(&Char8StackString[0], &ConvertedUtf8CharStackString2[0]);
			//AssertExtended::AreEqual(&Char8StackString[0], &ConvertedUtf8CharStackString3[0]);
			//AssertExtended::AreEqual(&Char8StackString[0], &ConvertedUtf8CharStackString4[0]);
			AssertExtended::AreEqual(&Char8StackString[0], &ConvertedUtf8CharStackString5[0]);
			*/
		}

		TEST_METHOD(EncodingToWideString)
		{
			Elysium::Core::String CharStackString = "φί~";
			Elysium::Core::Utf8String Char8StackString = u8"φί~";
			Elysium::Core::Utf16String Char16StackString = u"φί~";
			Elysium::Core::Utf32String Char32StackString = U"φί~";
			Elysium::Core::WideString WCharStackString = L"φί~";

			Elysium::Core::WideString ConvertedWCharStackString1 = Elysium::Core::Template::Text::Encoding::ToWideString<char>(CharStackString);
			Elysium::Core::WideString ConvertedWCharStackString2 = Elysium::Core::Template::Text::Encoding::ToWideString<char8_t>(Char8StackString);
			Elysium::Core::WideString ConvertedWCharStackString3 = Elysium::Core::Template::Text::Encoding::ToWideString<char16_t>(Char16StackString);
			//Elysium::Core::WideString ConvertedWCharStackString4 = Elysium::Core::Template::Text::Encoding::ToWideString<char32_t>(Char32StackString);
			Elysium::Core::WideString ConvertedWCharStackString5 = Elysium::Core::Template::Text::Encoding::ToWideString<wchar_t>(WCharStackString);
			
			AssertExtended::AreEqual(&WCharStackString[0], &ConvertedWCharStackString1[0]);
			AssertExtended::AreEqual(&WCharStackString[0], &ConvertedWCharStackString2[0]);
			AssertExtended::AreEqual(&WCharStackString[0], &ConvertedWCharStackString3[0]);
			//AssertExtended::AreEqual(&WCharStackString[0], &ConvertedWCharStackString4[0]);
			AssertExtended::AreEqual(&WCharStackString[0], &ConvertedWCharStackString5[0]);

			Elysium::Core::String CharHeapString = "this string is a bit longer to force it onto the heap";
			Elysium::Core::Utf8String Char8HeapString = u8"this string is a bit longer to force it onto the heap";
			Elysium::Core::Utf16String Char16HeapString = u"this string is a bit longer to force it onto the heap";
			Elysium::Core::Utf32String Char32HeapString = U"this string is a bit longer to force it onto the heap";
			Elysium::Core::WideString WCharHeapString = L"this string is a bit longer to force it onto the heap";

			Elysium::Core::WideString ConvertedWCharHeapString1 = Elysium::Core::Template::Text::Encoding::ToWideString<char>(CharHeapString);
			Elysium::Core::WideString ConvertedWCharHeapString2 = Elysium::Core::Template::Text::Encoding::ToWideString<char8_t>(Char8HeapString);
			Elysium::Core::WideString ConvertedWCharHeapString3 = Elysium::Core::Template::Text::Encoding::ToWideString<char16_t>(Char16HeapString);
			//Elysium::Core::WideString ConvertedWCharHeapString4 = Elysium::Core::Template::Text::Encoding::ToWideString<char32_t>(Char32HeapString);
			Elysium::Core::WideString ConvertedWCharHeapString5 = Elysium::Core::Template::Text::Encoding::ToWideString<wchar_t>(WCharHeapString);

			AssertExtended::AreEqual(&WCharHeapString[0], &ConvertedWCharHeapString1[0]);
			AssertExtended::AreEqual(&WCharHeapString[0], &ConvertedWCharHeapString2[0]);
			AssertExtended::AreEqual(&WCharHeapString[0], &ConvertedWCharHeapString3[0]);
			//AssertExtended::AreEqual(&WCharHeapString[0], &ConvertedWCharHeapString4[0]);
			AssertExtended::AreEqual(&WCharHeapString[0], &ConvertedWCharHeapString5[0]);
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
			Elysium::Core::Utf8StringView SourceView = Source;

			Elysium::Core::Template::Container::Vector<Elysium::Core::Utf8StringView> Lines = SourceView.Split(&Elysium::Core::Environment::NewLine[0]);

			Elysium::Core::Utf8StringView l1 = Lines[1];
			Elysium::Core::Utf8String s1 = l1.ToString();

			Assert::AreEqual((Elysium::Core::size)16, Lines.GetLength());
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
