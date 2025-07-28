#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Literals.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/CharacterTraits.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Utf8.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Template::Text;
using namespace Elysium::Core::Template::Text::Unicode;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Text::Unicode
{
	TEST_CLASS(Utf8Tests)
	{
	public:
		TEST_METHOD(IsInvalid)
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

			Assert::IsFalse(Utf8::IsValid(OverlongEncoding0, CharacterTraits<char8_t>::GetLength(OverlongEncoding0)));
			Assert::IsFalse(Utf8::IsValid(OverlongEncoding1, CharacterTraits<char8_t>::GetLength(OverlongEncoding1)));
			Assert::IsFalse(Utf8::IsValid(OverlongEncoding2, CharacterTraits<char8_t>::GetLength(OverlongEncoding2)));
			Assert::IsFalse(Utf8::IsValid(OverlongEncoding3, CharacterTraits<char8_t>::GetLength(OverlongEncoding3)));
			Assert::IsFalse(Utf8::IsValid(OverlongEncoding4, CharacterTraits<char8_t>::GetLength(OverlongEncoding4)));
			Assert::IsFalse(Utf8::IsValid(OverlongEncoding5, CharacterTraits<char8_t>::GetLength(OverlongEncoding5)));
			Assert::IsFalse(Utf8::IsValid(OverlongEncoding6, CharacterTraits<char8_t>::GetLength(OverlongEncoding6)));

			// incorrectly positioned lead bytes (for instance multiple in a row)
			constexpr const char8_t MulipleLeadBytes0[] = { 0xC2, 0xC2 };	// lead byte implying a single trail bytes
			constexpr const char8_t MulipleLeadBytes1[] = { 0xC0, 0xC0, 0xAF };	// lead byte implying two trail bytes
			constexpr const char8_t MulipleLeadBytes2[] = { 0xE2, 0xE2, 0xA2 };	// lead byte implying three trail bytes
			constexpr const char8_t MulipleLeadBytes3[] = { 0xF0, 0xF0, 0xAF, 0x80 };	// lead byte implying four trail bytes
			constexpr const char8_t MulipleLeadBytes4[] = { 0xF0, 0x90, 0xE2, 0xA2 };	// lead byte in the middle of the sequence

			Assert::IsFalse(Utf8::IsValid(MulipleLeadBytes0, CharacterTraits<char8_t>::GetLength(MulipleLeadBytes0)));
			Assert::IsFalse(Utf8::IsValid(MulipleLeadBytes1, CharacterTraits<char8_t>::GetLength(MulipleLeadBytes1)));
			Assert::IsFalse(Utf8::IsValid(MulipleLeadBytes2, CharacterTraits<char8_t>::GetLength(MulipleLeadBytes2)));
			Assert::IsFalse(Utf8::IsValid(MulipleLeadBytes3, CharacterTraits<char8_t>::GetLength(MulipleLeadBytes3)));
			Assert::IsFalse(Utf8::IsValid(MulipleLeadBytes4, CharacterTraits<char8_t>::GetLength(MulipleLeadBytes4)));

			// missing lead byte
			constexpr const char8_t StartingTrailByt0e[] = { 0x80 };
			Assert::IsFalse(Utf8::IsValid(StartingTrailByt0e, CharacterTraits<char8_t>::GetLength(StartingTrailByt0e)));

			// missing trail byte
			constexpr const char8_t MissingTrailByte0[] = { 0xC2 };	// needs one trail byte
			constexpr const char8_t MissingTrailByte1[] = { 0xE1, 0x80 };	// needs two trail bytes
			constexpr const char8_t MissingTrailByte2[] = { 0xF0, 0x90, 0x80 };	// needs three trail bytes

			Assert::IsFalse(Utf8::IsValid(MissingTrailByte0, CharacterTraits<char8_t>::GetLength(MissingTrailByte0)));
			Assert::IsFalse(Utf8::IsValid(MissingTrailByte1, CharacterTraits<char8_t>::GetLength(MissingTrailByte1)));
			Assert::IsFalse(Utf8::IsValid(MissingTrailByte2, CharacterTraits<char8_t>::GetLength(MissingTrailByte2)));

			// truncated sequence/premature ending ("special" form of missing trail byte)
			constexpr const char8_t Truncated0[] = { 0xC2, 0xA2 };	// one trail byte
			constexpr const char8_t Truncated1[] = { 0xE2, 0x82, 0xAC };	// two trail bytes
			constexpr const char8_t Truncated2[] = { 0xF0, 0x9F, 0x92, 0x96 };	// three trail bytes
			Assert::IsFalse(Utf8::IsValid(Truncated0, CharacterTraits<char8_t>::GetLength(Truncated0) - sizeof(char8_t)));
			Assert::IsFalse(Utf8::IsValid(Truncated1, CharacterTraits<char8_t>::GetLength(Truncated1) - sizeof(char8_t)));
			Assert::IsFalse(Utf8::IsValid(Truncated2, CharacterTraits<char8_t>::GetLength(Truncated2) - sizeof(char8_t)));

			// unexpected trail byte
			constexpr const char8_t UnexpectedTrailByte0[] = { 0xE2, 0x82, 0xAC, 0xA0 };
			Assert::IsFalse(Utf8::IsValid(UnexpectedTrailByte0, CharacterTraits<char8_t>::GetLength(UnexpectedTrailByte0)));

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

			Assert::IsFalse(Utf8::IsValid(Utf16Surrogates0, CharacterTraits<char8_t>::GetLength(Utf16Surrogates0)));
			Assert::IsFalse(Utf8::IsValid(Utf16Surrogates1, CharacterTraits<char8_t>::GetLength(Utf16Surrogates1)));
			Assert::IsFalse(Utf8::IsValid(Utf16Surrogates2, CharacterTraits<char8_t>::GetLength(Utf16Surrogates2)));
			Assert::IsFalse(Utf8::IsValid(Utf16Surrogates3, CharacterTraits<char8_t>::GetLength(Utf16Surrogates3)));
			Assert::IsFalse(Utf8::IsValid(Utf16Surrogates4, CharacterTraits<char8_t>::GetLength(Utf16Surrogates4)));
			Assert::IsFalse(Utf8::IsValid(Utf16Surrogates5, CharacterTraits<char8_t>::GetLength(Utf16Surrogates5)));
			Assert::IsFalse(Utf8::IsValid(Utf16Surrogates6, CharacterTraits<char8_t>::GetLength(Utf16Surrogates6)));
			Assert::IsFalse(Utf8::IsValid(Utf16Surrogates7, CharacterTraits<char8_t>::GetLength(Utf16Surrogates7)));
			Assert::IsFalse(Utf8::IsValid(Utf16Surrogates8, CharacterTraits<char8_t>::GetLength(Utf16Surrogates8)));
			Assert::IsFalse(Utf8::IsValid(Utf16Surrogates9, CharacterTraits<char8_t>::GetLength(Utf16Surrogates9)));

			// code-points outside unicode range (>U+10FFFF)
			constexpr const char8_t UndefinedUnicodeCodePoint0[] = { 0xF4, 0x90, 0x80, 0x80 };	// U+110000
			constexpr const char8_t UndefinedUnicodeCodePoint1[] = { 0xF8, 0x88, 0x80, 0x80, 0x80 };	// > 21 bits
			constexpr const char8_t UndefinedUnicodeCodePoint2[] = { 0xFC, 0x80, 0x80, 0x80, 0x80, 0x80 };	// six byte sequence

			Assert::IsFalse(Utf8::IsValid(UndefinedUnicodeCodePoint0, CharacterTraits<char8_t>::GetLength(UndefinedUnicodeCodePoint0)));
			Assert::IsFalse(Utf8::IsValid(UndefinedUnicodeCodePoint1, CharacterTraits<char8_t>::GetLength(UndefinedUnicodeCodePoint1)));
			Assert::IsFalse(Utf8::IsValid(UndefinedUnicodeCodePoint2, CharacterTraits<char8_t>::GetLength(UndefinedUnicodeCodePoint2)));

			// non-character code-points
			constexpr const char8_t NonCharacters0[] = { 0xEF, 0xB7, 0xAF };	// range of U+FDD0 – U+FDEF
			constexpr const char8_t NonCharacters1[] = { 0xEF, 0xBF, 0xBE };	// ending with 0xFFFE
			constexpr const char8_t NonCharacters2[] = { 0xEF, 0xBF, 0xBF };	// ending with 0xFFFF
			constexpr const char8_t NonCharacters3[] = { 0xF0, 0x9F, 0xBF, 0xBE };	// supplementary plane ending with 0xFFFE
			constexpr const char8_t NonCharacters4[] = { 0xF0, 0x9F, 0xBF, 0xBF };	// supplementary plane ending with 0xFFFF
			Assert::IsFalse(Utf8::IsValid(NonCharacters0, CharacterTraits<char8_t>::GetLength(NonCharacters0)));
			Assert::IsFalse(Utf8::IsValid(NonCharacters1, CharacterTraits<char8_t>::GetLength(NonCharacters1)));
			Assert::IsFalse(Utf8::IsValid(NonCharacters2, CharacterTraits<char8_t>::GetLength(NonCharacters2)));
			Assert::IsFalse(Utf8::IsValid(NonCharacters3, CharacterTraits<char8_t>::GetLength(NonCharacters3)));
			Assert::IsFalse(Utf8::IsValid(NonCharacters4, CharacterTraits<char8_t>::GetLength(NonCharacters4)));

			// "old" utf-8 (pre-RFC-3629)
			constexpr const char8_t Old0[] = { 0xF5 };	// utf-8 code-point represented by five bytes
			constexpr const char8_t Old1[] = { 0xFF };	// utf-8 code-point represented by six bytes

			Assert::IsFalse(Utf8::IsValid(Old0, CharacterTraits<char8_t>::GetLength(Old0)));
			Assert::IsFalse(Utf8::IsValid(Old1, CharacterTraits<char8_t>::GetLength(Old1)));
		}

		TEST_METHOD(IsValid)
		{
			// BOM is correct at the start of a file. therefore it should be handled (and possibly stripped) when reading a file.
			// If a BOM occurres within the actual text, it's invalid, meaning the following test is correct!
			Assert::IsTrue(Utf8::IsValid(Utf8::ByteOrderMark, CharacterTraits<char8_t>::GetLength(Utf8::ByteOrderMark)));
			Assert::IsTrue(Utf8::IsValid(Utf8::ByteOrderMark, CharacterTraits<char8_t>::GetLength(Utf8::ByteOrderMark)));
		}
	};
}
