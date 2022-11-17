/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_UNICODECATEGORY
#define ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_UNICODECATEGORY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

namespace Elysium::Core::Template::Globalization
{
	/// <summary>
	/// https://www.fileformat.info/info/unicode/category/index.htm
	/// </summary>
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class UnicodeCategory : System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class UnicodeCategory
#else
#error "undefined os"
#endif
	{
		/// <summary>
		/// [Lu]
		/// https://www.fileformat.info/info/unicode/category/Lu/index.htm
		/// </summary>
		UppercaseLetter = 0,

		/// <summary>
		/// [Ll]
		/// https://www.fileformat.info/info/unicode/category/Ll/index.htm
		/// </summary>
		LowercaseLetter = 1,

		/// <summary>
		/// [Lt]
		/// https://www.fileformat.info/info/unicode/category/Lt/index.htm
		/// </summary>
		TitlecaseLetter = 2,

		/// <summary>
		/// [Lm]
		/// https://www.fileformat.info/info/unicode/category/Lm/index.htm
		/// </summary>
		ModifierLetter = 3,

		/// <summary>
		/// [Lo]
		/// https://www.fileformat.info/info/unicode/category/Lo/index.htm
		/// </summary>
		OtherLetter = 4,

		/// <summary>
		/// [Mn]
		/// https://www.fileformat.info/info/unicode/category/Mn/index.htm
		/// </summary>
		NonSpacingMark = 5,

		/// <summary>
		/// [Mc]
		/// https://www.fileformat.info/info/unicode/category/Mc/index.htm
		/// </summary>
		SpacingCombiningMark = 6,

		/// <summary>
		/// [Me]
		/// https://www.fileformat.info/info/unicode/category/Me/index.htm
		/// </summary>
		EnclosingMark = 7,

		/// <summary>
		/// [Nd]
		/// https://www.fileformat.info/info/unicode/category/Nd/index.htm
		/// </summary>
		DecimalDigitNumber = 8,

		/// <summary>
		/// [Nl]
		/// https://www.fileformat.info/info/unicode/category/Nl/index.htm
		/// </summary>
		LetterNumber = 9,

		/// <summary>
		/// [No]
		/// https://www.fileformat.info/info/unicode/category/No/index.htm
		/// </summary>
		OtherNumber = 10,

		/// <summary>
		/// [Zs]
		/// https://www.fileformat.info/info/unicode/category/Zs/index.htm
		/// </summary>
		SpaceSeparator = 11,

		/// <summary>
		/// [Zl]
		/// https://www.fileformat.info/info/unicode/category/Zl/index.htm
		/// </summary>
		LineSeparator = 12,

		/// <summary>
		/// [Zp]
		/// https://www.fileformat.info/info/unicode/category/Zp/index.htm
		/// </summary>
		ParagraphSeparator = 13,

		/// <summary>
		/// [Cc]
		/// https://www.fileformat.info/info/unicode/category/Cc/index.htm
		/// </summary>
		Control = 14,

		/// <summary>
		/// [Cf]
		/// https://www.fileformat.info/info/unicode/category/Cf/index.htm
		/// </summary>
		Format = 15,

		/// <summary>
		/// [Cs]
		/// https://www.fileformat.info/info/unicode/category/Cs/index.htm
		/// </summary>
		Surrogate = 16,

		/// <summary>
		/// [Co]
		/// https://www.fileformat.info/info/unicode/category/Co/index.htm
		/// </summary>
		PrivateUse = 17,

		/// <summary>
		/// [Pc]
		/// https://www.fileformat.info/info/unicode/category/Pc/index.htm
		/// </summary>
		ConnectorPunctuation = 18,

		/// <summary>
		/// [Pd]
		/// https://www.fileformat.info/info/unicode/category/Pd/index.htm
		/// </summary>
		DashPunctuation = 19,

		/// <summary>
		/// [Ps]
		/// https://www.fileformat.info/info/unicode/category/Ps/index.htm
		/// </summary>
		OpenPunctuation = 20,

		/// <summary>
		/// [Pe]
		/// https://www.fileformat.info/info/unicode/category/Pe/index.htm
		/// </summary>
		ClosePunctuation = 21,

		/// <summary>
		/// [Pi] (may behave like Ps or Pe depending on usage)
		/// https://www.fileformat.info/info/unicode/category/Pi/index.htm
		/// </summary>
		InitialQuotePunctuation = 22,

		/// <summary>
		/// [Pf] (may behave like Ps or Pe depending on usage)
		/// https://www.fileformat.info/info/unicode/category/Pf/index.htm
		/// </summary>
		FinalQuotePunctuation = 23,

		/// <summary>
		/// [Po]
		/// https://www.fileformat.info/info/unicode/category/Po/index.htm
		/// </summary>
		OtherPunctuation = 24,

		/// <summary>
		/// [Sm]
		/// https://www.fileformat.info/info/unicode/category/Sm/index.htm
		/// </summary>
		MathSymbol = 25,

		/// <summary>
		/// [Sc]
		/// https://www.fileformat.info/info/unicode/category/Sc/index.htm
		/// </summary>
		CurrencySymbol = 26,

		/// <summary>
		/// [Sk]
		/// https://www.fileformat.info/info/unicode/category/Sk/index.htm
		/// </summary>
		ModifierSymbol = 27,

		/// <summary>
		/// [So]
		/// https://www.fileformat.info/info/unicode/category/So/index.htm
		/// </summary>
		OtherSymbol = 28,

		/// <summary>
		/// [Cn] (no characters in the file have this property)
		/// https://www.fileformat.info/info/unicode/category/Cn/index.htm
		/// </summary>
		OtherNotAssigned = 29,

		/*
		* omitted as there are currently no characters in this category
		/// <summary>
		/// [Lc]
		/// https://www.fileformat.info/info/unicode/category/LC/index.htm
		/// </summary>
		CasedLetter = -1
		*/
	};
}
#endif
