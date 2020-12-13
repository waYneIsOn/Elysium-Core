/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_GLOBALIZATION_UNICODECATEGORY
#define ELYSIUM_CORE_GLOBALIZATION_UNICODECATEGORY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

namespace Elysium::Core::Globalization
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class UnicodeCategory : Elysium::Core::uint8_t
#elif defined(__ANDROID__)
	enum class UnicodeCategory
#else
#error "undefined os"
#endif
	{
		UppercaseLetter = 0,
		LowercaseLetter = 1,
		TitlecaseLetter = 2,
		ModifierLetter = 3,
		OtherLetter = 4,
		NonSpacingMark = 5,
		SpacingCombiningMark = 6,
		EnclosingMark = 7,
		DecimalDigitNumber = 8,
		LetterNumber = 9,
		OtherNumber = 10,
		SpaceSeparator = 11,
		LineSeparator = 12,
		ParagraphSeparator = 13,
		Control = 14,
		Format = 15,
		Surrogate = 16,
		PrivateUse = 17,
		ConnectorPunctuation = 18,
		DashPunctuation = 19,
		OpenPunctuation = 20,
		ClosePunctuation = 21,
		InitialQuotePunctuation = 22,
		FinalQuotePunctuation = 23,
		OtherPunctuation = 24,
		MathSymbol = 25,
		CurrencySymbol = 26,
		ModifierSymbol = 27,
		OtherSymbol = 28,
		OtherNotAssigned = 29
	};
}
#endif
