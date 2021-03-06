/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_GLOBALIZATION_UNICODEBLOCK
#define ELYSIUM_CORE_GLOBALIZATION_UNICODEBLOCK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "Integer.hpp"
#endif

namespace Elysium::Core::Globalization
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class UnicodeBlock : Elysium::Core::uint32_t
#elif defined(__ANDROID__)
	enum class UnicodeBlock
#else
#error "undefined os"
#endif
	{
		BasicLatin = 0,
		Latin1Supplement = 128,
		LatinExtendedA = 256,
		LatinExtendedB = 384,
		IPAExtensions = 592,
		SpacingModifierLetters = 688,
		CombiningDiacriticalMarks = 768,
		GreekAndCoptic = 880,
		Cyrillic = 1024,
		CyrillicSupplement = 1280,
		Armenian = 1328,
		Hebrew = 1424,
		Arabic = 1536,
		Syriac = 1792,
		ArabicSupplement = 1872,
		Thaana = 1920,
		NKo = 1984,
		Samaritan = 2048,
		Mandaic = 2112,
		SyriacSupplement = 2144,
		ArabicExtendedA = 2208,
		Devanagari = 2304,
		Bengali = 2432,
		Gurmukhi = 2560,
		Gujarati = 2688,
		Oriya = 2816,
		Tamil = 2944,
		Telugu = 3072,
		Kannada = 3200,
		Malayalam = 3328,
		Sinhala = 3456,
		Thai = 3584,
		Lao = 3712,
		Tibetan = 3840,
		Myanmar = 4096,
		Georgian = 4256,
		HangulJamo = 4352,
		Ethiopic = 4608,
		EthiopicSupplement = 4992,
		Cherokee = 5024,
		UnifiedCanadianAboriginalSyllabics = 5120,
		Ogham = 5760,
		Runic = 5792,
		Tagalog = 5888,
		Hanunoo = 5920,
		Buhid = 5952,
		Tagbanwa = 5984,
		Khmer = 6016,
		Mongolian = 6144,
		UnifiedCanadianAboriginalSyllabicsExtended = 6320,
		Limbu = 6400,
		TaiLe = 6480,
		NewTaiLue = 6528,
		KhmerSymbols = 6624,
		Buginese = 6656,
		TaiTham = 6688,
		CombiningDiacriticalMarksExtended = 6832,
		Balinese = 6912,
		Sundanese = 7040,
		Batak = 7104,
		Lepcha = 7168,
		OlChiki = 7248,
		CyrillicExtendedC = 7296,
		GeorgianExtended = 7312,
		SundaneseSupplement = 7360,
		VedicExtensions = 7376,
		PhoneticExtensions = 7424,
		PhoneticExtensionsSupplement = 7552,
		CombiningDiacriticalMarksSupplement = 7616,
		LatinExtendedAdditional = 7680,
		GreekExtended = 7936,
		GeneralPunctuation = 8192,
		SuperscriptsAndSubscripts = 8304,
		CurrencySymbols = 8352,
		CombiningDiacriticalMarksForSymbols = 8400,
		LetterlikeSymbols = 8448,
		NumberForms = 8528,
		Arrows = 8592,
		MathematicalOperators = 8704,
		MiscellaneousTechnical = 8960,
		ControlPictures = 9216,
		OpticalCharacterRecognition = 9280,
		EnclosedAlphanumerics = 9312,
		BoxDrawing = 9472,
		BlockElements = 9600,
		GeometricShapes = 9632,
		MiscellaneousSymbols = 9728,
		Dingbats = 9984,
		MiscellaneousMathematicalSymbolsA = 10176,
		SupplementalArrowsA = 10024,
		BraillePatterns = 10240,
		SupplementalArrowsB = 10496,
		MiscellaneousMathematicalSymbolsB = 10624,
		SupplementalMathematicalOperators = 10752,
		MiscellaneousSymbolsAndArrows = 11008,
		Glagolitic = 11264,
		LatinExtendedC = 11360,
		Coptic = 11392,
		GeorgianSupplement = 11520,
		Tifinagh = 11568,
		EthiopicExtended = 11648,
		CyrillicExtendedA = 11744,
		SupplementalPunctuation = 11776,
		CJKRadicalsSupplement = 11904,
		KangxiRadicals = 12032,
		IdeographicDescriptionCharacters = 12272,
		CJKSymbolsAndPunctuation = 12288,
		Hiragana = 12352,
		Katakana = 12448,
		Bopomofo = 12544,
		HangulCompatibilityJamo = 12592,
		Kanbun = 12688,
		BopomofoExtended = 12704,
		CJKStrokes = 12736,
		KatakanaPhoneticExtensions = 12784,
		EnclosedCJKLettersAndMonths = 12800,
		CJKCompatibility = 13056,
		CJKUnifiedIdeographsExtensionA = 13312,
		YijingHexagramSymbols = 19904,
		CJKUnifiedIdeographs = 19968,
		YiSyllables = 40960,
		YiRadicals = 42128,
		Lisu = 42192,
		Vai = 42240,
		CyrillicExtendedB = 42560,
		Bamum = 42656,
		ModifierToneLetters = 42752,
		LatinExtendedD = 42784,
		SylotiNagri = 43008,
		CommonIndicNumberForms = 43056,
		PhagsPa = 43072,
		Saurashtra = 43136,
		DevanagariExtended = 43232,
		KayahLi = 43264,
		Rejang = 43312,
		HangulJamoExtendedA = 43360,
		Javanese = 43392,
		MyanmarExtendedB = 43488,
		Cham = 43520,
		MyanmarExtendedA = 43616,
		TaiViet = 43648,
		MeeteiMayekExtensions = 43744,
		EthiopicExtendedA = 43776,
		LatinExtendedE = 43824,
		CherokeeSupplement = 43888,
		MeeteiMayek = 43968,
		HangulSyllables = 44032,
		HangulJamoExtendedB = 55216,
		HighSurrogates = 55296,
		HighPrivateUseSurrogates = 56192,
		LowSurrogates = 56320,
		PrivateUseArea = 57344,
		CJKCompatibilityIdeographs = 63744,
		AlphabeticPresentationForms = 64256,
		ArabicPresentationFormsA = 64336,
		VariationSelectors = 65024,
		VerticalForms = 65040,
		CombiningHalfMarks = 65056,
		CJKCompatibilityForms = 65072,
		SmallFormVariants = 65104,
		ArabicPresentationFormsB = 65136,
		HalfwidthAndFullwidthForms = 65280,
		Specials = 65520,
		LinearBSyllabary = 65536,
		LinearBIdeograms = 65664,
		AegeanNumbers = 65792,
		AncientGreekNumbers = 65856,
		AncientSymbols = 65936,
		PhaistosDisc = 66000,
		Lycian = 66176,
		Carian = 66208,
		CopticEpactNumbers = 66272,
		OldItalic = 66304,
		Gothic = 66352,
		OldPermic = 66384,
		Ugaritic = 66432,
		OldPersian = 66464,
		Deseret = 66560,
		Shavian = 66640,
		Osmanya = 66688,
		Osage = 66736,
		Elbasan = 66816,
		CaucasianAlbanian = 66864,
		LinearA = 67072,
		CypriotSyllabary = 67584,
		ImperialAramaic = 67648,
		Palmyrene = 67680,
		Nabataean = 67712,
		Hatran = 67808,
		Phoenician = 67840,
		Lydian = 67872,
		MeroiticHieroglyphs = 67968,
		MeroiticCursive = 68000,
		Kharoshthi = 68096,
		OldSouthArabian = 68192,
		OldNorthArabian = 68224,
		Manichaean = 68288,
		Avestan = 68352,
		InscriptionalParthian = 68416,
		InscriptionalPahlavi = 68448,
		PsalterPahlavi = 68480,
		OldTurkic = 68608,
		OldHungarian = 68736,
		HanifiRohingya = 68864,
		RumiNumeralSymbols = 69216,
		Yezidi = 69248,
		OldSogdian = 69376,
		Sogdian = 69424,
		Chorasmian = 69552,
		Elymaic = 69600,
		Brahmi = 69632,
		Kaithi = 69760,
		SoraSompeng = 69840,
		Chakma = 69888,
		Mahajani = 69968,
		Sharada = 70016,
		SinhalaArchaicNumbers = 70112,
		Khojki = 70144,
		Multani = 70272,
		Khudawadi = 70320,
		Grantha = 70400,
		Newa = 70656,
		Tirhuta = 70784,
		Siddham = 71040,
		Modi = 71168,
		MongolianSupplement = 71264,
		Takri = 71296,
		Ahom = 71424,
		Dogra = 71680,
		WarangCiti = 71840,
		DivesAkuru = 71936,
		Nandinagari = 72192,
		Soyombo = 72272,
		PauCinHau = 72384,
		Bhaiksuki = 72704,
		Marchen = 72816,
		MasaramGondi = 72960,
		GunjalaGondi = 73056,
		Makasar = 73440,
		LisuSupplement = 73648,
		TamilSupplement = 73664,
		Cuneiform = 73728,
		CuneiformNumbersAndPunctuation = 74752,
		EarlyDynasticCuneiform = 74880,
		EgyptianHieroglyphs = 77824,
		EgyptianHieroglyphFormatControls = 78896,
		AnatolianHieroglyphs = 82944,
		BamumSupplement = 92160,
		Mro = 92736,
		BassaVah = 92880,
		PahawhHmong = 92928,
		Medefaidrin = 93760,
		Miao = 93952,
		IdeographicSymbolsAndPunctuation = 94176,
		Tangut = 94208,
		TangutComponents = 100352,
		KhitanSmallScript = 101120,
		TangutSupplement = 101632,
		KanaSupplement = 110592,
		KanaExtendedA = 110848,
		SmallKanaExtension = 110896,
		Nushu = 110960,
		Duployan = 113664,
		ShorthandFormatControls = 113824,
		ByzantineMusicalSymbols = 118784,
		MusicalSymbols = 119040,
		AncientGreekMusicalNotation = 119296,
		MayanNumerals = 119520,
		TaiXuanJingSymbols = 119552,
		CountingRodNumerals = 119648,
		MathematicalAlphanumericSymbols = 119808,
		SuttonSignWriting = 120832,
		GlagoliticSupplement = 122880,
		NyiakengPuachueHmong = 123136,
		Wancho = 123584,
		MendeKikakui = 124928,
		Adlam = 125184,
		IndicSiyaqNumbers = 126064,
		OttomanSiyaqNumbers = 126208,
		ArabicMathematicalAlphabeticSymbols = 126464,
		MahjongTiles = 126976,
		DominoTiles = 127024,
		PlayingCards = 127136,
		EnclosedAlphanumericSupplement = 127232,
		EnclosedIdeographicSupplement = 127488,
		MiscellaneousSymbolsAndPictographs = 127744,
		Emoticons = 128512,
		OrnamentalDingbats = 128592,
		TransportAndMapSymbols = 128640,
		AlchemicalSymbols = 128768,
		GeometricShapesExtended = 128896,
		SupplementalArrowsC = 129024,
		SupplementalSymbolsAndPictographs = 129280,
		ChessSymbols = 129536,
		SymbolsAndPictographsExtendedA = 129648,
		SymbolsForLegacyComputing = 129792,
		CJKUnifiedIdeographsExtensionB = 131072,
		CJKUnifiedIdeographsExtensionC = 173824,
		CJKUnifiedIdeographsExtensionD = 177984,
		CJKUnifiedIdeographsExtensionE = 178208,
		CJKUnifiedIdeographsExtensionF = 183984,
		CJKCompatibilityIdeographsSupplement = 194560,
		CJKUnifiedIdeographsExtensionG = 196608,
		Tags = 917504,
		VariationSelectorsSupplement = 917760,
		SupplementaryPrivateUseAreaA = 983040,
		SupplementaryPrivateUseAreaB = 1048576
	};
}
#endif
