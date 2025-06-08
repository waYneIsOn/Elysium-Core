/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_CODEANALYSIS_CSHARP_SYNTAXKIND
#define ELYSIUM_CORE_CODEANALYSIS_CSHARP_SYNTAXKIND

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../Elysium.Core.Template/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

namespace Elysium::Core::CodeAnalysis::CSharp
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class SyntaxKind : Elysium::Core::Template::System::uint16_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class SyntaxKind
#else
#error "undefined os"
#endif
	{
		None = 0,

		/// <summary>
		/// ~
		/// </summary>
		TildeToken = 8193,

		/// <summary>
		/// !
		/// </summary>
		ExclamationToken = 8194,

		/// <summary>
		/// $
		/// </summary>
		DollarToken = 8195,

		/// <summary>
		/// $
		/// </summary>
		PercentToken = 8196,

		/// <summary>
		/// ^
		/// </summary>
		CaretToken = 8197,

		/// <summary>
		/// &amp;
		/// </summary>
		AmpersandToken = 8198,

		/// <summary>
		/// *
		/// </summary>
		AsteriksToken = 8199,

		/// <summary>
		/// (
		/// </summary>
		OpenParentToken = 8200,

		/// <summary>
		/// )
		/// </summary>
		CloseParenToken = 8201,

		/// <summary>
		/// -
		/// </summary>
		MinusToken = 8202,

		/// <summary>
		/// +
		/// </summary>
		PlusToken = 8203,

		/// <summary>
		/// =
		/// </summary>
		EqualsToken = 8204,

		/// <summary>
		/// {
		/// </summary>
		OpenBraceToken = 8205,

		/// <summary>
		/// }
		/// </summary>
		CloseBraceToken = 8206,

		/// <summary>
		/// [
		/// </summary>
		OpenBracketToken = 8207,

		/// <summary>
		/// ]
		/// </summary>
		CloseBracketToken = 8208,

		/// <summary>
		/// |
		/// </summary>
		BarToken = 8209,

		/// <summary>
		/// \
		/// </summary>
		BackslashToken = 8210,

		/// <summary>
		/// :
		/// </summary>
		ColonToken = 8211,

		/// <summary>
		/// ;
		/// </summary>
		SemicolonToken = 8212,

		/// <summary>
		/// "
		/// </summary>
		DoubleQuoteToken = 8213,

		/// <summary>
		/// '
		/// </summary>
		SingleQuoteToken = 8214,

		/// <summary>
		/// <
		/// </summary>
		LessThanToken = 8215,

		/// <summary>
		/// >
		/// </summary>
		GreaterThanToken = 8216,

		/// <summary>
		/// ,
		/// </summary>
		CommaToken = 8217,

		/// <summary>
		/// .
		/// </summary>
		DotToken = 8218,

		/// <summary>
		/// ?
		/// </summary>
		QuestionToken = 8219,

		/// <summary>
		/// #
		/// </summary>
		HashToken = 8220,

		/// <summary>
		/// /
		/// </summary>
		SlashToken = 8221,

		/// <summary>
		/// ..
		/// </summary>
		DotDotToken = 8222,






		IfKeyword = 8325,

		ReturnKeyword = 8341,

		EndOfFileToken = 8496,

		IfStatement = 8819,

	};
}
#endif
