#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Literals.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/CharacterTraits.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Template::Text;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Text
{
	TEST_CLASS(CharacterTraitsTests)
	{
	public:
		TEST_METHOD(StaticFields)
		{
			Assert::AreEqual(1_ui8, CharacterTraits<char>::MinimumByteLength);
			Assert::AreEqual(2_ui8, CharacterTraits<wchar_t>::MinimumByteLength);
			Assert::AreEqual(1_ui8, CharacterTraits<char8_t>::MinimumByteLength);
			Assert::AreEqual(2_ui8, CharacterTraits<char16_t>::MinimumByteLength);
			Assert::AreEqual(4_ui8, CharacterTraits<char32_t>::MinimumByteLength);

			Assert::AreEqual(1_ui8, CharacterTraits<char>::MaximumByteLength);
			Assert::AreEqual(4_ui8, CharacterTraits<wchar_t>::MaximumByteLength);
			Assert::AreEqual(4_ui8, CharacterTraits<char8_t>::MaximumByteLength);
			Assert::AreEqual(4_ui8, CharacterTraits<char16_t>::MaximumByteLength);
			Assert::AreEqual(4_ui8, CharacterTraits<char32_t>::MaximumByteLength);

			Assert::AreEqual('\0', CharacterTraits<char>::NullTerminationCharacter);
			Assert::AreEqual(L'\0', CharacterTraits<wchar_t>::NullTerminationCharacter);
			Assert::AreEqual(u8'\0', CharacterTraits<char8_t>::NullTerminationCharacter);
			Assert::AreEqual(0, static_cast<int>(CharacterTraits<char16_t>::NullTerminationCharacter));
			Assert::AreEqual(0, static_cast<int>(CharacterTraits<char32_t>::NullTerminationCharacter));

			Assert::AreEqual(-128, static_cast<int>(CharacterTraits<char>::MinimumValue));
			Assert::AreEqual(0, static_cast<int>(CharacterTraits<wchar_t>::MinimumValue));
			Assert::AreEqual(0, static_cast<int>(CharacterTraits<char8_t>::MinimumValue));
			Assert::AreEqual(0, static_cast<int>(CharacterTraits<char16_t>::MinimumValue));
			Assert::AreEqual(0, static_cast<int>(CharacterTraits<char32_t>::MinimumValue));
			
			Assert::AreEqual(127, static_cast<int>(CharacterTraits<char>::MaximumValue));
			Assert::AreEqual(65535, static_cast<int>(CharacterTraits<wchar_t>::MaximumValue));
			Assert::AreEqual(255, static_cast<int>(CharacterTraits<char8_t>::MaximumValue));
			Assert::AreEqual(65535, static_cast<int>(CharacterTraits<char16_t>::MaximumValue));
			Assert::AreEqual(4294967295u, static_cast<unsigned int>(CharacterTraits<char32_t>::MaximumValue));
		}

		TEST_METHOD(ConvertToUtf32)
		{
			/*
			// incorrect input!
			AssertExtended::AreEqual(U'\u0000', CharacterTraits<char>::ConvertToUtf32(nullptr));
			AssertExtended::AreEqual(U'\u0000', CharacterTraits<char8_t>::ConvertToUtf32(nullptr));
			AssertExtended::AreEqual(U'\u0000', CharacterTraits<char16_t>::ConvertToUtf32(nullptr));
			AssertExtended::AreEqual(U'\u0000', CharacterTraits<char32_t>::ConvertToUtf32(nullptr));
			AssertExtended::AreEqual(U'\u0000', CharacterTraits<wchar_t>::ConvertToUtf32(nullptr));
			*/
			AssertExtended::AreEqual(U'\u0000', CharacterTraits<char>::ConvertToUtf32(""));
			AssertExtended::AreEqual(U'\u0000', CharacterTraits<char8_t>::ConvertToUtf32(u8""));
			AssertExtended::AreEqual(U'\u0000', CharacterTraits<char16_t>::ConvertToUtf32(u""));
			AssertExtended::AreEqual(U'\u0000', CharacterTraits<char32_t>::ConvertToUtf32(U""));
			AssertExtended::AreEqual(U'\u0000', CharacterTraits<wchar_t>::ConvertToUtf32(L""));

			AssertExtended::AreEqual(U'\u003F', CharacterTraits<char>::ConvertToUtf32("\u01D1"));
			AssertExtended::AreEqual(U'\u01D1', CharacterTraits<char8_t>::ConvertToUtf32(u8"\u01D1"));
			AssertExtended::AreEqual(U'\u01D1', CharacterTraits<char16_t>::ConvertToUtf32(u"\u01D1"));
			AssertExtended::AreEqual(U'\u01D1', CharacterTraits<char32_t>::ConvertToUtf32(U"\u01D1"));
			AssertExtended::AreEqual(U'\u01D1', CharacterTraits<wchar_t>::ConvertToUtf32(L"\u01D1"));
		}

		TEST_METHOD(GetLength)
		{
			Assert::AreEqual(0_ui64, CharacterTraits<char>::GetLength(nullptr));
			Assert::AreEqual(0_ui64, CharacterTraits<char8_t>::GetLength(nullptr));
			Assert::AreEqual(0_ui64, CharacterTraits<char16_t>::GetLength(nullptr));
			Assert::AreEqual(0_ui64, CharacterTraits<char32_t>::GetLength(nullptr));
			Assert::AreEqual(0_ui64, CharacterTraits<wchar_t>::GetLength(nullptr));
			
			Assert::AreEqual(0_ui64, CharacterTraits<char>::GetLength(""));
			Assert::AreEqual(0_ui64, CharacterTraits<char8_t>::GetLength(u8""));
			Assert::AreEqual(0_ui64, CharacterTraits<char16_t>::GetLength(u""));
			Assert::AreEqual(0_ui64, CharacterTraits<char32_t>::GetLength(U""));
			Assert::AreEqual(0_ui64, CharacterTraits<wchar_t>::GetLength(L""));

			Assert::AreEqual(3_ui64, CharacterTraits<char>::GetLength("abc"));
			Assert::AreEqual(3_ui64, CharacterTraits<char8_t>::GetLength(u8"abc"));
			Assert::AreEqual(3_ui64, CharacterTraits<char16_t>::GetLength(u"abc"));
			Assert::AreEqual(3_ui64, CharacterTraits<char32_t>::GetLength(U"abc"));
			Assert::AreEqual(3_ui64, CharacterTraits<wchar_t>::GetLength(L"abc"));

			Assert::AreEqual(93_ui64, CharacterTraits<char>::GetLength("this is a sentence which has a few more letters and therefore is longer than the previous one"));
			Assert::AreEqual(93_ui64, CharacterTraits<char8_t>::GetLength(u8"this is a sentence which has a few more letters and therefore is longer than the previous one"));
			Assert::AreEqual(93_ui64, CharacterTraits<char16_t>::GetLength(u"this is a sentence which has a few more letters and therefore is longer than the previous one"));
			Assert::AreEqual(93_ui64, CharacterTraits<char32_t>::GetLength(U"this is a sentence which has a few more letters and therefore is longer than the previous one"));
			Assert::AreEqual(93_ui64, CharacterTraits<wchar_t>::GetLength(L"this is a sentence which has a few more letters and therefore is longer than the previous one"));

			Assert::AreEqual(3_ui64, CharacterTraits<char>::GetLength("\u01D1E9"));
			Assert::AreEqual(4_ui64, CharacterTraits<char8_t>::GetLength(u8"\u01D1E9"));
			Assert::AreEqual(3_ui64, CharacterTraits<char16_t>::GetLength(u"\u01D1E9"));
			Assert::AreEqual(3_ui64, CharacterTraits<char32_t>::GetLength(U"\u01D1E9"));
			Assert::AreEqual(3_ui64, CharacterTraits<wchar_t>::GetLength(L"\u01D1E9"));
		}

		TEST_METHOD(IsAsciiChar)
		{
			for (Elysium::Core::uint8_t i = 0; i < 0x80; i++)
			{
				Assert::IsTrue(CharacterTraits<char>::IsAscii(i));
				Assert::IsTrue(CharacterTraits<char8_t>::IsAscii(i));
				Assert::IsTrue(CharacterTraits<char16_t>::IsAscii(i));
				Assert::IsTrue(CharacterTraits<char32_t>::IsAscii(i));
				Assert::IsTrue(CharacterTraits<wchar_t>::IsAscii(i));
			}
			for (Elysium::Core::uint8_t i = 0x80; i < 0xFF; i++)
			{
				Assert::IsFalse(CharacterTraits<char>::IsAscii(i));
				Assert::IsFalse(CharacterTraits<char8_t>::IsAscii(i));
				Assert::IsFalse(CharacterTraits<char16_t>::IsAscii(i));
				Assert::IsFalse(CharacterTraits<char32_t>::IsAscii(i));
				Assert::IsFalse(CharacterTraits<wchar_t>::IsAscii(i));
			}
		}

		TEST_METHOD(IsControlChar)
		{
			// ASCII-characters
			for (Elysium::Core::uint8_t i = 0; i < 0x20; i++)
			{
				Assert::IsTrue(CharacterTraits<char>::IsControl(i));
				Assert::IsTrue(CharacterTraits<char8_t>::IsControl(i));
				Assert::IsTrue(CharacterTraits<char16_t>::IsControl(i));
				Assert::IsTrue(CharacterTraits<char32_t>::IsControl(i));
				Assert::IsTrue(CharacterTraits<wchar_t>::IsControl(i));
			}
			for (Elysium::Core::uint8_t i = 0x20; i < 0x7F; i++)
			{
				Assert::IsFalse(CharacterTraits<char>::IsControl(i));
				Assert::IsFalse(CharacterTraits<char8_t>::IsControl(i));
				Assert::IsFalse(CharacterTraits<char16_t>::IsControl(i));
				Assert::IsFalse(CharacterTraits<char32_t>::IsControl(i));
				Assert::IsFalse(CharacterTraits<wchar_t>::IsControl(i));
			}
			Assert::IsTrue(CharacterTraits<char>::IsControl(0x7F));
			Assert::IsTrue(CharacterTraits<char8_t>::IsControl(0x7F));
			Assert::IsTrue(CharacterTraits<char16_t>::IsControl(0x7F));
			Assert::IsTrue(CharacterTraits<char32_t>::IsControl(0x7F));
			Assert::IsTrue(CharacterTraits<wchar_t>::IsControl(0x7F));
			for (Elysium::Core::uint8_t i = 0x80; i < 0xA0; i++)
			{
				Assert::IsFalse(CharacterTraits<char>::IsControl(i));
				Assert::IsTrue(CharacterTraits<char8_t>::IsControl(i));
				Assert::IsTrue(CharacterTraits<char16_t>::IsControl(i));
				Assert::IsTrue(CharacterTraits<char32_t>::IsControl(i));
				Assert::IsTrue(CharacterTraits<wchar_t>::IsControl(i));
			}
			for (Elysium::Core::uint8_t i = 0xA0; i < 0xFF; i++)
			{
				Assert::IsFalse(CharacterTraits<char>::IsControl(i));
				Assert::IsFalse(CharacterTraits<char8_t>::IsControl(i));
				Assert::IsFalse(CharacterTraits<char16_t>::IsControl(i));
				Assert::IsFalse(CharacterTraits<char32_t>::IsControl(i));
				Assert::IsFalse(CharacterTraits<wchar_t>::IsControl(i));
			}
		}

		TEST_METHOD(IsDigitChar)
		{
			for (Elysium::Core::uint8_t i = 0x00; i < 0x30; i++)
			{
				Assert::IsFalse(CharacterTraits<char>::IsDigit(i));
				Assert::IsFalse(CharacterTraits<char8_t>::IsDigit(i));
				Assert::IsFalse(CharacterTraits<char16_t>::IsDigit(i));
				Assert::IsFalse(CharacterTraits<char32_t>::IsDigit(i));
				Assert::IsFalse(CharacterTraits<wchar_t>::IsDigit(i));
			}
			for (Elysium::Core::uint8_t i = 0x30; i < 0x3A; i++)
			{
				Assert::IsTrue(CharacterTraits<char>::IsDigit(i));
				Assert::IsTrue(CharacterTraits<char8_t>::IsDigit(i));
				Assert::IsTrue(CharacterTraits<char16_t>::IsDigit(i));
				Assert::IsTrue(CharacterTraits<char32_t>::IsDigit(i));
				Assert::IsTrue(CharacterTraits<wchar_t>::IsDigit(i));
			}
			for (Elysium::Core::uint8_t i = 0x3A; i < 0xFF; i++)
			{
				Assert::IsFalse(CharacterTraits<char>::IsDigit(i));
				Assert::IsFalse(CharacterTraits<char8_t>::IsDigit(i));
				Assert::IsFalse(CharacterTraits<char16_t>::IsDigit(i));
				Assert::IsFalse(CharacterTraits<char32_t>::IsDigit(i));
				Assert::IsFalse(CharacterTraits<wchar_t>::IsDigit(i));
			}
		}

		TEST_METHOD(IsLetter)
		{
			// ASCII-characters
			for (Elysium::Core::uint8_t i = 0; i < 0x41; i++)
			{
				Assert::IsFalse(CharacterTraits<char>::IsLetter(i));
				Assert::IsFalse(CharacterTraits<char8_t>::IsLetter(i));
				Assert::IsFalse(CharacterTraits<char16_t>::IsLetter(i));
				Assert::IsFalse(CharacterTraits<char32_t>::IsLetter(i));
				Assert::IsFalse(CharacterTraits<wchar_t>::IsLetter(i));
			}
			for (Elysium::Core::uint8_t i = 0x41; i < 0x5B; i++)
			{	// A - Z
				Assert::IsTrue(CharacterTraits<char>::IsLetter(i));
				Assert::IsTrue(CharacterTraits<char8_t>::IsLetter(i));
				Assert::IsTrue(CharacterTraits<char16_t>::IsLetter(i));
				Assert::IsTrue(CharacterTraits<char32_t>::IsLetter(i));
				Assert::IsTrue(CharacterTraits<wchar_t>::IsLetter(i));
			}
			for (Elysium::Core::uint8_t i = 0x5B; i < 0x61; i++)
			{
				Assert::IsFalse(CharacterTraits<char>::IsLetter(i));
				Assert::IsFalse(CharacterTraits<char8_t>::IsLetter(i));
				Assert::IsFalse(CharacterTraits<char16_t>::IsLetter(i));
				Assert::IsFalse(CharacterTraits<char32_t>::IsLetter(i));
				Assert::IsFalse(CharacterTraits<wchar_t>::IsLetter(i));
			}
			for (Elysium::Core::uint8_t i = 0x61; i < 0x7B; i++)
			{	// a - Z
				Assert::IsTrue(CharacterTraits<char>::IsLetter(i));
				Assert::IsTrue(CharacterTraits<char8_t>::IsLetter(i));
				Assert::IsTrue(CharacterTraits<char16_t>::IsLetter(i));
				Assert::IsTrue(CharacterTraits<char32_t>::IsLetter(i));
				Assert::IsTrue(CharacterTraits<wchar_t>::IsLetter(i));
			}
			for (Elysium::Core::uint8_t i = 0x7B; i < 0xFF; i++)
			{
				Assert::IsFalse(CharacterTraits<char>::IsLetter(i));
				Assert::IsFalse(CharacterTraits<char8_t>::IsLetter(i));
				Assert::IsFalse(CharacterTraits<char16_t>::IsLetter(i));
				Assert::IsFalse(CharacterTraits<char32_t>::IsLetter(i));
				Assert::IsFalse(CharacterTraits<wchar_t>::IsLetter(i));
			}
		}

		TEST_METHOD(IsValid)
		{
			// simple texts using ascii-chars only
			constexpr const char* SimpleText = "blabla";
			constexpr const char8_t* SimpleText8 = u8"blabla";
			constexpr const char16_t* SimpleText16 = u"blabla";
			constexpr const char32_t* SimpleText32 = U"blabla";
			constexpr const wchar_t* SimpleWideText = L"blabla";

			constexpr const Elysium::Core::Template::System::size STLength = CharacterTraits<char>::GetLength(SimpleText);
			constexpr const Elysium::Core::Template::System::size ST8Length = CharacterTraits<char8_t>::GetLength(SimpleText8);
			constexpr const Elysium::Core::Template::System::size ST16Length = CharacterTraits<char16_t>::GetLength(SimpleText16);
			constexpr const Elysium::Core::Template::System::size ST32Length = CharacterTraits<char32_t>::GetLength(SimpleText32);
			constexpr const Elysium::Core::Template::System::size STWLength = CharacterTraits<wchar_t>::GetLength(SimpleWideText);

			constexpr const bool IsSimpleTextValid = CharacterTraits<char>::IsValid(SimpleText, STLength);
			Assert::IsTrue(IsSimpleTextValid);

			const bool IsSimpleText8Valid = CharacterTraits<char8_t>::IsValid(SimpleText8, ST8Length);
			Assert::IsTrue(IsSimpleText8Valid);

			constexpr const bool IsSimpleText16Valid = CharacterTraits<char16_t>::IsValid(SimpleText16, ST16Length);
			Assert::IsTrue(IsSimpleText16Valid);

			constexpr const bool IsSimpleText32Valid = CharacterTraits<char32_t>::IsValid(SimpleText32, ST32Length);
			Assert::IsTrue(IsSimpleText32Valid);

			constexpr const bool IsSimpleWideTextValid = CharacterTraits<wchar_t>::IsValid(SimpleWideText, STWLength);
			Assert::IsTrue(IsSimpleWideTextValid);

			// more "complex" strings
			constexpr const char* Text = "צהü";
			constexpr const char8_t* Text8 = u8"צהü";
			constexpr const char16_t* Text16 = u"צהü";
			constexpr const char32_t* Text32 = U"צהü";
			constexpr const wchar_t* WideText = L"צהü";

			constexpr const Elysium::Core::Template::System::size TLength = CharacterTraits<char>::GetLength(Text);
			constexpr const Elysium::Core::Template::System::size T8Length = CharacterTraits<char8_t>::GetLength(Text8);
			constexpr const Elysium::Core::Template::System::size T16Length = CharacterTraits<char16_t>::GetLength(Text16);
			constexpr const Elysium::Core::Template::System::size T32Length = CharacterTraits<char32_t>::GetLength(Text32);
			constexpr const Elysium::Core::Template::System::size TWLength = CharacterTraits<wchar_t>::GetLength(WideText);

			constexpr const bool IsTextValid = CharacterTraits<char>::IsValid(Text, TLength);
			Assert::IsTrue(IsTextValid);

			constexpr const bool IsText8Valid = CharacterTraits<char8_t>::IsValid(Text8, T8Length);
			Assert::IsTrue(IsText8Valid);
			
			constexpr const bool IsText16Valid = CharacterTraits<char16_t>::IsValid(Text16, T16Length);
			Assert::IsTrue(IsText16Valid);

			constexpr const bool IsText32Valid = CharacterTraits<char32_t>::IsValid(Text32, T32Length);
			Assert::IsTrue(IsText32Valid);

			constexpr const bool IsWideTextValid = CharacterTraits<wchar_t>::IsValid(WideText, TWLength);
			Assert::IsTrue(IsWideTextValid);
		}

		TEST_METHOD(IsInvalid)
		{
			/*
			// ...
			{
				constexpr const char* InvalidText = "0000000000";
				constexpr const Elysium::Core::Template::System::size ITLength = CharacterTraits<char>::GetLength(InvalidText);
				constexpr const bool IsInvalidTextValid = CharacterTraits<char>::IsValid(InvalidText, ITLength);
				Assert::IsFalse(IsInvalidTextValid);
			}
			*/
			// utf-8
			{
				char8_t Text8[] = u8"0000000000";
				const Elysium::Core::Template::System::size IT8Length = CharacterTraits<char8_t>::GetLength(Text8);

				Elysium::Core::Template::System::byte* Data = reinterpret_cast<Elysium::Core::Template::System::byte*>(Text8);

				// multiple lead bytes in a row
				Data[0] = 0xC0;
				Data[1] = 0xC0;

				const bool IsTwoLeadingBytesValid = CharacterTraits<char8_t>::IsValid(Text8, IT8Length);
				Assert::IsFalse(IsTwoLeadingBytesValid);

				Data[0] = 0x00;
				Data[1] = 0x00;
				Assert::IsTrue(CharacterTraits<char8_t>::IsValid(Text8, IT8Length));

				// leading trail byte
				Data[0] = 0x80;
				const bool IsLeadingTrailByteValid = CharacterTraits<char8_t>::IsValid(Text8, IT8Length);
				Assert::IsFalse(IsLeadingTrailByteValid);

				Data[0] = 0x00;
				Assert::IsTrue(CharacterTraits<char8_t>::IsValid(Text8, IT8Length));

				// incorrect number of trail bytes
				Data[0] = 0xF7;	// should be three trail bytes but are none
				const bool IsTooFewTrailBytesValid = CharacterTraits<char8_t>::IsValid(Text8, IT8Length);
				Assert::IsFalse(IsTooFewTrailBytesValid);

				Data[0] = 0xE0;	// should be two trail bytes but are three
				Data[1] = 0xBF;
				Data[2] = 0xBF;
				Data[3] = 0xBF;
				const bool IsTooManyTrailBytesValid = CharacterTraits<char8_t>::IsValid(Text8, IT8Length);
				Assert::IsFalse(IsTooFewTrailBytesValid);

				Data[0] = 0x00;
				Data[1] = 0x00;
				Data[2] = 0x00;
				Data[3] = 0x00;
				Assert::IsTrue(CharacterTraits<char8_t>::IsValid(Text8, IT8Length));

				// invalid byte (0xF5 – 0xFF)
				Data[0] = 0xFF;
				const bool IsInvalidByteValid = CharacterTraits<char8_t>::IsValid(Text8, IT8Length);
				Assert::IsFalse(IsInvalidByteValid);

				Data[0] = 0x00;
				Assert::IsTrue(CharacterTraits<char8_t>::IsValid(Text8, IT8Length));

				// invalid code point (any > 0x10FFFF)
				Data[0] = static_cast<char8_t>(0xc0 + (0xFFFFFF >> 6));
				Data[1] = static_cast<char8_t>(0x80 + ((0xFFFFFF >> 12) & 0x3F));
				Data[2] = static_cast<char8_t>(0x80 + ((0xFFFFFF >> 6) & 0x3F));
				Data[3] = static_cast<char8_t>(0x80 + (0xFFFFFF & 0x3F));

				const bool IsInvalidCodePointValid = CharacterTraits<char8_t>::IsValid(Text8, IT8Length);
				Assert::IsFalse(IsInvalidCodePointValid);

				Data[0] = 0x00;
				Data[1] = 0x00;
				Data[2] = 0x00;
				Data[3] = 0x00;
				Assert::IsTrue(CharacterTraits<char8_t>::IsValid(Text8, IT8Length));

				// Non-canonical sequences/overlong representation (for instance: 0x41 fits into a single byte but get's spread out over two in this case)
				Data[0] = 0xC1;
				Data[1] = 0x81;
				const bool IsOverlongEncodingValid = CharacterTraits<char8_t>::IsValid(Text8, IT8Length);
				Assert::IsFalse(IsOverlongEncodingValid);

				Data[0] = 0x00;
				Data[1] = 0x00;
				Assert::IsTrue(CharacterTraits<char8_t>::IsValid(Text8, IT8Length));
				
				// @ToDo: check whether there are more things than can be invalid utf-8
			}
			/*
			// ...
			{
				constexpr const char16_t* InvalidText16 = u"0000000000";
				constexpr const Elysium::Core::Template::System::size IT16Length = CharacterTraits<char16_t>::GetLength(InvalidText16);
				constexpr const bool IsInvalidText16Valid = CharacterTraits<char16_t>::IsValid(InvalidText16, IT16Length);
				Assert::IsFalse(IsInvalidText16Valid);
			}

			// ...
			{
				constexpr const char32_t* InvalidText32 = U"0000000000";
				constexpr const Elysium::Core::Template::System::size IT32Length = CharacterTraits<char32_t>::GetLength(InvalidText32);
				constexpr const bool IsInvalidText32Valid = CharacterTraits<char32_t>::IsValid(InvalidText32, IT32Length);
				Assert::IsFalse(IsInvalidText32Valid);
			}

			// ...
			{
				constexpr const wchar_t* InvalidWideText = L"0000000000";
				constexpr const Elysium::Core::Template::System::size ITWLength = CharacterTraits<wchar_t>::GetLength(InvalidWideText);
				constexpr const bool IsInvalidWideTextValid = CharacterTraits<wchar_t>::IsValid(InvalidWideText, ITWLength);
				Assert::IsFalse(IsInvalidWideTextValid);
			}
			*/
		}

		TEST_METHOD(IsInvalidUtf8)
		{
			// the following line should result in the byte sequence 0xC0 0xAF 0x00 but actually is 0xC0 0x80 0x00!
			// const char8_t* OverlongEncoding = u8"\xC0\xAF";
			// (might be the compiler interfering, meaning I cannot simply use that line though!!!)

			// overlong encodings
			constexpr const char8_t OverlongEncoding0[] = { 0xC0, 0xAF };	// 2 bytes
			constexpr const char8_t OverlongEncoding1[] = { 0xE0, 0x80, 0xAF };	// 3 bytes
			constexpr const char8_t OverlongEncoding2[] = { 0xF0, 0x80, 0x80, 0xAF };	// 4 bytes
			constexpr const char8_t OverlongEncoding3[] = { 0xC0, 0xAF };	// 2 byte overlong for '/'
			constexpr const char8_t OverlongEncoding4[] = { 0xE0, 0x80, 0xAF };	// 3 byte overlong for '/'
			constexpr const char8_t OverlongEncoding5[] = { 0xC0, 0x80 };	// 2 byte overlong for NULL
			constexpr const char8_t OverlongEncoding6[] = { 0xE0, 0x80, 0x80 };	// 3 byte overlong for NULL

			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(OverlongEncoding0, CharacterTraits<char8_t>::GetLength(OverlongEncoding0)));
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(OverlongEncoding1, CharacterTraits<char8_t>::GetLength(OverlongEncoding1)));
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(OverlongEncoding2, CharacterTraits<char8_t>::GetLength(OverlongEncoding2)));
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(OverlongEncoding3, CharacterTraits<char8_t>::GetLength(OverlongEncoding3)));
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(OverlongEncoding4, CharacterTraits<char8_t>::GetLength(OverlongEncoding4)));
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(OverlongEncoding5, CharacterTraits<char8_t>::GetLength(OverlongEncoding5)));
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(OverlongEncoding6, CharacterTraits<char8_t>::GetLength(OverlongEncoding6)));

			// incorrectly positioned lead bytes (for instance multiple in a row)
			constexpr const char8_t MulipleLeadBytes0[] = { 0xC2, 0xC2 };	// lead byte implying a single trail bytes
			constexpr const char8_t MulipleLeadBytes1[] = { 0xC0, 0xC0, 0xAF };	// lead byte implying two trail bytes
			constexpr const char8_t MulipleLeadBytes2[] = { 0xE2, 0xE2, 0xA2 };	// lead byte implying three trail bytes
			constexpr const char8_t MulipleLeadBytes3[] = { 0xF0, 0xF0, 0xAF, 0x80 };	// lead byte implying four trail bytes
			constexpr const char8_t MulipleLeadBytes4[] = { 0xF0, 0x90, 0xE2, 0xA2 };	// lead byte in the middle of the sequence

			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(MulipleLeadBytes0, CharacterTraits<char8_t>::GetLength(MulipleLeadBytes0)));
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(MulipleLeadBytes1, CharacterTraits<char8_t>::GetLength(MulipleLeadBytes1)));
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(MulipleLeadBytes2, CharacterTraits<char8_t>::GetLength(MulipleLeadBytes2)));
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(MulipleLeadBytes3, CharacterTraits<char8_t>::GetLength(MulipleLeadBytes3)));
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(MulipleLeadBytes4, CharacterTraits<char8_t>::GetLength(MulipleLeadBytes4)));

			// missing lead byte
			constexpr const char8_t StartingTrailByt0e[] = { 0x80 };
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(StartingTrailByt0e, CharacterTraits<char8_t>::GetLength(StartingTrailByt0e)));

			// missing trail byte
			constexpr const char8_t MissingTrailByte0[] = { 0xC2 };	// needs one trail byte
			constexpr const char8_t MissingTrailByte1[] = { 0xE1, 0x80 };	// needs two trail bytes
			constexpr const char8_t MissingTrailByte2[] = { 0xF0, 0x90, 0x80 };	// needs three trail bytes

			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(MissingTrailByte0, CharacterTraits<char8_t>::GetLength(MissingTrailByte0)));
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(MissingTrailByte1, CharacterTraits<char8_t>::GetLength(MissingTrailByte1)));
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(MissingTrailByte2, CharacterTraits<char8_t>::GetLength(MissingTrailByte2)));

			// truncated sequence/premature ending ("special" form of missing trail byte)
			constexpr const char8_t Truncated0[] = { 0xC2, 0xA2 };	// one trail byte
			constexpr const char8_t Truncated1[] = { 0xE2, 0x82, 0xAC };	// two trail bytes
			constexpr const char8_t Truncated2[] = { 0xF0, 0x9F, 0x92, 0x96 };	// three trail bytes
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(Truncated0, CharacterTraits<char8_t>::GetLength(Truncated0) - sizeof(char8_t)));
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(Truncated1, CharacterTraits<char8_t>::GetLength(Truncated1) - sizeof(char8_t)));
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(Truncated2, CharacterTraits<char8_t>::GetLength(Truncated2) - sizeof(char8_t)));

			// unexpected trail byte
			constexpr const char8_t UnexpectedTrailByte0[] = { 0xE2, 0x82, 0xAC, 0xA0 };
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(UnexpectedTrailByte0, CharacterTraits<char8_t>::GetLength(UnexpectedTrailByte0)));

			// utf-16
			constexpr const char8_t Utf16Surrogates0[] = { 0xD8, 0x00 };	// high-surrogate
			constexpr const char8_t Utf16Surrogates1[] = { 0xD8, 0x00, 0x00, 0x41 };	// two high-surrogates
			constexpr const char8_t Utf16Surrogates2[] = { 0xD8, 0x00, 0x00, 0x41 };	// high-surrogate and non-low surrogate
			constexpr const char8_t Utf16Surrogates3[] = { 0xDC, 0x00 };	// low-surrogate
			constexpr const char8_t Utf16Surrogates4[] = { 0xDC, 0x00, 0xDC, 0x00 };	// two low-surrogates
			constexpr const char8_t Utf16Surrogates5[] = { 0x41, 0xDC, 0x00 };	// valid utf8 and low-surrogate
			constexpr const char8_t Utf16Surrogates6[] = { 0xDC, 0x01, 0xD8, 0x00 };	// low- and high surrogate
			constexpr const char8_t Utf16Surrogates7[] = { 0x01, 0x61, 0xD8, 0x01, 0x01, 0x62 };	// high-surrogate in between valid utf8
			constexpr const char8_t Utf16Surrogates8[] = { 0x01, 0x61, 0xDC, 0x01, 0x01, 0x62 };	// low-surrogate in between valid utf8
			constexpr const char8_t Utf16Surrogates9[] = { 0xD8, 0x34, 0xDD, 0x1E };	// surrogate pair

			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(Utf16Surrogates0, CharacterTraits<char8_t>::GetLength(Utf16Surrogates0)));
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(Utf16Surrogates1, CharacterTraits<char8_t>::GetLength(Utf16Surrogates1)));
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(Utf16Surrogates2, CharacterTraits<char8_t>::GetLength(Utf16Surrogates2)));
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(Utf16Surrogates3, CharacterTraits<char8_t>::GetLength(Utf16Surrogates3)));
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(Utf16Surrogates4, CharacterTraits<char8_t>::GetLength(Utf16Surrogates4)));
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(Utf16Surrogates5, CharacterTraits<char8_t>::GetLength(Utf16Surrogates5)));
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(Utf16Surrogates6, CharacterTraits<char8_t>::GetLength(Utf16Surrogates6)));
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(Utf16Surrogates7, CharacterTraits<char8_t>::GetLength(Utf16Surrogates7)));
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(Utf16Surrogates8, CharacterTraits<char8_t>::GetLength(Utf16Surrogates8)));
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(Utf16Surrogates9, CharacterTraits<char8_t>::GetLength(Utf16Surrogates9)));

			// code-points outside unicode range (>U+10FFFF)
			constexpr const char8_t UndefinedUnicodeCodePoint0[] = { 0xF4, 0x90, 0x80, 0x80 };	// U+110000
			constexpr const char8_t UndefinedUnicodeCodePoint1[] = { 0xF8, 0x88, 0x80, 0x80, 0x80 };	// > 21 bits
			constexpr const char8_t UndefinedUnicodeCodePoint2[] = { 0xFC, 0x80, 0x80, 0x80, 0x80, 0x80 };	// six byte sequence

			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(UndefinedUnicodeCodePoint0, CharacterTraits<char8_t>::GetLength(UndefinedUnicodeCodePoint0)));
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(UndefinedUnicodeCodePoint1, CharacterTraits<char8_t>::GetLength(UndefinedUnicodeCodePoint1)));
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(UndefinedUnicodeCodePoint2, CharacterTraits<char8_t>::GetLength(UndefinedUnicodeCodePoint2)));

			// non-character code-points
			constexpr const char8_t NonCharacters0[] = { 0xEF, 0xB7, 0xAF };	// range of U+FDD0 – U+FDEF
			constexpr const char8_t NonCharacters1[] = { 0xEF, 0xBF, 0xBE };	// ending with 0xFFFE
			constexpr const char8_t NonCharacters2[] = { 0xEF, 0xBF, 0xBF };	// ending with 0xFFFF
			constexpr const char8_t NonCharacters3[] = { 0xF0, 0x9F, 0xBF, 0xBE };	// supplementary plane ending with 0xFFFE
			constexpr const char8_t NonCharacters4[] = { 0xF0, 0x9F, 0xBF, 0xBF };	// supplementary plane ending with 0xFFFF
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(NonCharacters0, CharacterTraits<char8_t>::GetLength(NonCharacters0)));
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(NonCharacters1, CharacterTraits<char8_t>::GetLength(NonCharacters1)));
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(NonCharacters2, CharacterTraits<char8_t>::GetLength(NonCharacters2)));
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(NonCharacters3, CharacterTraits<char8_t>::GetLength(NonCharacters3)));
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(NonCharacters4, CharacterTraits<char8_t>::GetLength(NonCharacters4)));

			// "old" utf-8 (pre-RFC-3629)
			constexpr const char8_t Old0[] = { 0xF5 };	// utf-8 code-point represented by five bytes
			constexpr const char8_t Old1[] = { 0xFF };	// utf-8 code-point represented by six bytes

			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(Old0, CharacterTraits<char8_t>::GetLength(Old0)));
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(Old1, CharacterTraits<char8_t>::GetLength(Old1)));

			// BOM handling	- @ToDo: bom is only valid at the beginning, not in the middle. think about how I want to handle this!
			constexpr const char8_t BOM[] = { 0xEF, 0xBB, 0xBF };
			Assert::IsFalse(CharacterTraits<char8_t>::IsValid(BOM, CharacterTraits<char8_t>::GetLength(BOM)));
		}
	};
}
