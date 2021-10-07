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
			Assert::AreEqual(static_cast<size_t>(1), CharacterTraits<char>::ByteLength);
			Assert::AreEqual(static_cast<size_t>(1), CharacterTraits<signed char>::ByteLength);
			Assert::AreEqual(static_cast<size_t>(1), CharacterTraits<unsigned char>::ByteLength);
			Assert::AreEqual(static_cast<size_t>(2), CharacterTraits<wchar_t>::ByteLength);
			Assert::AreEqual(static_cast<size_t>(1), CharacterTraits<char8_t>::ByteLength);
			Assert::AreEqual(static_cast<size_t>(2), CharacterTraits<char16_t>::ByteLength);
			Assert::AreEqual(static_cast<size_t>(4), CharacterTraits<char32_t>::ByteLength);

			Assert::AreEqual('\0', CharacterTraits<char>::NullTerminationCharacter);
			Assert::AreEqual(static_cast<signed char>('\0'), CharacterTraits<signed char>::NullTerminationCharacter);
			Assert::AreEqual(static_cast<unsigned char>('\0'), CharacterTraits<unsigned char>::NullTerminationCharacter);
			Assert::AreEqual(L'\0', CharacterTraits<wchar_t>::NullTerminationCharacter);
			Assert::AreEqual(u8'\0', CharacterTraits<char8_t>::NullTerminationCharacter);
			//Assert::AreEqual(static_cast<char16_t>('\0'), CharacterTraits<char16_t>::NullTerminationCharacter);
			//Assert::AreEqual(static_cast<char32_t>('\0'), CharacterTraits<char32_t>::NullTerminationCharacter);

			Assert::AreEqual(static_cast<char>(0), CharacterTraits<char>::MinValue);
			Assert::AreEqual(static_cast<signed char>(-128), CharacterTraits<signed char>::MinValue);
			Assert::AreEqual(static_cast<unsigned char>(0), CharacterTraits<unsigned char>::MinValue);
			Assert::AreEqual(static_cast<wchar_t>(0), CharacterTraits<wchar_t>::MinValue);
			Assert::AreEqual(static_cast<char8_t>(0), CharacterTraits<char8_t>::MinValue);
			//Assert::AreEqual(static_cast<char16_t>(0), CharacterTraits<char16_t>::MinValue);
			//Assert::AreEqual(static_cast<char32_t>(0), CharacterTraits<char32_t>::MinValue);

			Assert::AreEqual(static_cast<char>(255), CharacterTraits<char>::MaxValue);
			Assert::AreEqual(static_cast<signed char>(127), CharacterTraits<signed char>::MaxValue);
			Assert::AreEqual(static_cast<unsigned char>(255), CharacterTraits<unsigned char>::MaxValue);
			Assert::AreEqual(static_cast<wchar_t>(65535), CharacterTraits<wchar_t>::MaxValue);
			Assert::AreEqual(static_cast<char8_t>(255), CharacterTraits<char8_t>::MaxValue);
			//Assert::AreEqual(static_cast<char16_t>(65536), CharacterTraits<char16_t>::MinValue);
			//Assert::AreEqual(static_cast<char32_t>(4294967295), CharacterTraits<char32_t>::MinValue);
		}

		TEST_METHOD(StaticMethods)
		{
			for (size_t i = 0; i < 0x20; i++)
			{
				Assert::IsTrue(CharacterTraits<char>::IsControl(i));
				Assert::IsTrue(CharacterTraits<signed char>::IsControl(i));
				Assert::IsTrue(CharacterTraits<unsigned char>::IsControl(i));
				Assert::IsTrue(CharacterTraits<wchar_t>::IsControl(i));
				Assert::IsTrue(CharacterTraits<char8_t>::IsControl(i));
				Assert::IsTrue(CharacterTraits<char16_t>::IsControl(i));
				Assert::IsTrue(CharacterTraits<char32_t>::IsControl(i));
			}
			for (size_t i = 0x20; i < 0x7F; i++)
			{
				Assert::IsFalse(CharacterTraits<char>::IsControl(i));
				Assert::IsFalse(CharacterTraits<signed char>::IsControl(i));
				Assert::IsFalse(CharacterTraits<unsigned char>::IsControl(i));
				Assert::IsFalse(CharacterTraits<wchar_t>::IsControl(i));
				Assert::IsFalse(CharacterTraits<char8_t>::IsControl(i));
				Assert::IsFalse(CharacterTraits<char16_t>::IsControl(i));
				Assert::IsFalse(CharacterTraits<char32_t>::IsControl(i));
			}
			for (size_t i = 0x7F; i < 0xA0; i++)
			{
				Assert::IsTrue(CharacterTraits<char>::IsControl(i));
				Assert::IsTrue(CharacterTraits<signed char>::IsControl(i));
				Assert::IsTrue(CharacterTraits<unsigned char>::IsControl(i));
				Assert::IsTrue(CharacterTraits<wchar_t>::IsControl(i));
				Assert::IsTrue(CharacterTraits<char8_t>::IsControl(i));
				Assert::IsTrue(CharacterTraits<char16_t>::IsControl(i));
				Assert::IsTrue(CharacterTraits<char32_t>::IsControl(i));
			}
			for (size_t i = 0xA0; i <= 0xFF; i++)
			{
				//Assert::IsFalse(CharacterTraits<char>::IsControl(i));
				//Assert::IsFalse(CharacterTraits<signed char>::IsControl(i));
				Assert::IsFalse(CharacterTraits<unsigned char>::IsControl(i));
				Assert::IsFalse(CharacterTraits<wchar_t>::IsControl(i));
				Assert::IsFalse(CharacterTraits<char8_t>::IsControl(i));
				Assert::IsFalse(CharacterTraits<char16_t>::IsControl(i));
				Assert::IsFalse(CharacterTraits<char32_t>::IsControl(i));
			}
		}

		TEST_METHOD(StaticMethodsChar)
		{
			Assert::Fail();
		}

		TEST_METHOD(StaticMethodsSignedChar)
		{
			Assert::Fail();
		}

		TEST_METHOD(StaticMethodsUnsignedChar)
		{
			Assert::Fail();
		}

		TEST_METHOD(StaticMethodsWideChar)
		{
			Assert::Fail();
		}

		TEST_METHOD(StaticMethodsUtf8Char)
		{
			Assert::Fail();
		}

		TEST_METHOD(StaticMethodsUtf16Char)
		{
			Assert::Fail();
		}

		TEST_METHOD(StaticMethodsUtf32Char)
		{
			Assert::Fail();
		}
	};
}
