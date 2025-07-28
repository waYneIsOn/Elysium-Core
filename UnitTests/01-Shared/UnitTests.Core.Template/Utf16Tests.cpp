#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Literals.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/CharacterTraits.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Utf16.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Template::Text;
using namespace Elysium::Core::Template::Text::Unicode;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Text::Unicode
{
	TEST_CLASS(Utf16Tests)
	{
	public:
		TEST_METHOD(IsInvalid)
		{
			constexpr const char16_t something0[] = { 0xD8, 0x34, 0x00, 0x41, 0x00, 0x00 };

			Assert::IsFalse(Utf16::IsValidLittleEndian(something0, CharacterTraits<char16_t>::GetLength(something0)));
			//Assert::IsFalse(Utf16::IsValidBigEndian(something0, CharacterTraits<char16_t>::GetLength(something0)));
		}

		TEST_METHOD(IsValid)
		{
			// BOM is correct at the start of a file. therefore it should be handled (and possibly stripped) when reading a file.
			// If a BOM occurres within the actual text, it's invalid, meaning the following test is correct!
			Assert::IsTrue(Utf16::IsValidLittleEndian(Utf16::ByteOrderMarkLittleEndian,
				CharacterTraits<char16_t>::GetLength(Utf16::ByteOrderMarkLittleEndian)));
			Assert::IsTrue(Utf16::IsValidLittleEndian(Utf16::ByteOrderMarkLittleEndian,
				CharacterTraits<char16_t>::GetLength(Utf16::ByteOrderMarkLittleEndian)));
		}
	};
}
