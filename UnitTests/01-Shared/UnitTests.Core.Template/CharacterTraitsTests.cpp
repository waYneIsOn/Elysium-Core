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
			Assert::AreEqual(static_cast<Elysium::Core::size>(1), CharacterTraits<signed char>::MinimumByteLength);
			Assert::AreEqual(static_cast<Elysium::Core::size>(1), CharacterTraits<unsigned char>::MinimumByteLength);
			Assert::AreEqual(static_cast<Elysium::Core::size>(2), CharacterTraits<wchar_t>::MinimumByteLength);
			Assert::AreEqual(static_cast<Elysium::Core::size>(1), CharacterTraits<char8_t>::MinimumByteLength);
			Assert::AreEqual(static_cast<Elysium::Core::size>(2), CharacterTraits<char16_t>::MinimumByteLength);
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), CharacterTraits<char32_t>::MinimumByteLength);

			Assert::AreEqual(static_cast<Elysium::Core::size>(1), CharacterTraits<char>::MaximumByteLength);
			Assert::AreEqual(static_cast<Elysium::Core::size>(1), CharacterTraits<signed char>::MaximumByteLength);
			Assert::AreEqual(static_cast<Elysium::Core::size>(1), CharacterTraits<unsigned char>::MaximumByteLength);
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), CharacterTraits<wchar_t>::MaximumByteLength);
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), CharacterTraits<char8_t>::MaximumByteLength);
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), CharacterTraits<char16_t>::MaximumByteLength);
			Assert::AreEqual(static_cast<Elysium::Core::size>(4), CharacterTraits<char32_t>::MaximumByteLength);

			Assert::AreEqual('\0', CharacterTraits<char>::NullTerminationCharacter);
			Assert::AreEqual(static_cast<signed char>('\0'), CharacterTraits<signed char>::NullTerminationCharacter);
			Assert::AreEqual(static_cast<unsigned char>('\0'), CharacterTraits<unsigned char>::NullTerminationCharacter);
			Assert::AreEqual(L'\0', CharacterTraits<wchar_t>::NullTerminationCharacter);
			Assert::AreEqual(u8'\0', CharacterTraits<char8_t>::NullTerminationCharacter);
			Assert::AreEqual(0, static_cast<int>(CharacterTraits<char16_t>::NullTerminationCharacter));
			Assert::AreEqual(0, static_cast<int>(CharacterTraits<char32_t>::NullTerminationCharacter));

			Assert::AreEqual(static_cast<char>(-128), CharacterTraits<char>::MinimumValue);
			Assert::AreEqual(static_cast<signed char>(-128), CharacterTraits<signed char>::MinimumValue);
			Assert::AreEqual(static_cast<unsigned char>(0), CharacterTraits<unsigned char>::MinimumValue);
			Assert::AreEqual(static_cast<wchar_t>(0), CharacterTraits<wchar_t>::MinimumValue);
			Assert::AreEqual(static_cast<char8_t>(0), CharacterTraits<char8_t>::MinimumValue);
			Assert::AreEqual(0, static_cast<int>(CharacterTraits<char16_t>::MinimumValue));
			Assert::AreEqual(0, static_cast<int>(CharacterTraits<char32_t>::MinimumValue));

			Assert::AreEqual(static_cast<char>(127), CharacterTraits<char>::MaximumValue);
			Assert::AreEqual(static_cast<signed char>(127), CharacterTraits<signed char>::MaximumValue);
			Assert::AreEqual(static_cast<unsigned char>(255), CharacterTraits<unsigned char>::MaximumValue);
			Assert::AreEqual(static_cast<wchar_t>(65535), CharacterTraits<wchar_t>::MaximumValue);
			Assert::AreEqual(static_cast<char8_t>(255), CharacterTraits<char8_t>::MaximumValue);
			Assert::AreEqual(65535, static_cast<int>(CharacterTraits<char16_t>::MaximumValue));
			Assert::AreEqual(4294967295u, static_cast<unsigned int>(CharacterTraits<char32_t>::MaximumValue));
		}

		TEST_METHOD(IsControlChar)
		{
			for (Elysium::Core::size i = 0; i < 0x20; i++)
			{
				Assert::IsTrue(CharacterTraits<char>::IsControl(static_cast<char>(i)));
			}
			for (Elysium::Core::size i = 0x20; i < 0x7F; i++)
			{
				Assert::IsFalse(CharacterTraits<char>::IsControl(static_cast<char>(i)));
			}
			Assert::IsTrue(CharacterTraits<char>::IsControl(0x7F));
			for (Elysium::Core::size i = 0x80; i <= 0xFF; i++)
			{
				Assert::IsFalse(CharacterTraits<char>::IsControl(static_cast<char>(i)));
			}
		}

		TEST_METHOD(IsControlSignedChar)
		{
			for (Elysium::Core::size i = 0; i < 0x20; i++)
			{
				Assert::IsTrue(CharacterTraits<signed char>::IsControl(static_cast<signed char>(i)));
			}
			for (Elysium::Core::size i = 0x20; i < 0x7F; i++)
			{
				Assert::IsFalse(CharacterTraits<signed char>::IsControl(static_cast<signed char>(i)));
			}
			Assert::IsTrue(CharacterTraits<char>::IsControl(0x7F));
			for (Elysium::Core::size i = 0x80; i <= 0xFF; i++)
			{
				Assert::IsFalse(CharacterTraits<signed char>::IsControl(static_cast<signed char>(i)));
			}
		}

		TEST_METHOD(IsControlUnsignedChar)
		{
			for (Elysium::Core::size i = 0; i < 0x20; i++)
			{
				Assert::IsTrue(CharacterTraits<unsigned char>::IsControl(static_cast<unsigned char>(i)));
			}
			for (Elysium::Core::size i = 0x20; i < 0x7F; i++)
			{
				Assert::IsFalse(CharacterTraits<unsigned char>::IsControl(static_cast<unsigned char>(i)));
			}
			for (Elysium::Core::size i = 0x7F; i < 0xA0; i++)
			{
				Assert::IsTrue(CharacterTraits<unsigned char>::IsControl(static_cast<unsigned char>(i)));
			}
			for (Elysium::Core::size i = 0xA0; i <= 0xFF; i++)
			{
				Assert::IsFalse(CharacterTraits<unsigned char>::IsControl(static_cast<unsigned char>(i)));
			}
		}

		TEST_METHOD(IsControlWideChar)
		{
			for (Elysium::Core::size i = 0; i < 0x20; i++)
			{
				Assert::IsTrue(CharacterTraits<wchar_t>::IsControl(static_cast<wchar_t>(i)));
			}
			for (Elysium::Core::size i = 0x20; i < 0x7F; i++)
			{
				Assert::IsFalse(CharacterTraits<wchar_t>::IsControl(static_cast<wchar_t>(i)));
			}
			for (Elysium::Core::size i = 0x7F; i < 0xA0; i++)
			{
				Assert::IsTrue(CharacterTraits<wchar_t>::IsControl(static_cast<wchar_t>(i)));
			}
			for (Elysium::Core::size i = 0xA0; i <= 0xFF; i++)
			{
				Assert::IsFalse(CharacterTraits<wchar_t>::IsControl(static_cast<wchar_t>(i)));
			}
		}

		TEST_METHOD(IsControlUtf8Char)
		{
			for (Elysium::Core::size i = 0; i < 0x20; i++)
			{
				Assert::IsTrue(CharacterTraits<char8_t>::IsControl(static_cast<char8_t>(i)));
			}
			for (Elysium::Core::size i = 0x20; i < 0x7F; i++)
			{
				Assert::IsFalse(CharacterTraits<char8_t>::IsControl(static_cast<char8_t>(i)));
			}
			for (Elysium::Core::size i = 0x7F; i < 0xA0; i++)
			{
				Assert::IsTrue(CharacterTraits<char8_t>::IsControl(static_cast<char8_t>(i)));
			}
			for (Elysium::Core::size i = 0xA0; i <= 0xFF; i++)
			{
				Assert::IsFalse(CharacterTraits<char8_t>::IsControl(static_cast<char8_t>(i)));
			}
		}

		TEST_METHOD(IsControlUtf16Char)
		{
			for (Elysium::Core::size i = 0; i < 0x20; i++)
			{
				Assert::IsTrue(CharacterTraits<char16_t>::IsControl(static_cast<char16_t>(i)));
			}
			for (Elysium::Core::size i = 0x20; i < 0x7F; i++)
			{
				Assert::IsFalse(CharacterTraits<char16_t>::IsControl(static_cast<char16_t>(i)));
			}
			for (Elysium::Core::size i = 0x7F; i < 0xA0; i++)
			{
				Assert::IsTrue(CharacterTraits<char16_t>::IsControl(static_cast<char16_t>(i)));
			}
			for (Elysium::Core::size i = 0xA0; i <= 0xFF; i++)
			{
				Assert::IsFalse(CharacterTraits<char16_t>::IsControl(static_cast<char16_t>(i)));
			}
		}

		TEST_METHOD(IsControlUtf32Char)
		{
			for (Elysium::Core::size i = 0; i < 0x20; i++)
			{
				Assert::IsTrue(CharacterTraits<char32_t>::IsControl(static_cast<char32_t>(i)));
			}
			for (Elysium::Core::size i = 0x20; i < 0x7F; i++)
			{
				Assert::IsFalse(CharacterTraits<char32_t>::IsControl(static_cast<char32_t>(i)));
			}
			for (Elysium::Core::size i = 0x7F; i < 0xA0; i++)
			{
				Assert::IsTrue(CharacterTraits<char32_t>::IsControl(static_cast<char32_t>(i)));
			}
			for (Elysium::Core::size i = 0xA0; i <= 0xFF; i++)
			{
				Assert::IsFalse(CharacterTraits<char32_t>::IsControl(static_cast<char32_t>(i)));
			}
		}

		TEST_METHOD(IsDigitChar)
		{
			for (Elysium::Core::size i = 0x00; i < 0x30; i++)
			{
				Assert::IsFalse(CharacterTraits<char>::IsDigit(static_cast<char>(i)));
			}
			for (Elysium::Core::size i = 0x30; i < 0x3A; i++)
			{
				Assert::IsTrue(CharacterTraits<char>::IsDigit(static_cast<char>(i)));
			}
			for (Elysium::Core::size i = 0x3A; i <= 0xFF; i++)
			{
				Assert::IsFalse(CharacterTraits<char>::IsDigit(static_cast<char>(i)));
			}
		}

		TEST_METHOD(IsDigitSignedChar)
		{
			for (Elysium::Core::size i = 0x00; i < 0x30; i++)
			{
				Assert::IsFalse(CharacterTraits<signed char>::IsDigit(static_cast<signed char>(i)));
			}
			for (Elysium::Core::size i = 0x30; i < 0x3A; i++)
			{
				Assert::IsTrue(CharacterTraits<signed char>::IsDigit(static_cast<signed char>(i)));
			}
			for (Elysium::Core::size i = 0x3A; i <= 0xFF; i++)
			{
				Assert::IsFalse(CharacterTraits<signed char>::IsDigit(static_cast<signed char>(i)));
			}
		}

		TEST_METHOD(IsDigitUnsignedChar)
		{
			for (Elysium::Core::size i = 0x00; i < 0x30; i++)
			{
				Assert::IsFalse(CharacterTraits<unsigned char>::IsDigit(static_cast<unsigned char>(i)));
			}
			for (Elysium::Core::size i = 0x30; i < 0x3A; i++)
			{
				Assert::IsTrue(CharacterTraits<unsigned char>::IsDigit(static_cast<unsigned char>(i)));
			}
			for (Elysium::Core::size i = 0x3A; i <= 0xFF; i++)
			{
				Assert::IsFalse(CharacterTraits<unsigned char>::IsDigit(static_cast<unsigned char>(i)));
			}
		}

		TEST_METHOD(IsDigitWideChar)
		{
			Assert::Fail();
		}

		TEST_METHOD(IsDigitUtf8Char)
		{
			Assert::Fail();
		}

		TEST_METHOD(IsDigitUtf16Char)
		{
			Assert::Fail();
		}

		TEST_METHOD(IsDigitUtf32Char)
		{
			for (Elysium::Core::size i = 0x00; i < 0x30; i++)
			{
				Assert::IsFalse(CharacterTraits<char32_t>::IsDigit(static_cast<char32_t>(i)));
			}
			for (Elysium::Core::size i = 0x30; i < 0x3A; i++)
			{
				Assert::IsTrue(CharacterTraits<char32_t>::IsDigit(static_cast<char32_t>(i)));
			}
			for (Elysium::Core::size i = 0x3A; i <= 0xFF; i++)
			{
				Assert::IsFalse(CharacterTraits<char32_t>::IsDigit(static_cast<char32_t>(i)));
			}
			// ToDo: other values
		}
	};
}
