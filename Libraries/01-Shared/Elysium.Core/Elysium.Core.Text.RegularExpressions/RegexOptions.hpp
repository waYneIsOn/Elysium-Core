/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEXT_REGULAREXPRESSIONS
#define ELYSIUM_CORE_TEXT_REGULAREXPRESSIONS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Text::RegularExpressions
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class RegexOptions : Elysium::Core::uint16_t
#elif defined(__ANDROID__)
	enum class RegexOptions
#else
#error "undefined os"
#endif
	{
		None = 0,
		IgnoreCase = 1,
		Multiline = 2,
		ExplicitCapture = 4,
		Compiled = 8,
		Singleline = 16,
		IgnorePatternWhitespace = 32,
		RightToLeft = 64,

		ECMAScript = 256,
		CultureInvariant = 512
	};

	inline RegexOptions operator|(RegexOptions Left, RegexOptions Right)
	{
		return static_cast<RegexOptions>(static_cast<Elysium::Core::uint16_t>(Left) | static_cast<Elysium::Core::uint16_t>(Right));
	}
	inline RegexOptions operator&(RegexOptions Left, RegexOptions Right)
	{
		return static_cast<RegexOptions>(static_cast<Elysium::Core::uint16_t>(Left) & static_cast<Elysium::Core::uint16_t>(Right));
	}
}
#endif