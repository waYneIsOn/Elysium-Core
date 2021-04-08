/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_CHAR
#define ELYSIUM_CORE_CHAR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_GLOBALIZATION_UNICODECATEGORY
#include "../Elysium.Core.Globalization/UnicodeCategory.hpp"
#endif

namespace Elysium::Core
{
	class String;

	class ELYSIUM_CORE_API Char final
	{
	public:
		Char() = delete;
		Char(const Char& Right) = delete;
		Char(Char&& Right) noexcept = delete;
		~Char() = delete;

		Char& operator=(const Char& Source) = delete;
		Char& operator=(Char&& Right) noexcept = delete;

		//static constexpr const char8_t MaxValue = 0xFF;

		static constexpr const char8_t MinValue = 0x00;

		static const Elysium::Core::String ConvertFromUtf32(const Elysium::Core::uint32_t CodePoint);

		static const Elysium::Core::uint32_t ConvertToUtf32(const char8_t* Input);

		//static const double GetNumericValue(const char8_t Value);

		//static const Elysium::Core::Globalization::UnicodeCategory GetUnicodeCategory(const char8_t Value);

		static const bool IsControl(const char8_t Character, const char8_t FollowUpCharacter = 0x00) noexcept;

		static const bool IsDigit(const char8_t Character) noexcept;

		static const bool IsLeadByte(const char8_t Character) noexcept;

		//static const bool IsLetter(const char8_t Character);

		//static const bool IsLetterOrDigit(const char8_t Character);

		//static const bool IsLower(const char8_t Character);

		//static const bool IsNumber(const char8_t Character);

		//static const bool IsPunctuation(const char8_t Character);

		//static const bool IsSeparator(const char8_t Character);

		//static const bool IsSymbol(const char8_t Character);

		static const bool IsTrailByte(const char8_t Character) noexcept;

		//static const bool IsUpper(const char8_t Character);

		//static const bool IsWhiteSpace(const char8_t Character);

		//static const Char ToLower(const char8_t Character);

		//static const Char ToLowerInvariant(const char8_t Character);

		//static const Char ToUpper(const char8_t Character);

		//static const Char ToUpperInvariant(const char8_t Character);

		//const Elysium::Core::String ToString() const;	
	};
}
#endif
