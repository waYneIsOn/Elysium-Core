/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UNICODERANGES
#define ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UNICODERANGES

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_UNICODECHARACTER
#include "UnicodeCharacter.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UNICODERANGE
#include "UnicodeRange.hpp"
#endif

namespace Elysium::Core::Template::Text::Unicode
{
	template <Concepts::UnicodeCharacter UC>
	class UnicodeRanges
	{
	public:
		constexpr UnicodeRanges() noexcept = delete;

		constexpr UnicodeRanges(const UnicodeRange<UC>& Source) = delete;

		constexpr UnicodeRanges(UnicodeRange<UC>&& Right) noexcept = delete;

		constexpr ~UnicodeRanges() = delete;
	public:
		UnicodeRanges& operator=(const UnicodeRanges& Source) = delete;

		UnicodeRanges& operator=(UnicodeRanges&& Right) noexcept = delete;
	public:
		inline static constexpr const UnicodeRange<UC> All = UnicodeRange<UC>(0x0000, 0x10FFFF);

		inline static constexpr const UnicodeRange<UC> AlphabeticPresentationForms = UnicodeRange<UC>(0xFB00, 0xFB4F);

		inline static constexpr const UnicodeRange<UC> Arabic = UnicodeRange<UC>(0x0600, 0x06FF);

		inline static constexpr const UnicodeRange<UC> ArabicExtendedA = UnicodeRange<UC>(0x08A0, 0x08FF);

		inline static constexpr const UnicodeRange<UC> ArabicExtendedB = UnicodeRange<UC>(0x0870, 0x089F);

		inline static constexpr const UnicodeRange<UC> ArabicPresentationFormsA = UnicodeRange<UC>(0xFB50, 0xFDFF);

		inline static constexpr const UnicodeRange<UC> ArabicPresentationFormsB = UnicodeRange<UC>(0xFE70, 0xFEFF);

		inline static constexpr const UnicodeRange<UC> ArabicSupplement = UnicodeRange<UC>(0x0750, 0x077F);

		inline static constexpr const UnicodeRange<UC> Armenian = UnicodeRange<UC>(0x0530, 0x058F);

		inline static constexpr const UnicodeRange<UC> Arrows = UnicodeRange<UC>(0x2190, 0x21FF);

		inline static constexpr const UnicodeRange<UC> Balinese = UnicodeRange<UC>(0x1B00, 0x1B7F);

		//inline static constexpr const UnicodeRange<UC> Bamum = UnicodeRange<UC>(0x1B00, 0x1B7F);	// same as Balinese

		inline static constexpr const UnicodeRange<UC> BasicLatin = UnicodeRange<UC>(0x0021, 0x007F);

		inline static constexpr const UnicodeRange<UC> Batak = UnicodeRange<UC>(0x1BC0, 0x1BFF);

		inline static constexpr const UnicodeRange<UC> Bengali = UnicodeRange<UC>(0x0980, 0x09FF);

		inline static constexpr const UnicodeRange<UC> BlockElements = UnicodeRange<UC>(0x2580, 0x259F);

		inline static constexpr const UnicodeRange<UC> Bopomofo = UnicodeRange<UC>(0x3100, 0x312F);

		inline static constexpr const UnicodeRange<UC> BopomofoExtended = UnicodeRange<UC>(0x31A0, 0x31BF);

		inline static constexpr const UnicodeRange<UC> BoxDrawing = UnicodeRange<UC>(0x2500, 0x257F);

		inline static constexpr const UnicodeRange<UC> BraillePatterns = UnicodeRange<UC>(0x2800, 0x28FF);

		inline static constexpr const UnicodeRange<UC> Buginese = UnicodeRange<UC>(0x1A00, 0x1A1F);

		inline static constexpr const UnicodeRange<UC> Buhid = UnicodeRange<UC>(0x1740, 0x175F);

		inline static constexpr const UnicodeRange<UC> Cham = UnicodeRange<UC>(0xAA00, 0xAA5F);

		inline static constexpr const UnicodeRange<UC> Cherokee = UnicodeRange<UC>(0x13A0, 0x13FF);

		inline static constexpr const UnicodeRange<UC> CherokeeSupplement = UnicodeRange<UC>(0xAB70, 0xABBF);

		inline static constexpr const UnicodeRange<UC> CjkCompatibility = UnicodeRange<UC>(0x3300, 0x33FF);

		inline static constexpr const UnicodeRange<UC> CjkCompatibilityForms = UnicodeRange<UC>(0xFE30, 0xFE4F);

		inline static constexpr const UnicodeRange<UC> CjkCompatibilityIdeographs = UnicodeRange<UC>(0xF900, 0xFAD9);

		inline static constexpr const UnicodeRange<UC> CjkRadicalsSupplement = UnicodeRange<UC>(0x2E80, 0x2EFF);

		inline static constexpr const UnicodeRange<UC> CjkStrokes = UnicodeRange<UC>(0x31C0, 0x31EF);

		inline static constexpr const UnicodeRange<UC> CjkSymbolsandPunctuation = UnicodeRange<UC>(0x3000, 0x303F);

		inline static constexpr const UnicodeRange<UC> CjkUnifiedIdeographs = UnicodeRange<UC>(0x4E00, 0x9FCC);

		inline static constexpr const UnicodeRange<UC> CjkUnifiedIdeographsExtensionA = UnicodeRange<UC>(0x3400, 0x4DB5);

		inline static constexpr const UnicodeRange<UC> CombiningDiacriticalMarks = UnicodeRange<UC>(0x0300, 0x036F);

		inline static constexpr const UnicodeRange<UC> CombiningDiacriticalMarksExtended = UnicodeRange<UC>(0x1AB0, 0x1AFF);

		inline static constexpr const UnicodeRange<UC> CombiningDiacriticalMarksforSymbols = UnicodeRange<UC>(0x20D0, 0x20FF);

		inline static constexpr const UnicodeRange<UC> CombiningDiacriticalMarksSupplement = UnicodeRange<UC>(0x1DC0, 0x1DFF);

		inline static constexpr const UnicodeRange<UC> CombiningHalfMarks = UnicodeRange<UC>(0xFE20, 0xFE2F);

		inline static constexpr const UnicodeRange<UC> CommonIndicNumberForms = UnicodeRange<UC>(0xA830, 0xA83F);

		inline static constexpr const UnicodeRange<UC> ControlPictures = UnicodeRange<UC>(0x2400, 0x243F);

		inline static constexpr const UnicodeRange<UC> Coptic = UnicodeRange<UC>(0x2C80, 0x2CFF);

		inline static constexpr const UnicodeRange<UC> CurrencySymbols = UnicodeRange<UC>(0x20A0, 0x20CF);

		inline static constexpr const UnicodeRange<UC> Cyrillic = UnicodeRange<UC>(0x0400, 0x04FF);

		inline static constexpr const UnicodeRange<UC> CyrillicExtendedA = UnicodeRange<UC>(0x2DE0, 0x2DFF);

		inline static constexpr const UnicodeRange<UC> CyrillicExtendedB = UnicodeRange<UC>(0xA640, 0xA69F);

		inline static constexpr const UnicodeRange<UC> CyrillicExtendedC = UnicodeRange<UC>(0x1C80, 0x1C8F);

		inline static constexpr const UnicodeRange<UC> CyrillicSupplement = UnicodeRange<UC>(0x0500, 0x052F);

		inline static constexpr const UnicodeRange<UC> Devanagari = UnicodeRange<UC>(0x0900, 0x097F);

		inline static constexpr const UnicodeRange<UC> DevanagariExtended = UnicodeRange<UC>(0xA8E0, 0xA8FF);

		inline static constexpr const UnicodeRange<UC> Dingbats = UnicodeRange<UC>(0x2700, 0x27BF);

		inline static constexpr const UnicodeRange<UC> EnclosedAlphanumerics = UnicodeRange<UC>(0x2460, 0x24FF);

		inline static constexpr const UnicodeRange<UC> EnclosedCjkLettersandMonths = UnicodeRange<UC>(0x3200, 0x32FF);

		inline static constexpr const UnicodeRange<UC> Ethiopic = UnicodeRange<UC>(0x1200, 0x137C);

		inline static constexpr const UnicodeRange<UC> EthiopicExtended = UnicodeRange<UC>(0x2D80, 0x2DDF);

		inline static constexpr const UnicodeRange<UC> EthiopicExtendedA = UnicodeRange<UC>(0xAB00, 0xAB2F);

		inline static constexpr const UnicodeRange<UC> EthiopicSupplement = UnicodeRange<UC>(0x1380, 0x1399);

		inline static constexpr const UnicodeRange<UC> GeneralPunctuation = UnicodeRange<UC>(0x2000, 0x206F);

		inline static constexpr const UnicodeRange<UC> GeometricShapes = UnicodeRange<UC>(0x25A0, 0x25FF);

		inline static constexpr const UnicodeRange<UC> Georgian = UnicodeRange<UC>(0x10A0, 0x10FF);

		inline static constexpr const UnicodeRange<UC> GeorgianExtended = UnicodeRange<UC>(0x1C90, 0x1CBF);

		inline static constexpr const UnicodeRange<UC> GeorgianSupplement = UnicodeRange<UC>(0x2D00, 0x2D2F);

		inline static constexpr const UnicodeRange<UC> Glagolitic = UnicodeRange<UC>(0x2C00, 0x2C5F);

		inline static constexpr const UnicodeRange<UC> GreekandCoptic = UnicodeRange<UC>(0x0370, 0x03FF);

		inline static constexpr const UnicodeRange<UC> GreekExtended = UnicodeRange<UC>(0x1F00, 0x1FFF);

		inline static constexpr const UnicodeRange<UC> Gujarati = UnicodeRange<UC>(0x0A81, 0x0AFF);

		inline static constexpr const UnicodeRange<UC> Gurmukhi = UnicodeRange<UC>(0x0A01, 0x0A7F);

		inline static constexpr const UnicodeRange<UC> HalfwidthandFullwidthForms = UnicodeRange<UC>(0xFF00, 0xFFEE);

		inline static constexpr const UnicodeRange<UC> HangulCompatibilityJamo = UnicodeRange<UC>(0x3131, 0x318F);

		inline static constexpr const UnicodeRange<UC> HangulJamo = UnicodeRange<UC>(0x1100, 0x11FF);

		inline static constexpr const UnicodeRange<UC> HangulJamoExtendedA = UnicodeRange<UC>(0xA960, 0x0A9F);

		inline static constexpr const UnicodeRange<UC> HangulJamoExtendedB = UnicodeRange<UC>(0xD7B0, 0xD7FF);

		inline static constexpr const UnicodeRange<UC> HangulSyllables = UnicodeRange<UC>(0xAC00, 0xD7AF);

		inline static constexpr const UnicodeRange<UC> Hanunoo = UnicodeRange<UC>(0x1720, 0x173F);

		inline static constexpr const UnicodeRange<UC> Hebrew = UnicodeRange<UC>(0x0590, 0x05FF);

		inline static constexpr const UnicodeRange<UC> Hiragana = UnicodeRange<UC>(0x3040, 0x309F);

		inline static constexpr const UnicodeRange<UC> IdeographicDescriptionCharacters = UnicodeRange<UC>(0x2FF0, 0x2FFF);

		inline static constexpr const UnicodeRange<UC> IpaExtensions = UnicodeRange<UC>(0x0250, 0x02AF);

		inline static constexpr const UnicodeRange<UC> Javanese = UnicodeRange<UC>(0xA980, 0xA9DF);

		inline static constexpr const UnicodeRange<UC> Kanbun = UnicodeRange<UC>(0x3190, 0x319F);

		inline static constexpr const UnicodeRange<UC> KangxiRadicals = UnicodeRange<UC>(0x2F00, 0x2FDF);

		inline static constexpr const UnicodeRange<UC> Kannada = UnicodeRange<UC>(0x0C81, 0x0CFF);

		inline static constexpr const UnicodeRange<UC> Katakana = UnicodeRange<UC>(0x30A0, 0x30FF);

		inline static constexpr const UnicodeRange<UC> KatakanaPhoneticExtensions = UnicodeRange<UC>(0x31F0, 0x31FF);

		inline static constexpr const UnicodeRange<UC> KayahLi = UnicodeRange<UC>(0xA900, 0xA92F);

		inline static constexpr const UnicodeRange<UC> Khmer = UnicodeRange<UC>(0x1780, 0x17FF);

		inline static constexpr const UnicodeRange<UC> KhmerSymbols = UnicodeRange<UC>(0x19E0, 0x19FF);

		inline static constexpr const UnicodeRange<UC> Lao = UnicodeRange<UC>(0x0E80, 0x0EDF);

		inline static constexpr const UnicodeRange<UC> Latin1Supplement = UnicodeRange<UC>(0x00A1, 0x00FF);

		inline static constexpr const UnicodeRange<UC> LatinExtendedA = UnicodeRange<UC>(0x0100, 0x017F);

		inline static constexpr const UnicodeRange<UC> LatinExtendedAdditional = UnicodeRange<UC>(0x1E00, 0x1EFF);

		inline static constexpr const UnicodeRange<UC> LatinExtendedB = UnicodeRange<UC>(0x0180, 0x024F);

		inline static constexpr const UnicodeRange<UC> LatinExtendedC = UnicodeRange<UC>(0x2C60, 0x2C7F);

		inline static constexpr const UnicodeRange<UC> LatinExtendedD = UnicodeRange<UC>(0xA720, 0xA7FF);

		inline static constexpr const UnicodeRange<UC> LatinExtendedE = UnicodeRange<UC>(0xAB30, 0xAB6F);

		inline static constexpr const UnicodeRange<UC> Lepcha = UnicodeRange<UC>(0x1C00, 0x1C4F);

		inline static constexpr const UnicodeRange<UC> LetterlikeSymbols = UnicodeRange<UC>(0x2100, 0x214F);

		inline static constexpr const UnicodeRange<UC> Limbu = UnicodeRange<UC>(0x1900, 0x194F);

		inline static constexpr const UnicodeRange<UC> Lisu = UnicodeRange<UC>(0xA4D0, 0xA4FF);

		inline static constexpr const UnicodeRange<UC> Malayalam = UnicodeRange<UC>(0x0D00, 0x0D7F);

		inline static constexpr const UnicodeRange<UC> Mandaic = UnicodeRange<UC>(0x0840, 0x085F);

		inline static constexpr const UnicodeRange<UC> MathematicalOperators = UnicodeRange<UC>(0x2200, 0x22FF);

		inline static constexpr const UnicodeRange<UC> MeeteiMayek = UnicodeRange<UC>(0xABC0, 0xABFF);

		inline static constexpr const UnicodeRange<UC> MeeteiMayekExtensions = UnicodeRange<UC>(0xAAE0, 0xAAFF);

		inline static constexpr const UnicodeRange<UC> MiscellaneousMathematicalSymbolsA = UnicodeRange<UC>(0x27C0, 0x27EF);

		inline static constexpr const UnicodeRange<UC> MiscellaneousMathematicalSymbolsB = UnicodeRange<UC>(0x2980, 0x29FF);

		inline static constexpr const UnicodeRange<UC> MiscellaneousSymbols = UnicodeRange<UC>(0x2600, 0x26FF);

		inline static constexpr const UnicodeRange<UC> MiscellaneousSymbolsandArrows = UnicodeRange<UC>(0x2B00, 0x2BFF);

		inline static constexpr const UnicodeRange<UC> MiscellaneousTechnical = UnicodeRange<UC>(0x2300, 0x23FF);

		inline static constexpr const UnicodeRange<UC> ModifierToneLetters = UnicodeRange<UC>(0xA700, 0xA71F);

		inline static constexpr const UnicodeRange<UC> Mongolian = UnicodeRange<UC>(0x1800, 0x18AF);

		inline static constexpr const UnicodeRange<UC> Myanmar = UnicodeRange<UC>(0x1000, 0x109F);

		inline static constexpr const UnicodeRange<UC> MyanmarExtendedA = UnicodeRange<UC>(0xAA60, 0xAA7F);

		inline static constexpr const UnicodeRange<UC> MyanmarExtendedB = UnicodeRange<UC>(0xA9E0, 0xA9FF);

		inline static constexpr const UnicodeRange<UC> NewTaiLue = UnicodeRange<UC>(0x1980, 0x19DF);

		inline static constexpr const UnicodeRange<UC> NKo = UnicodeRange<UC>(0x07C0, 0x07FF);

		//inline static constexpr const UnicodeRange<UC> None = UnicodeRange<UC>(0xAA00, 0xAA5F);

		inline static constexpr const UnicodeRange<UC> NumberForms = UnicodeRange<UC>(0x2150, 0x218F);

		inline static constexpr const UnicodeRange<UC> Ogham = UnicodeRange<UC>(0x1680, 0x169F);

		inline static constexpr const UnicodeRange<UC> OlChiki = UnicodeRange<UC>(0x1C50, 0x1C7F);

		inline static constexpr const UnicodeRange<UC> OpticalCharacterRecognition = UnicodeRange<UC>(0x2440, 0x245F);

		inline static constexpr const UnicodeRange<UC> Oriya = UnicodeRange<UC>(0x0B00, 0x0B7F);

		inline static constexpr const UnicodeRange<UC> Phagspa = UnicodeRange<UC>(0xA840, 0xA87F);

		inline static constexpr const UnicodeRange<UC> PhoneticExtensions = UnicodeRange<UC>(0x1D00, 0x1D7F);

		inline static constexpr const UnicodeRange<UC> PhoneticExtensionsSupplement = UnicodeRange<UC>(0x1D80, 0x1DBF);

		inline static constexpr const UnicodeRange<UC> Rejang = UnicodeRange<UC>(0xA930, 0xA95F);

		inline static constexpr const UnicodeRange<UC> Runic = UnicodeRange<UC>(0x16A0, 0x16FF);

		inline static constexpr const UnicodeRange<UC> Samaritan = UnicodeRange<UC>(0x0800, 0x083F);

		inline static constexpr const UnicodeRange<UC> Saurashtra = UnicodeRange<UC>(0xA880, 0xA8DF);

		inline static constexpr const UnicodeRange<UC> Sinhala = UnicodeRange<UC>(0x0D80, 0x0DFF);

		inline static constexpr const UnicodeRange<UC> SmallFormVariants = UnicodeRange<UC>(0xFE50, 0xFE6F);

		inline static constexpr const UnicodeRange<UC> SpacingModifierLetters = UnicodeRange<UC>(0x02B0, 0x02FF);

		inline static constexpr const UnicodeRange<UC> Specials = UnicodeRange<UC>(0xFFF0, 0xFFFF);

		inline static constexpr const UnicodeRange<UC> Sundanese = UnicodeRange<UC>(0x1B80, 0x1BBF);

		inline static constexpr const UnicodeRange<UC> SundaneseSupplement = UnicodeRange<UC>(0x1CC0, 0x1CCF);

		inline static constexpr const UnicodeRange<UC> SuperscriptsandSubscripts = UnicodeRange<UC>(0x2070, 0x209F);

		inline static constexpr const UnicodeRange<UC> SupplementalArrowsA = UnicodeRange<UC>(0x27F0, 0x27FF);

		inline static constexpr const UnicodeRange<UC> SupplementalArrowsB = UnicodeRange<UC>(0x2900, 0x297F);

		inline static constexpr const UnicodeRange<UC> SupplementalMathematicalOperators = UnicodeRange<UC>(0x2A00, 0x2AFF);

		inline static constexpr const UnicodeRange<UC> SupplementalPunctuation = UnicodeRange<UC>(0x2E00, 0x2E7F);

		inline static constexpr const UnicodeRange<UC> SylotiNagri = UnicodeRange<UC>(0xA800, 0xA82F);

		inline static constexpr const UnicodeRange<UC> Syriac = UnicodeRange<UC>(0x0700, 0x074F);

		inline static constexpr const UnicodeRange<UC> SyriacSupplement = UnicodeRange<UC>(0x0860, 0x086F);

		inline static constexpr const UnicodeRange<UC> Tagalog = UnicodeRange<UC>(0x1700, 0x171F);

		inline static constexpr const UnicodeRange<UC> Tagbanwa = UnicodeRange<UC>(0x1760, 0x177F);

		inline static constexpr const UnicodeRange<UC> TaiLe = UnicodeRange<UC>(0x1950, 0x197F);

		inline static constexpr const UnicodeRange<UC> TaiTham = UnicodeRange<UC>(0x1A20, 0x1AAF);

		inline static constexpr const UnicodeRange<UC> TaiViet = UnicodeRange<UC>(0xAA80, 0xAADF);

		inline static constexpr const UnicodeRange<UC> Tamil = UnicodeRange<UC>(0x0B80, 0x0BFF);

		inline static constexpr const UnicodeRange<UC> Telugu = UnicodeRange<UC>(0x0C00, 0x0C7F);

		inline static constexpr const UnicodeRange<UC> Thaana = UnicodeRange<UC>(0x0780, 0x07BF);

		inline static constexpr const UnicodeRange<UC> Thai = UnicodeRange<UC>(0x0E00, 0x0E7F);

		inline static constexpr const UnicodeRange<UC> Tibetan = UnicodeRange<UC>(0x0F00, 0x0FFF);

		inline static constexpr const UnicodeRange<UC> Tifinagh = UnicodeRange<UC>(0x2D30, 0x2D7F);

		inline static constexpr const UnicodeRange<UC> UnifiedCanadianAboriginalSyllabics = UnicodeRange<UC>(0x1400, 0x167F);

		inline static constexpr const UnicodeRange<UC> UnifiedCanadianAboriginalSyllabicsExtended = UnicodeRange<UC>(0x18B0, 0x18FF);

		inline static constexpr const UnicodeRange<UC> Vai = UnicodeRange<UC>(0xA500, 0xA63F);

		inline static constexpr const UnicodeRange<UC> VariationSelectors = UnicodeRange<UC>(0xFE00, 0xFE0F);

		inline static constexpr const UnicodeRange<UC> VedicExtensions = UnicodeRange<UC>(0x1CD0, 0x1CFF);

		inline static constexpr const UnicodeRange<UC> VerticalForms = UnicodeRange<UC>(0xFE10, 0xFE1F);

		inline static constexpr const UnicodeRange<UC> YijingHexagramSymbols = UnicodeRange<UC>(0x4DC0, 0x4DFF);

		inline static constexpr const UnicodeRange<UC> YiRadicals = UnicodeRange<UC>(0xA490, 0xA4CF);

		inline static constexpr const UnicodeRange<UC> YiSyllables = UnicodeRange<UC>(0xA000, 0xA48F);
	};
}
#endif
