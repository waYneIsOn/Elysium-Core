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

#ifndef ELYSIUM_CORE_IO_STREAMWRITER
#include "../../../Libraries/01-Shared/Elysium.Core.IO/StreamWriter.hpp"
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
			const Elysium::Core::Text::Encoding& UTF16BEEncoding = Elysium::Core::Text::Encoding::UTF16BE();
			const Elysium::Core::Text::Encoding& UTF16LEEncoding = Elysium::Core::Text::Encoding::UTF16LE();
			const Elysium::Core::Text::Encoding& UTF32BEEncoding = Elysium::Core::Text::Encoding::UTF32BE();
			const Elysium::Core::Text::Encoding& UTF32LEEncoding = Elysium::Core::Text::Encoding::UTF32LE();
			const Elysium::Core::Text::UTF8Encoding& CastUTF8Encoding = static_cast<const Elysium::Core::Text::UTF8Encoding&>(UTF8Encoding);

			Assert::AreEqual(Elysium::Core::uint32_t(20127), ASCIIEncoding.GetCodePage());
			Assert::AreEqual(Elysium::Core::uint32_t(65001), DefaultEncoding.GetCodePage());
			Assert::AreEqual(Elysium::Core::uint32_t(65001), UTF8Encoding.GetCodePage());
			Assert::AreEqual(Elysium::Core::uint32_t(1201), UTF16BEEncoding.GetCodePage());
			Assert::AreEqual(Elysium::Core::uint32_t(1200), UTF16LEEncoding.GetCodePage());
			Assert::AreEqual(Elysium::Core::uint32_t(12001), UTF32BEEncoding.GetCodePage());
			Assert::AreEqual(Elysium::Core::uint32_t(12000), UTF32LEEncoding.GetCodePage());
			Assert::AreEqual(Elysium::Core::uint32_t(65001), CastUTF8Encoding.GetCodePage());

			Assert::AreEqual(true, ASCIIEncoding.GetIsSingleByte());
			Assert::AreEqual(false, DefaultEncoding.GetIsSingleByte());
			Assert::AreEqual(false, UTF8Encoding.GetIsSingleByte());
			Assert::AreEqual(false, UTF16BEEncoding.GetIsSingleByte());
			Assert::AreEqual(false, UTF16LEEncoding.GetIsSingleByte());
			Assert::AreEqual(false, UTF32BEEncoding.GetIsSingleByte());
			Assert::AreEqual(false, UTF32LEEncoding.GetIsSingleByte());
			Assert::AreEqual(false, CastUTF8Encoding.GetIsSingleByte());

			// ASCII
			{
				Elysium::Core::Utf8String Input = Elysium::Core::Utf8String(256);
				for (Elysium::Core::size i = 0; i < Input.GetLength(); ++i)
				{
					Input[i] = static_cast<char>(i);
				}

				Elysium::Core::Container::VectorOfByte Bytes = ASCIIEncoding.GetBytes(&Input[0], Input.GetLength());
				for (Elysium::Core::size i = 0; i < 128; ++i)
				{
					Assert::AreEqual((int)Bytes[i], (int)i);
				}
				for (Elysium::Core::size i = 128; i < 256; ++i)
				{
					Assert::AreEqual((int)Bytes[i], 0x3F);
				}

				Elysium::Core::Utf8String Output = ASCIIEncoding.GetString(&Bytes[0], Bytes.GetLength());
				Assert::AreEqual(Input.GetLength(), Output.GetLength());
				for (Elysium::Core::size i = 0; i < 128; ++i)
				{
					Assert::AreEqual(Input[i], Output[i]);
				}
				for (Elysium::Core::size i = 128; i < 256; ++i)
				{
					Assert::AreEqual(static_cast<char8_t>(0x3F), Output[i]);
				}
			}


			// Unicode
			{
				//Elysium::Core::Utf8String Input = u8"\x24\xC2\xA2\xE2\x82\xAC\xF0\x90\x8D\x88\xE0\xA4\xB9";
				Elysium::Core::Utf8String Input = u8"$¢€\x10348\x0939";

				// UTF-8
				{
					Assert::AreEqual(static_cast<Elysium::Core::size>(13), Input.GetLength());

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

					Elysium::Core::Container::VectorOfByte Bytes = UTF8Encoding.GetBytes(&Input[0], Input.GetLength());
					Assert::AreEqual(static_cast<Elysium::Core::size>(Input.GetLength()), Bytes.GetLength());
					for (Elysium::Core::size i = 0; i < Bytes.GetLength(); ++i)
					{
						Assert::AreEqual(static_cast<Elysium::Core::byte>(Input[i]), Bytes[i]);
					}

					Elysium::Core::Utf8String Output = UTF8Encoding.GetString(&Bytes[0], Bytes.GetLength());
					AssertExtended::AreEqual(Input, Output);
				}

				// UTF-16 BE
				{
					Elysium::Core::Container::VectorOfByte Bytes = UTF16BEEncoding.GetBytes(&Input[0], Input.GetLength());
					Elysium::Core::Utf8String Output = UTF16BEEncoding.GetString(&Bytes[0], Bytes.GetLength());
					AssertExtended::AreEqual(Input, Output);
				}
			}
		}

		TEST_METHOD(Utf16BE_Bytes)
		{
			const Elysium::Core::Text::Encoding& Encoding = Elysium::Core::Text::Encoding::UTF16BE();

			Elysium::Core::Container::VectorOfByte Bytes = Elysium::Core::Container::VectorOfByte(
				{
					0x00, 0x74,	// would be 1 byte utf-8
					0x07, 0xFF, // would be 2 byte utf-8
					//0x04, 0xDF, // would be 2 byte utf-8
					0x60, 0x45,	// would be 3 byte utf-8
					//0xFF, 0xFF,	// would be 3 byte utf-8
					0xD8, 0x03, 0xDE, 0x6D,	// would be 4 byte utf-8
				});

			Elysium::Core::Utf8String ResultingString = Encoding.GetString(&Bytes[0], Bytes.GetLength());
			Assert::AreEqual(Bytes.GetLength(), ResultingString.GetLength());

			Elysium::Core::Container::VectorOfByte ResultingBytes = Encoding.GetBytes(&ResultingString[0], ResultingString.GetLength());
			Assert::AreEqual(Bytes.GetLength(), ResultingBytes.GetLength());
			for (Elysium::Core::size i = 0; i < Bytes.GetLength(); i++)
			{
				Assert::AreEqual(Bytes[i], ResultingBytes[i]);
			}
		}

		TEST_METHOD(Utf16LE_Bytes)
		{
			const Elysium::Core::Text::Encoding& Encoding = Elysium::Core::Text::Encoding::UTF16LE();

			Elysium::Core::Container::VectorOfByte Bytes = Elysium::Core::Container::VectorOfByte(
				{
					0x74, 0x00,	// would be 1 byte utf-8
					0xFF, 0x07, // would be 2 byte utf-8
					//0xDF, 0x04, // would be 2 byte utf-8
					0x45, 0x60,	// would be 3 byte utf-8
					//0xFF, 0xFF,	// would be 3 byte utf-8
					0x03, 0xD8, 0x6D, 0xDE,	// would be 4 byte utf-8
				});

			Elysium::Core::Utf8String ResultingString = Encoding.GetString(&Bytes[0], Bytes.GetLength());
			Assert::AreEqual(Bytes.GetLength(), ResultingString.GetLength());

			Elysium::Core::Container::VectorOfByte ResultingBytes = Encoding.GetBytes(&ResultingString[0], ResultingString.GetLength());
			Assert::AreEqual(Bytes.GetLength(), ResultingBytes.GetLength());
			for (Elysium::Core::size i = 0; i < Bytes.GetLength(); i++)
			{
				Elysium::Core::Template::System::byte Expected = Bytes[i];
				Elysium::Core::Template::System::byte Actual = ResultingBytes[i];

				Assert::AreEqual(Bytes[i], ResultingBytes[i]);
			}
		}

		TEST_METHOD(Utf8_FileStream)
		{
			Elysium::Core::Text::Encoding& Encoding = Elysium::Core::Text::Encoding::UTF8();

			Elysium::Core::IO::FileStream File = Elysium::Core::IO::FileStream(u8"Utf8.txt", Elysium::Core::IO::FileMode::Create,
				Elysium::Core::IO::FileAccess::Read | Elysium::Core::IO::FileAccess::Write);
			WriteTo(File, Encoding);
			ReadFrom(File, Encoding);
		}

		TEST_METHOD(Utf16BE_FileStream)
		{
			Elysium::Core::Text::Encoding& Encoding = Elysium::Core::Text::Encoding::UTF16BE();

			Elysium::Core::IO::FileStream File = Elysium::Core::IO::FileStream(u8"Utf16BE.txt", Elysium::Core::IO::FileMode::Create,
				Elysium::Core::IO::FileAccess::Read | Elysium::Core::IO::FileAccess::Write);
			WriteTo(File, Encoding);
			ReadFrom(File, Encoding);
		}

		TEST_METHOD(Utf16LE_FileStream)
		{
			Elysium::Core::Text::Encoding& Encoding = Elysium::Core::Text::Encoding::UTF16LE();

			Elysium::Core::IO::FileStream File = Elysium::Core::IO::FileStream(u8"Utf16LE.txt", Elysium::Core::IO::FileMode::Create,
				Elysium::Core::IO::FileAccess::Read | Elysium::Core::IO::FileAccess::Write);
			WriteTo(File, Encoding);
			ReadFrom(File, Encoding);
		}

		TEST_METHOD(Utf32BE_FileStream)
		{
			Assert::Fail(L"Heap corruption in WriteTo(...)!");

			Elysium::Core::Text::Encoding& Encoding = Elysium::Core::Text::Encoding::UTF32BE();

			Elysium::Core::IO::FileStream File = Elysium::Core::IO::FileStream(u8"Utf32BE.txt", Elysium::Core::IO::FileMode::Create,
				Elysium::Core::IO::FileAccess::Read | Elysium::Core::IO::FileAccess::Write);
			WriteTo(File, Encoding);
			ReadFrom(File, Encoding);
		}

		TEST_METHOD(Utf32LE_FileStream)
		{
			Assert::Fail(L"Heap corruption in WriteTo(...)!");

			Elysium::Core::Text::Encoding& Encoding = Elysium::Core::Text::Encoding::UTF32LE();

			Elysium::Core::IO::FileStream File = Elysium::Core::IO::FileStream(u8"Utf32LE.txt", Elysium::Core::IO::FileMode::Create,
				Elysium::Core::IO::FileAccess::Read | Elysium::Core::IO::FileAccess::Write);
			WriteTo(File, Encoding);
			ReadFrom(File, Encoding);
		}
	private:
		Elysium::Core::Utf8String _Content = u8"abc";

		void WriteTo(Elysium::Core::IO::FileStream& TargetStream, const Elysium::Core::Text::Encoding& Encoding)
		{
			Elysium::Core::Container::VectorOfByte Bytes = Encoding.GetBytes(&_Content[0], _Content.GetLength());

			Elysium::Core::IO::StreamWriter Writer = Elysium::Core::IO::StreamWriter(TargetStream, Encoding);
			Writer.Write(&Bytes[0], Bytes.GetLength());
			Writer.Flush();
			Writer.Close();
		}

		void ReadFrom(Elysium::Core::IO::FileStream& SourceStream, Elysium::Core::Text::Encoding& Encoding)
		{
			Elysium::Core::IO::StreamReader Reader = Elysium::Core::IO::StreamReader(SourceStream, Encoding);
			Elysium::Core::Utf8String Result = Reader.ReadToEnd();
			Reader.Close();

			AssertExtended::AreEqual(_Content, Result);
		}
	};
}
