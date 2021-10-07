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
			Assert::AreEqual(1_ui8, CharacterTraits<char>::SizePerCharacter);
			Assert::AreEqual(1_ui8, CharacterTraits<signed char>::SizePerCharacter);
			Assert::AreEqual(1_ui8, CharacterTraits<unsigned char>::SizePerCharacter);
			Assert::AreEqual(2_ui8, CharacterTraits<wchar_t>::SizePerCharacter);
			Assert::AreEqual(1_ui8, CharacterTraits<char8_t>::SizePerCharacter);
			Assert::AreEqual(2_ui8, CharacterTraits<char16_t>::SizePerCharacter);
			Assert::AreEqual(4_ui8, CharacterTraits<char32_t>::SizePerCharacter);

			Assert::AreEqual('\0', CharacterTraits<char>::NullTerminationCharacter);
			Assert::AreEqual(static_cast<signed char>('\0'), CharacterTraits<signed char>::NullTerminationCharacter);
			Assert::AreEqual(static_cast<unsigned char>('\0'), CharacterTraits<unsigned char>::NullTerminationCharacter);
			Assert::AreEqual(L'\0', CharacterTraits<wchar_t>::NullTerminationCharacter);
			Assert::AreEqual(u8'\0', CharacterTraits<char8_t>::NullTerminationCharacter);
			//Assert::AreEqual(static_cast<char16_t>('\0'), CharacterTraits<char16_t>::NullTerminationCharacter);
			//Assert::AreEqual(static_cast<char32_t>('\0'), CharacterTraits<char32_t>::NullTerminationCharacter);
		}

		TEST_METHOD(StaticMethods)
		{
			Assert::AreEqual(static_cast<size_t>(0), CharacterTraits<char>::GetLength(nullptr));
			Assert::AreEqual(static_cast<size_t>(0), CharacterTraits<signed char>::GetLength(nullptr));
			Assert::AreEqual(static_cast<size_t>(0), CharacterTraits<unsigned char>::GetLength(nullptr));
			Assert::AreEqual(static_cast<size_t>(0), CharacterTraits<wchar_t>::GetLength(nullptr));
			Assert::AreEqual(static_cast<size_t>(0), CharacterTraits<char8_t>::GetLength(nullptr));
			Assert::AreEqual(static_cast<size_t>(0), CharacterTraits<char16_t>::GetLength(nullptr));
			Assert::AreEqual(static_cast<size_t>(0), CharacterTraits<char32_t>::GetLength(nullptr));

			Assert::AreEqual(static_cast<size_t>(9), CharacterTraits<char>::GetLength("some text"));
			Assert::AreEqual(static_cast<size_t>(9), CharacterTraits<signed char>::GetLength(static_cast<const signed char[10]>("some text")));
			Assert::AreEqual(static_cast<size_t>(9), CharacterTraits<unsigned char>::GetLength(static_cast<const unsigned char[10]>("some text")));
			Assert::AreEqual(static_cast<size_t>(9), CharacterTraits<wchar_t>::GetLength(L"some text"));
			Assert::AreEqual(static_cast<size_t>(9), CharacterTraits<char8_t>::GetLength(u8"some text"));
			//Assert::AreEqual(static_cast<size_t>(9), CharacterTraits<char16_t>::GetLength(static_cast<const char16_t[10]>("some text")));
			//Assert::AreEqual(static_cast<size_t>(9), CharacterTraits<char32_t>::GetLength(static_cast<const char32_t[10]>("some text")));
		}
	};
}
