#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
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
			Assert::AreEqual(static_cast<Elysium::Core::size>(1), CharacterTraits<char>::MinimumByteLength);
			Assert::AreEqual(static_cast<Elysium::Core::size>(2), CharacterTraits<wchar_t>::MinimumByteLength);
			Assert::AreEqual(static_cast<Elysium::Core::size>(1), CharacterTraits<char8_t>::MinimumByteLength);
			Assert::AreEqual(static_cast<Elysium::Core::size>(2), CharacterTraits<char16_t>::MinimumByteLength);
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), CharacterTraits<char32_t>::MinimumByteLength);

			Assert::AreEqual(static_cast<Elysium::Core::size>(1), CharacterTraits<char>::MaximumByteLength);
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), CharacterTraits<wchar_t>::MaximumByteLength);
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), CharacterTraits<char8_t>::MaximumByteLength);
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), CharacterTraits<char16_t>::MaximumByteLength);
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), CharacterTraits<char32_t>::MaximumByteLength);

			Assert::AreEqual('\0', CharacterTraits<char>::NullTerminationCharacter);
			Assert::AreEqual(L'\0', CharacterTraits<wchar_t>::NullTerminationCharacter);
			Assert::AreEqual(u8'\0', CharacterTraits<char8_t>::NullTerminationCharacter);
			Assert::AreEqual(0, static_cast<int>(CharacterTraits<char16_t>::NullTerminationCharacter));
			Assert::AreEqual(0, static_cast<int>(CharacterTraits<char32_t>::NullTerminationCharacter));

			Assert::AreEqual(static_cast<char>(-128), CharacterTraits<char>::MinimumValue);
			Assert::AreEqual(static_cast<wchar_t>(0), CharacterTraits<wchar_t>::MinimumValue);
			Assert::AreEqual(static_cast<char8_t>(0), CharacterTraits<char8_t>::MinimumValue);
			Assert::AreEqual(0, static_cast<int>(CharacterTraits<char16_t>::MinimumValue));
			Assert::AreEqual(0, static_cast<int>(CharacterTraits<char32_t>::MinimumValue));

			Assert::AreEqual(static_cast<char>(127), CharacterTraits<char>::MaximumValue);
			Assert::AreEqual(static_cast<wchar_t>(65535), CharacterTraits<wchar_t>::MaximumValue);
			Assert::AreEqual(static_cast<char8_t>(255), CharacterTraits<char8_t>::MaximumValue);
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
			/*
			// incorrect input!
			Assert::AreEqual(0_ui64, CharacterTraits<char>::GetLength(nullptr));
			Assert::AreEqual(0_ui64, CharacterTraits<char8_t>::GetLength(nullptr));
			Assert::AreEqual(0_ui64, CharacterTraits<char16_t>::GetLength(nullptr));
			Assert::AreEqual(0_ui64, CharacterTraits<char32_t>::GetLength(nullptr));
			Assert::AreEqual(0_ui64, CharacterTraits<wchar_t>::GetLength(nullptr));
			*/
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
	};
}
