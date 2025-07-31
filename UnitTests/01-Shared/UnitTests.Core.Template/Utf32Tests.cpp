#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Literals.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/CharacterTraits.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Text/Unicode/Utf32.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Template::Text;
using namespace Elysium::Core::Template::Text::Unicode;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Text::Unicode
{
	TEST_CLASS(Utf32Tests)
	{
	public:
		TEST_METHOD(IsInvalid)
		{
			// invalid codepoints
			constexpr const char32_t Invalid0[] = { 0x00110000, 0x00000000 };
			Assert::IsFalse(Utf32::IsValid(Invalid0, CharacterTraits<char32_t>::GetLength(Invalid0)));
			
			// utf-16 surrogates
			constexpr const char32_t Utf16HighSurrogate[] = { 0x0000D800, 0x00000000 };
			constexpr const char32_t Utf16LowSurrogate[] = { 0x0000DFFF, 0x00000000 };
			constexpr const char32_t Utf16SurrogatePair[] = { 0x0000D800, 0x0000DFFF, 0x00000000 };
			Assert::IsFalse(Utf32::IsValid(Utf16HighSurrogate, CharacterTraits<char32_t>::GetLength(Utf16HighSurrogate)));
			Assert::IsFalse(Utf32::IsValid(Utf16LowSurrogate, CharacterTraits<char32_t>::GetLength(Utf16LowSurrogate)));
			Assert::IsFalse(Utf32::IsValid(Utf16SurrogatePair, CharacterTraits<char32_t>::GetLength(Utf16SurrogatePair)));
		}

		TEST_METHOD(IsValid)
		{
			// empty
			constexpr const char32_t* NonEmpty = U"some text";
			Assert::IsTrue(Utf32::IsValid(NonEmpty, CharacterTraits<char32_t>::GetLength(NonEmpty)));
			Assert::IsTrue(Utf32::IsValid(NonEmpty, 0));

			// null
			Assert::IsTrue(Utf32::IsValid(nullptr, 0));
			Assert::IsTrue(Utf32::IsValid(nullptr, 123));

			// BOM
			constexpr const Elysium::Core::Template::System::size BOMLELength =
				CharacterTraits<char32_t>::GetLength(Utf32::ByteOrderMarkLittleEndian);
			constexpr const Elysium::Core::Template::System::size BOMBELength =
				CharacterTraits<char32_t>::GetLength(Utf32::ByteOrderMarkBigEndian);
			Assert::AreEqual(2_ui64, BOMLELength);
			Assert::AreEqual(0_ui64, BOMBELength);

			Assert::IsTrue(Utf32::IsValid(Utf32::ByteOrderMarkLittleEndian, BOMLELength));
			Assert::IsTrue(Utf32::IsValid(Utf32::ByteOrderMarkBigEndian, BOMBELength));
		}

		TEST_METHOD(IsSuspicious)
		{
			/*
			// non-character codepoints
			// @ToDo: technically valid but suspicious
			constexpr const char32_t NonCharacter0[] = { 0x0000FFFF, 0x00000000 };
			Assert::IsFalse(Utf32::IsValid(NonCharacter0, CharacterTraits<char32_t>::GetLength(NonCharacter0)));
			
			// BOM
			// @ToDo: BOM in the middle of an utf-32 string is valid but suspicious, so think about whether I want to handle it!
			constexpr const Elysium::Core::Template::System::size BOMLELength =
				CharacterTraits<char32_t>::GetLength(Utf32::ByteOrderMarkLittleEndian);
			constexpr const Elysium::Core::Template::System::size BOMBELength =
				CharacterTraits<char32_t>::GetLength(Utf32::ByteOrderMarkBigEndian);
			Assert::AreEqual(2_ui64, BOMLELength);
			Assert::AreEqual(2_ui64, BOMBELength);

			Assert::IsTrue(Utf32::IsValid(Utf32::ByteOrderMarkLittleEndian, BOMLELength));
			Assert::IsTrue(Utf32::IsValid(Utf32::ByteOrderMarkBigEndian, BOMBELength));
			*/
		}
	};
}
