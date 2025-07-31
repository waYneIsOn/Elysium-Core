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
			// missing surrogates
			constexpr const char16_t Unpaired0[] = { 0xD800, 0x0000 };	// missing low-surrogate
			constexpr const char16_t Unpaired1[] = { 0xDC00, 0x0000 };	// missing high-surrogate
			Assert::IsFalse(Utf16::IsValid(Unpaired0, CharacterTraits<char16_t>::GetLength(Unpaired0)));
			Assert::IsFalse(Utf16::IsValid(Unpaired1, CharacterTraits<char16_t>::GetLength(Unpaired1)));

			// swapped surrogates
			constexpr const char16_t SwappedSurrogates0[] = { 0xDC00, 0xD800, 0x0000 };	// low- then high-surrogate
			Assert::IsFalse(Utf16::IsValid(SwappedSurrogates0, CharacterTraits<char16_t>::GetLength(SwappedSurrogates0)));

			// mixed in surrogates
			constexpr const char16_t MixedIn0[] = { u'H', 0xD800, u'i', 0xDC00, u'!', 0x0000 };
			Assert::IsFalse(Utf16::IsValid(MixedIn0, CharacterTraits<char16_t>::GetLength(MixedIn0)));

			// low surrogates
			constexpr const char16_t LowSurrogates0[] = { 0xDC01, u'B', 0x0000 };	// low-surrogate at the start
			constexpr const char16_t LowSurrogates1[] = { 0xD800, 0x0061, 0x0000 };	// invalid low-surrogate
			Assert::IsFalse(Utf16::IsValid(LowSurrogates0, CharacterTraits<char16_t>::GetLength(LowSurrogates0)));
			Assert::IsFalse(Utf16::IsValid(LowSurrogates1, CharacterTraits<char16_t>::GetLength(LowSurrogates1)));

			// truncated sequence/premature ending ("special" form of missing low-surrogate)
			constexpr const char16_t Truncated0[] = { u'A', 0xD801, 0x0000 };
			constexpr const char16_t Truncated1[] = { u'X', 0xD83D, 0x0000 };
			Assert::IsFalse(Utf16::IsValid(Truncated0, CharacterTraits<char16_t>::GetLength(Truncated0)));
			Assert::IsFalse(Utf16::IsValid(Truncated1, CharacterTraits<char16_t>::GetLength(Truncated1)));
		}

		TEST_METHOD(IsValid)
		{
			// empty
			constexpr const char16_t* NonEmpty = u"some text";
			Assert::IsTrue(Utf16::IsValid(NonEmpty, CharacterTraits<char16_t>::GetLength(NonEmpty)));
			Assert::IsTrue(Utf16::IsValid(NonEmpty, 0));

			// null
			Assert::IsTrue(Utf16::IsValid(nullptr, 0));
			Assert::IsTrue(Utf16::IsValid(nullptr, 123));
			
			// BOM
			constexpr const Elysium::Core::Template::System::size BOMLELength =
				CharacterTraits<char16_t>::GetLength(Utf16::ByteOrderMarkLittleEndian);
			constexpr const Elysium::Core::Template::System::size BOMBELength =
				CharacterTraits<char16_t>::GetLength(Utf16::ByteOrderMarkBigEndian);
			Assert::AreEqual(2_ui64, BOMLELength);
			Assert::AreEqual(2_ui64, BOMBELength);

			Assert::IsTrue(Utf16::IsValid(Utf16::ByteOrderMarkLittleEndian, BOMLELength));
			Assert::IsTrue(Utf16::IsValid(Utf16::ByteOrderMarkBigEndian, BOMBELength));
		}

		TEST_METHOD(IsSuspicious)
		{
			/*
			// bmp (basic multilingual plane)
			// all of these are technically valid but discouraged/suspicious
			// @ToDo: think about how I want to handle those cases!
			constexpr const char16_t BMP0[] = { 0xFDD0, 0x0000 };	// non-character range start
			constexpr const char16_t BMP1[] = { 0xFDEF, 0x0000 };	// non-character range end
			constexpr const char16_t BMP2[] = { 0xFFFE, 0x0000 };	// non-character other range start
			constexpr const char16_t BMP3[] = { 0xFFFF, 0x0000 };	// non-character other range end
			Assert::IsFalse(Utf16::IsValid(BMP0, CharacterTraits<char16_t>::GetLength(BMP0)));
			Assert::IsFalse(Utf16::IsValid(BMP1, CharacterTraits<char16_t>::GetLength(BMP1)));
			Assert::IsFalse(Utf16::IsValid(BMP2, CharacterTraits<char16_t>::GetLength(BMP2)));
			Assert::IsFalse(Utf16::IsValid(BMP3, CharacterTraits<char16_t>::GetLength(BMP3)));

			// BOM
			// @ToDo: BOM in the middle of an utf-16 string is valid but suspicious, so think about whether I want to handle it!
			constexpr const Elysium::Core::Template::System::size BOMLELength =
				CharacterTraits<char16_t>::GetLength(Utf16::ByteOrderMarkLittleEndian);
			constexpr const Elysium::Core::Template::System::size BOMBELength =
				CharacterTraits<char16_t>::GetLength(Utf16::ByteOrderMarkBigEndian);
			Assert::AreEqual(2_ui64, BOMLELength);
			Assert::AreEqual(2_ui64, BOMBELength);

			Assert::IsTrue(Utf16::IsValid(Utf16::ByteOrderMarkLittleEndian, BOMLELength));
			Assert::IsTrue(Utf16::IsValid(Utf16::ByteOrderMarkBigEndian, BOMBELength));
			*/
		}
	};
}
