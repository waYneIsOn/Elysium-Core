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

		constexpr UnicodeRanges(const UnicodeRange& Source) = delete;

		constexpr UnicodeRanges(UnicodeRange&& Right) noexcept = delete;

		constexpr ~UnicodeRanges() = delete;
	public:
		UnicodeRanges& operator=(const UnicodeRanges& Source) = delete;

		UnicodeRanges& operator=(UnicodeRanges&& Right) noexcept = delete;
	public:
		constexpr const UnicodeRange<UC> All = UnicodeRange<UC>('\u0000', '\uFFFFFF');

		constexpr const UnicodeRange<UC> AlphabeticPresentationForms = UnicodeRange<UC>('\uFB00', '\uFB4F');

		constexpr const UnicodeRange<UC> Arabic = UnicodeRange<UC>('\u0600', '\u06FF');

		constexpr const UnicodeRange<UC> ArabicExtendedA = UnicodeRange<UC>('\u08A0', '\u08FF');

		constexpr const UnicodeRange<UC> ArabicExtendedB = UnicodeRange<UC>('\u0870', '\u089F');

		constexpr const UnicodeRange<UC> ArabicPresentationFormsA = UnicodeRange<UC>('\uFB50', '\uFDFF');

		constexpr const UnicodeRange<UC> ArabicPresentationFormsB = UnicodeRange<UC>('\uFE70', '\uFEFF');

		constexpr const UnicodeRange<UC> ArabicSupplement = UnicodeRange<UC>('\u0750', '\u077F');

		constexpr const UnicodeRange<UC> Armenian = UnicodeRange<UC>('\u0530', '\u058F');

		constexpr const UnicodeRange<UC> Arrows = UnicodeRange<UC>('\u2190', '\u21FF');

		constexpr const UnicodeRange<UC> Balinese = UnicodeRange<UC>('\u1B00', '\u1B7F');

		constexpr const UnicodeRange<UC> Bamum = UnicodeRange<UC>('\u1B00', '\u1B7F');

		constexpr const UnicodeRange<UC> BasicLatin = UnicodeRange<UC>('\u0021', '\u007F');

		constexpr const UnicodeRange<UC> Batak = UnicodeRange<UC>('\u1BC0', '\u1BFF');

		constexpr const UnicodeRange<UC> Bengali = UnicodeRange<UC>('\u0980', '\u09FF');

		constexpr const UnicodeRange<UC> BlockElements = UnicodeRange<UC>('\u2580', '\u259F');

		constexpr const UnicodeRange<UC> Bopomofo = UnicodeRange<UC>('\u3100', '\u312F');

		constexpr const UnicodeRange<UC> BopomofoExtended = UnicodeRange<UC>('\u31A0', '\u31BF');

		constexpr const UnicodeRange<UC> BoxDrawing = UnicodeRange<UC>('\u2500', '\u257F');

		constexpr const UnicodeRange<UC> BraillePatterns = UnicodeRange<UC>('\u2800', '\u28FF');

		constexpr const UnicodeRange<UC> Buginese = UnicodeRange<UC>('\u1A00', '\u1A1F');

		constexpr const UnicodeRange<UC> Buhid = UnicodeRange<UC>('\u1740', '\u175F');

		constexpr const UnicodeRange<UC> Cham = UnicodeRange<UC>('\uAA00', '\uAA5F');

		constexpr const UnicodeRange<UC> Cham = UnicodeRange<UC>('\uAA00', '\uAA5F');
		
		constexpr const UnicodeRange<UC> Cherokee = UnicodeRange<UC>('\u13A0', '\u13FF');

		constexpr const UnicodeRange<UC> CherokeeSupplement = UnicodeRange<UC>('\uAB70', '\uABBF');

		constexpr const UnicodeRange<UC> CjkCompatibility = UnicodeRange<UC>('\u3300', '\u33FF');

		constexpr const UnicodeRange<UC> CjkCompatibilityForms = UnicodeRange<UC>('\uFE30', '\uFE4F');

		constexpr const UnicodeRange<UC> CjkCompatibilityIdeographs = UnicodeRange<UC>('\uF900', '\uFAD9');
		
		constexpr const UnicodeRange<UC> CjkRadicalsSupplement = UnicodeRange<UC>('\u2E80', '\u2EFF');
		
		constexpr const UnicodeRange<UC> CjkStrokes = UnicodeRange<UC>('\u31C0', '\u31EF');

		constexpr const UnicodeRange<UC> CjkSymbolsandPunctuation = UnicodeRange<UC>('\u3000', '\u303F');
		
		constexpr const UnicodeRange<UC> CjkUnifiedIdeographs = UnicodeRange<UC>('\u4E00', '\u9FCC');
		
		constexpr const UnicodeRange<UC> CjkUnifiedIdeographsExtensionA = UnicodeRange<UC>('\u3400', '\u4DB5');
		
		constexpr const UnicodeRange<UC> CombiningDiacriticalMarks = UnicodeRange<UC>('\u0300', '\u036F');

		constexpr const UnicodeRange<UC> CombiningDiacriticalMarksExtended = UnicodeRange<UC>('\u1AB0', '\u1AFF');

		constexpr const UnicodeRange<UC> CombiningDiacriticalMarksforSymbols = UnicodeRange<UC>('\u20D0', '\u20FF');

		constexpr const UnicodeRange<UC> CombiningDiacriticalMarksSupplement = UnicodeRange<UC>('\u1DC0', '\u1DFF');
		
		constexpr const UnicodeRange<UC> CombiningHalfMarks = UnicodeRange<UC>('\uFE20', '\uFE2F');
		
		constexpr const UnicodeRange<UC> CommonIndicNumberForms = UnicodeRange<UC>('\uA830', '\uA83F');

		constexpr const UnicodeRange<UC> ControlPictures = UnicodeRange<UC>('\u2400', '\u243F');
		
		constexpr const UnicodeRange<UC> Coptic = UnicodeRange<UC>('\u2C80', '\u2CFF');

		constexpr const UnicodeRange<UC> CurrencySymbols = UnicodeRange<UC>('\u20A0', '\u20CF');

		constexpr const UnicodeRange<UC> Cyrillic = UnicodeRange<UC>('\u0400', '\u04FF');
		
		constexpr const UnicodeRange<UC> CyrillicExtendedA = UnicodeRange<UC>('\u2DE0', '\u2DFF');

		constexpr const UnicodeRange<UC> CyrillicExtendedB = UnicodeRange<UC>('\uA640', '\uA69F');

		constexpr const UnicodeRange<UC> CyrillicExtendedC = UnicodeRange<UC>('\u1C80', '\u1C8F');

		constexpr const UnicodeRange<UC> CyrillicSupplement = UnicodeRange<UC>('\u0500', '\u052F');

		constexpr const UnicodeRange<UC> Devanagari = UnicodeRange<UC>('\u0900', '\u097F');
		
		constexpr const UnicodeRange<UC> DevanagariExtended = UnicodeRange<UC>('\uA8E0', '\uA8FF');
		
		constexpr const UnicodeRange<UC> Dingbats = UnicodeRange<UC>('\u2700', '\u27BF');
		
		constexpr const UnicodeRange<UC> EnclosedAlphanumerics = UnicodeRange<UC>('\u2460', '\u24FF');
		
		constexpr const UnicodeRange<UC> EnclosedCjkLettersandMonths = UnicodeRange<UC>('\u3200', '\u32FF');
		
		constexpr const UnicodeRange<UC> Ethiopic = UnicodeRange<UC>('\u1200', '\u137C');

		constexpr const UnicodeRange<UC> EthiopicExtended = UnicodeRange<UC>('\u2D80', '\u2DDF');

		constexpr const UnicodeRange<UC> EthiopicExtendedA = UnicodeRange<UC>('\uAB00', '\uAB2F');

		constexpr const UnicodeRange<UC> EthiopicSupplement = UnicodeRange<UC>('\u1380', '\u1399');

		constexpr const UnicodeRange<UC> GeneralPunctuation = UnicodeRange<UC>('\u2000', '\u206F');
		
		constexpr const UnicodeRange<UC> GeometricShapes = UnicodeRange<UC>('\u25A0', '\u25FF');
		
		constexpr const UnicodeRange<UC> Georgian = UnicodeRange<UC>('\u10A0', '\u10FF');

		constexpr const UnicodeRange<UC> GeorgianExtended = UnicodeRange<UC>('\u1C90', '\u1CBF');

		constexpr const UnicodeRange<UC> GeorgianSupplement = UnicodeRange<UC>('\u2D00', '\u2D2F');
		
		constexpr const UnicodeRange<UC> Glagolitic = UnicodeRange<UC>('\u2C00', '\u2C5F');

		constexpr const UnicodeRange<UC> GreekandCoptic = UnicodeRange<UC>('\u0370', '\u03FF');
		
		constexpr const UnicodeRange<UC> GreekExtended = UnicodeRange<UC>('\u1F00', '\u1FFF');
		
		constexpr const UnicodeRange<UC> Gujarati = UnicodeRange<UC>('\u0A81', '\u0AFF');

		constexpr const UnicodeRange<UC> Gurmukhi = UnicodeRange<UC>('\u0A01', '\u0A7F');

		constexpr const UnicodeRange<UC> HalfwidthandFullwidthForms = UnicodeRange<UC>('\uFF00', '\uFFEE');
		
		constexpr const UnicodeRange<UC> HangulCompatibilityJamo = UnicodeRange<UC>('\u3131', '\u318F');
		
		constexpr const UnicodeRange<UC> HangulJamo = UnicodeRange<UC>('\u1100', '\u11FF');

		constexpr const UnicodeRange<UC> HangulJamoExtendedA = UnicodeRange<UC>('\uA960', '\u0A9F');
		
		constexpr const UnicodeRange<UC> HangulJamoExtendedB = UnicodeRange<UC>('\uD7B0', '\uD7FF');

		constexpr const UnicodeRange<UC> HangulSyllables = UnicodeRange<UC>('\uAC00', '\uD7AF');

		constexpr const UnicodeRange<UC> Hanunoo = UnicodeRange<UC>('\u1720', '\u173F');
		
		constexpr const UnicodeRange<UC> Hebrew = UnicodeRange<UC>('\u0590', '\u05FF');

		constexpr const UnicodeRange<UC> Hiragana = UnicodeRange<UC>('\u3040', '\u309F');

		constexpr const UnicodeRange<UC> IdeographicDescriptionCharacters = UnicodeRange<UC>('\u2FF0', '\u2FFF');
		
		constexpr const UnicodeRange<UC> IpaExtensions = UnicodeRange<UC>('\u0250', '\u02AF');

		constexpr const UnicodeRange<UC> Javanese = UnicodeRange<UC>('\uA980', '\uA9DF');

		constexpr const UnicodeRange<UC> Kanbun = UnicodeRange<UC>('\u3190', '\u319F');
		
		constexpr const UnicodeRange<UC> KangxiRadicals = UnicodeRange<UC>('\u2F00', '\u2FDF');
		
		constexpr const UnicodeRange<UC> Kannada = UnicodeRange<UC>('\u0C81', '\u0CFF');

		constexpr const UnicodeRange<UC> Katakana = UnicodeRange<UC>('\u30A0', '\u30FF');
		
		constexpr const UnicodeRange<UC> KatakanaPhoneticExtensions = UnicodeRange<UC>('\u31F0', '\u31FF');

		constexpr const UnicodeRange<UC> KayahLi = UnicodeRange<UC>('\uA900', '\uA92F');

		constexpr const UnicodeRange<UC> Khmer = UnicodeRange<UC>('\u1780', '\u17FF');

		constexpr const UnicodeRange<UC> KhmerSymbols = UnicodeRange<UC>('\u19E0', '\u19FF');

		constexpr const UnicodeRange<UC> Lao = UnicodeRange<UC>('\u0E80', '\u0EDF');
		
		constexpr const UnicodeRange<UC> Latin1Supplement = UnicodeRange<UC>('\u00A1', '\u00FF');

		constexpr const UnicodeRange<UC> LatinExtendedA = UnicodeRange<UC>('\u0100', '\u017F');
		
		constexpr const UnicodeRange<UC> LatinExtendedAdditional = UnicodeRange<UC>('\u1E00', '\u1EFF');

		constexpr const UnicodeRange<UC> LatinExtendedB = UnicodeRange<UC>('\u0180', '\u024F');

		constexpr const UnicodeRange<UC> LatinExtendedC = UnicodeRange<UC>('\u2C60', '\u2C7F');

		constexpr const UnicodeRange<UC> LatinExtendedD = UnicodeRange<UC>('\uA720', '\uA7FF');

		constexpr const UnicodeRange<UC> LatinExtendedE = UnicodeRange<UC>('\uAB30', '\uAB6F');

		constexpr const UnicodeRange<UC> Lepcha = UnicodeRange<UC>('\u1C00', '\u1C4F');
		
		constexpr const UnicodeRange<UC> LetterlikeSymbols = UnicodeRange<UC>('\u2100', '\u214F');
		
		constexpr const UnicodeRange<UC> Limbu = UnicodeRange<UC>('\u1900', '\u194F');

		constexpr const UnicodeRange<UC> Lisu = UnicodeRange<UC>('\uA4D0', '\uA4FF');

		constexpr const UnicodeRange<UC> Malayalam = UnicodeRange<UC>('\u0D00', '\u0D7F');
		
		constexpr const UnicodeRange<UC> Mandaic = UnicodeRange<UC>('\u0840', '\u085F');

		constexpr const UnicodeRange<UC> MathematicalOperators = UnicodeRange<UC>('\u2200', '\u22FF');

		constexpr const UnicodeRange<UC> MeeteiMayek = UnicodeRange<UC>('\uABC0', '\uABFF');

		constexpr const UnicodeRange<UC> MeeteiMayekExtensions = UnicodeRange<UC>('\uAAE0', '\uAAFF');
		
		constexpr const UnicodeRange<UC> MiscellaneousMathematicalSymbolsA = UnicodeRange<UC>('\u27C0', '\u27EF');

		constexpr const UnicodeRange<UC> MiscellaneousMathematicalSymbolsB = UnicodeRange<UC>('\u2980', '\u29FF');

		constexpr const UnicodeRange<UC> MiscellaneousSymbols = UnicodeRange<UC>('\u2600', '\u26FF');
		
		constexpr const UnicodeRange<UC> MiscellaneousSymbolsandArrows = UnicodeRange<UC>('\u2B00', '\u2BFF');

		constexpr const UnicodeRange<UC> MiscellaneousTechnical = UnicodeRange<UC>('\u2300', '\u23FF');

		constexpr const UnicodeRange<UC> ModifierToneLetters = UnicodeRange<UC>('\uA700', '\uA71F');

		constexpr const UnicodeRange<UC> Mongolian = UnicodeRange<UC>('\u1800', '\u18AF');
		
		constexpr const UnicodeRange<UC> Myanmar = UnicodeRange<UC>('\u1000', '\u109F');

		constexpr const UnicodeRange<UC> MyanmarExtendedA = UnicodeRange<UC>('\uAA60', '\uAA7F');

		constexpr const UnicodeRange<UC> MyanmarExtendedB = UnicodeRange<UC>('\uA9E0', '\uA9FF');

		constexpr const UnicodeRange<UC> NewTaiLue = UnicodeRange<UC>('\u1980', '\u19DF');
		
		constexpr const UnicodeRange<UC> NKo = UnicodeRange<UC>('\u07C0', '\u07FF');

		//constexpr const UnicodeRange<UC> None = UnicodeRange<UC>('\uAA00', '\uAA5F');
		
		constexpr const UnicodeRange<UC> NumberForms = UnicodeRange<UC>('\u2150', '\u218F');

		constexpr const UnicodeRange<UC> Ogham = UnicodeRange<UC>('\u1680', '\u169F');
		
		constexpr const UnicodeRange<UC> OlChiki = UnicodeRange<UC>('\u1C50', '\u1C7F');

		constexpr const UnicodeRange<UC> OpticalCharacterRecognition = UnicodeRange<UC>('\u2440', '\u245F');
		
		constexpr const UnicodeRange<UC> Oriya = UnicodeRange<UC>('\u0B00', '\u0B7F');

		constexpr const UnicodeRange<UC> Phagspa = UnicodeRange<UC>('\uA840', '\uA87F');

		constexpr const UnicodeRange<UC> PhoneticExtensions = UnicodeRange<UC>('\u1D00', '\u1D7F');

		constexpr const UnicodeRange<UC> PhoneticExtensionsSupplement = UnicodeRange<UC>('\u1D80', '\u1DBF');
		
		constexpr const UnicodeRange<UC> Rejang = UnicodeRange<UC>('\uA930', '\uA95F');

		constexpr const UnicodeRange<UC> Runic = UnicodeRange<UC>('\u16A0', '\u16FF');

		constexpr const UnicodeRange<UC> Samaritan = UnicodeRange<UC>('\u0800', '\u083F');
		
		constexpr const UnicodeRange<UC> Saurashtra = UnicodeRange<UC>('\uA880', '\uA8DF');

		constexpr const UnicodeRange<UC> Sinhala = UnicodeRange<UC>('\u0D80', '\u0DFF');

		constexpr const UnicodeRange<UC> SmallFormVariants = UnicodeRange<UC>('\uFE50', '\uFE6F');

		constexpr const UnicodeRange<UC> SpacingModifierLetters = UnicodeRange<UC>('\u02B0', '\u02FF');

		constexpr const UnicodeRange<UC> Specials = UnicodeRange<UC>('\uFFF0', '\uFFFF');
		
		constexpr const UnicodeRange<UC> Sundanese = UnicodeRange<UC>('\u1B80', '\u1BBF');

		constexpr const UnicodeRange<UC> SundaneseSupplement = UnicodeRange<UC>('\u1CC0', '\u1CCF');

		constexpr const UnicodeRange<UC> SuperscriptsandSubscripts = UnicodeRange<UC>('\u2070', '\u209F');

		constexpr const UnicodeRange<UC> SupplementalArrowsA = UnicodeRange<UC>('\u27F0', '\u27FF');

		constexpr const UnicodeRange<UC> SupplementalArrowsB = UnicodeRange<UC>('\u2900', '\u297F');
		
		constexpr const UnicodeRange<UC> SupplementalMathematicalOperators = UnicodeRange<UC>('\u2A00', '\u2AFF');

		constexpr const UnicodeRange<UC> SupplementalPunctuation = UnicodeRange<UC>('\u2E00', '\u2E7F');

		constexpr const UnicodeRange<UC> SylotiNagri = UnicodeRange<UC>('\uA800', '\uA82F');

		constexpr const UnicodeRange<UC> Syriac = UnicodeRange<UC>('\u0700', '\u074F');
		
		constexpr const UnicodeRange<UC> SyriacSupplement = UnicodeRange<UC>('\u0860', '\u086F');

		constexpr const UnicodeRange<UC> Tagalog = UnicodeRange<UC>('\u1700', '\u171F');

		constexpr const UnicodeRange<UC> Tagbanwa = UnicodeRange<UC>('\u1760', '\u177F');
		
		constexpr const UnicodeRange<UC> TaiLe = UnicodeRange<UC>('\u1950', '\u197F');

		constexpr const UnicodeRange<UC> TaiTham = UnicodeRange<UC>('\u1A20', '\u1AAF');
		
		constexpr const UnicodeRange<UC> TaiViet = UnicodeRange<UC>('\uAA80', '\uAADF');

		constexpr const UnicodeRange<UC> Tamil = UnicodeRange<UC>('\u0B80', '\u0BFF');

		constexpr const UnicodeRange<UC> Telugu = UnicodeRange<UC>('\u0C00', '\u0C7F');
		
		constexpr const UnicodeRange<UC> Thaana = UnicodeRange<UC>('\u0780', '\u07BF');

		constexpr const UnicodeRange<UC> Thai = UnicodeRange<UC>('\u0E00', '\u0E7F');
		
		constexpr const UnicodeRange<UC> Tibetan = UnicodeRange<UC>('\u0F00', '\u0FFF');

		constexpr const UnicodeRange<UC> Tifinagh = UnicodeRange<UC>('\u2D30', '\u2D7F');
		
		constexpr const UnicodeRange<UC> UnifiedCanadianAboriginalSyllabics = UnicodeRange<UC>('\u1400', '\u167F');

		constexpr const UnicodeRange<UC> UnifiedCanadianAboriginalSyllabicsExtended = UnicodeRange<UC>('\u18B0', '\u18FF');

		constexpr const UnicodeRange<UC> Vai = UnicodeRange<UC>('\uA500', '\uA63F');

		constexpr const UnicodeRange<UC> VariationSelectors = UnicodeRange<UC>('\uFE00', '\uFE0F');
		
		constexpr const UnicodeRange<UC> VedicExtensions = UnicodeRange<UC>('\u1CD0', '\u1CFF');

		constexpr const UnicodeRange<UC> VerticalForms = UnicodeRange<UC>('\uFE10', '\uFE1F');

		constexpr const UnicodeRange<UC> YijingHexagramSymbols = UnicodeRange<UC>('\u4DC0', '\u4DFF');

		constexpr const UnicodeRange<UC> YiRadicals = UnicodeRange<UC>('\uA490', '\uA4CF');

		constexpr const UnicodeRange<UC> YiSyllables = UnicodeRange<UC>('\uA000', '\uA48F');
	};
}
#endif
