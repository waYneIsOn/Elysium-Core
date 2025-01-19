/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_INTERNAL_LANGUAGE
#define ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_INTERNAL_LANGUAGE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_INTERNAL_LANGUAGESCOPE
#include "LanguageScope.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_INTERNAL_LANGUAGETYPE
#include "LanguageType.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "../../String.hpp"
#endif

namespace Elysium::Core::Template::Globalization::Internal
{
	class Language final
	{
		// https://www.loc.gov/standards/iso639-2/php/code_list.php
		// - dialects en-EN, en-GB
	public:
		constexpr Language(const char8_t* Name, const char8_t* Iso639_1, const LanguageScope Scope = LanguageScope::Individual, 
			const LanguageType Type = LanguageType::Living) noexcept;

		constexpr Language(const Language& Source) noexcept = delete;

		constexpr Language(Language&& Source) noexcept = delete;

		constexpr ~Language() noexcept;
	public:
		constexpr Language& operator=(const Language& Source) noexcept = delete;

		constexpr Language& operator=(Language&& Right) noexcept = delete;
	private:
		const char8_t* _Name;
		const char8_t* _Iso639_1;
		const LanguageScope _Scope;
		const LanguageType _Type;
		//char8_t _Iso693_1Code[2];	// guaranteed to be two letters and one value per language
		//char8_t _Iso693_2Code[3];	// example of multiple: fre/fra
		//char8_t _Iso693_3Code[3];	// can have multiple - example albanian = sqi but four individual language codes: aae, aat, aln, als
	};

	inline constexpr Elysium::Core::Template::Globalization::Internal::Language::Language(const char8_t* Name, const char8_t* Iso639_1, const LanguageScope Scope, const LanguageType Type) noexcept
		: _Name(Name), _Iso639_1(Iso639_1), _Scope(Scope), _Type(Type)
	{ }

	inline constexpr Elysium::Core::Template::Globalization::Internal::Language::~Language() noexcept
	{ }

	constexpr Language Abkhazian(u8"Abkhazian", u8"ab");

}
#endif
