#include "CppUnitTest.h"

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
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

#ifndef ELYSIUM_CORE_IO_FILESTREAM
#include "../../../Libraries/01-Shared/Elysium.Core.IO/FileStream.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STREAMREADER
#include "../../../Libraries/01-Shared/Elysium.Core.IO/StreamReader.hpp"
#endif

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Text
{
	TEST_CLASS(EncodingTest)
	{
	public:
		TEST_METHOD(Encoding)
		{
			const Elysium::Core::Text::Encoding& ASCIIEncoding = Elysium::Core::Text::Encoding::ASCII();
			const Elysium::Core::Text::Encoding& DefaultEncoding = Elysium::Core::Text::Encoding::Default();
			const Elysium::Core::Text::Encoding& UTF8Encoding = Elysium::Core::Text::Encoding::UTF8();
			const Elysium::Core::Text::UTF8Encoding& CastUTF8Encoding = static_cast<const Elysium::Core::Text::UTF8Encoding&>(UTF8Encoding);

			Assert::AreEqual(20127, ASCIIEncoding.GetCodePage());
			Assert::AreEqual(65001, DefaultEncoding.GetCodePage());
			Assert::AreEqual(65001, UTF8Encoding.GetCodePage());
			Assert::AreEqual(65001, CastUTF8Encoding.GetCodePage());

			Assert::AreEqual(true, ASCIIEncoding.GetIsSingleByte());
			Assert::AreEqual(false, DefaultEncoding.GetIsSingleByte());
			Assert::AreEqual(false, UTF8Encoding.GetIsSingleByte());
			Assert::AreEqual(false, CastUTF8Encoding.GetIsSingleByte());

			// ASCII
			{
				Elysium::Core::String Input = Elysium::Core::String(256);
				for (size_t i = 0; i < Input.GetLength(); ++i)
				{
					Input[i] = static_cast<char>(i);
				}

				Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Bytes = ASCIIEncoding.GetBytes(Input, 0, Input.GetLength());
				for (size_t i = 0; i < 128; ++i)
				{
					Assert::AreEqual((int)Bytes[i], (int)i);
				}
				for (size_t i = 128; i < 256; ++i)
				{
					Assert::AreEqual((int)Bytes[i], 0x3F);
				}

				Elysium::Core::String Output = ASCIIEncoding.GetString(&Bytes[0], Bytes.GetLength());
				Assert::AreEqual(Input.GetLength(), Output.GetLength());
				for (size_t i = 0; i < 128; ++i)
				{
					Assert::AreEqual(Input[i], Output[i]);
				}
				for (size_t i = 128; i < 256; ++i)
				{
					Assert::AreEqual(static_cast<char8_t>(0x3F), Output[i]);
				}
			}


			// Unicode
			{
				//Elysium::Core::String Input = "\x24\xC2\xA2\xE2\x82\xAC\xF0\x90\x8D\x88\xE0\xA4\xB9";
				Elysium::Core::String Input = u8"$¢€\x10348\x0939";

				// UTF-8
				{
					Assert::AreEqual(static_cast<size_t>(13), Input.GetLength());

					Assert::AreEqual(static_cast<const char8_t>(0x24), Input[0]);

					Assert::AreEqual(static_cast<const char8_t>(0xC2), Input[1]);
					Assert::AreEqual(static_cast<const char8_t>(0xA2), Input[2]);

					Assert::AreEqual(static_cast<const char8_t>(0xE2), Input[3]);
					Assert::AreEqual(static_cast<const char8_t>(0x82), Input[4]);
					Assert::AreEqual(static_cast<const char8_t>(0xAC), Input[5]);

					Assert::AreEqual(static_cast<const char8_t>(0xF0), Input[6]);
					Assert::AreEqual(static_cast<const char8_t>(0x90), Input[7]);
					Assert::AreEqual(static_cast<const char8_t>(0x8D), Input[8]);
					Assert::AreEqual(static_cast<const char8_t>(0x88), Input[9]);

					Assert::AreEqual(static_cast<const char8_t>(0xE0), Input[10]);
					Assert::AreEqual(static_cast<const char8_t>(0xA4), Input[11]);
					Assert::AreEqual(static_cast<const char8_t>(0xB9), Input[12]);

					Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Bytes = UTF8Encoding.GetBytes(Input, 0, Input.GetLength());
					Assert::AreEqual(static_cast<size_t>(Input.GetLength()), Bytes.GetLength());
					for (size_t i = 0; i < Bytes.GetLength(); ++i)
					{
						Assert::AreEqual(static_cast<Elysium::Core::byte>(Input[i]), Bytes[i]);
					}

					Elysium::Core::String Output = UTF8Encoding.GetString(&Bytes[0], Bytes.GetLength());
					AssertExtended::AreEqual(Input, Output);
				}

				// UTF-16 BE
				{
					Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Bytes = Elysium::Core::Collections::Template::Array<Elysium::Core::byte>(10);

					Elysium::Core::String Output = Elysium::Core::Text::Encoding::UTF16BE().GetString(&Bytes[0], Bytes.GetLength());
					AssertExtended::AreEqual(Input, Output);
				}
			}
		}

		TEST_METHOD(FileStreamUtf8)
		{
			{
				Elysium::Core::IO::FileStream SourceStream = Elysium::Core::IO::FileStream(u8"Utf8.txt", Elysium::Core::IO::FileMode::Open, Elysium::Core::IO::FileAccess::Read);
				Elysium::Core::IO::StreamReader Reader = Elysium::Core::IO::StreamReader(SourceStream, Elysium::Core::Text::Encoding::UTF8());
			}
		}

		TEST_METHOD(FileStreamUtf16)
		{
			{
				Elysium::Core::IO::FileStream SourceStream = Elysium::Core::IO::FileStream(u8"Utf16LE.txt", Elysium::Core::IO::FileMode::Open, Elysium::Core::IO::FileAccess::Read);
				Elysium::Core::IO::StreamReader Reader = Elysium::Core::IO::StreamReader(SourceStream, Elysium::Core::Text::Encoding::UTF16LE());
			}

			{
				Elysium::Core::IO::FileStream SourceStream = Elysium::Core::IO::FileStream(u8"Utf16BE.txt", Elysium::Core::IO::FileMode::Open, Elysium::Core::IO::FileAccess::Read);
				Elysium::Core::IO::StreamReader Reader = Elysium::Core::IO::StreamReader(SourceStream, Elysium::Core::Text::Encoding::UTF16BE());
			}
		}

		TEST_METHOD(FileStreamUtf32)
		{
			{
				Elysium::Core::IO::FileStream SourceStream = Elysium::Core::IO::FileStream(u8"Utf32.txt", Elysium::Core::IO::FileMode::Open, Elysium::Core::IO::FileAccess::Read);
				Elysium::Core::IO::StreamReader Reader = Elysium::Core::IO::StreamReader(SourceStream, Elysium::Core::Text::Encoding::UTF32());
			}
		}
	};
}
