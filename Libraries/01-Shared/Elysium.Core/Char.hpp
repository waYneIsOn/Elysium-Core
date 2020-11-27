/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

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

#ifndef ELYSIUM_CORE_INTEGER
#include "Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_GLOBALIZATION_UNICODECATEGORY
#include "UnicodeCategory.hpp"
#endif

namespace Elysium::Core
{
	namespace Collections::Template
	{
		template <typename T>
		class StringBase;
	}
	using String = Collections::Template::StringBase<char>;

	class ELYSIUM_CORE_API Char final
	{
	public:
		Char() = delete;
		Char(const Char& Right) = delete;
		Char(Char&& Right) noexcept = delete;
		~Char() = delete;

		Char& operator=(const Char& Source) = delete;
		Char& operator=(Char&& Right) noexcept = delete;

		static const unsigned char MaxValue;
		static const unsigned char MinValue;

		//static const double GetNumericValue(const char8_t Value);
		//static const double GetNumericValue(const char8_t* Value);

		//static const Elysium::Core::Globalization::UnicodeCategory GetUnicodeCategory(const char8_t Value);
		//static const Elysium::Core::Globalization::UnicodeCategory GetUnicodeCategory(const char8_t* Value);

		//static const bool IsControl(const char8_t Value);
		//static const bool IsControl(const char8_t* Value);

		//static const bool IsDigit(const char8_t Value);
		//static const bool IsDigit(const char8_t* Value);

		//static const bool IsLetter(const char8_t Value);
		//static const bool IsLetter(const char8_t* Value);

		//static const bool IsLetterOrDigit(const char8_t Value);
		//static const bool IsLetterOrDigit(const char8_t* Value);

		//static const bool IsLower(const char8_t Value);
		//static const bool IsLower(const char8_t* Value);

		//static const bool IsNumber(const char8_t Value);
		//static const bool IsNumber(const char8_t* Value);

		//static const bool IsPunctuation(const char8_t Value);
		//static const bool IsPunctuation(const char8_t* Value);

		//static const bool IsSeparator(const char8_t Value);
		//static const bool IsSeparator(const char8_t* Value);

		//static const bool IsSymbol(const char8_t Value);
		//static const bool IsSymbol(const char8_t* Value);

		//static const bool IsUpper(const char8_t Value);
		//static const bool IsUpper(const char8_t* Value);

		//static const bool IsWhiteSpace(const char8_t Value);
		//static const bool IsWhiteSpace(const char8_t* Value);

		//static const Char ToLower(const char8_t Value);

		//static const Char ToLowerInvariant(const char8_t Value);

		//static const Char ToUpper(const char8_t Value);

		//static const Char ToUpperInvariant(const char8_t Value);

		//const Elysium::Core::String ToString() const;	
	};
}
#endif
