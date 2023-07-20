/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_RUNTIMETYPEINFORMATION_ENUMERATION
#define ELYSIUM_CORE_TEMPLATE_RUNTIMETYPEINFORMATION_ENUMERATION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_ENUMERATION
#include "../Concepts/Enumeration.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#include "CharacterTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "String.hpp"
#endif

namespace Elysium::Core::Template::RunTimeTypeInformation
{
	template <Concepts::Enumeration T>
	class Enumeration
	{
	public:
		template <T Value>
		inline static constexpr const Elysium::Core::Template::Text::String<char8_t> GetName() noexcept;

		inline static constexpr const Elysium::Core::Template::Text::String<char8_t> GetValues() noexcept;

		inline static constexpr const Elysium::Core::Template::Text::String<char8_t> ToString() noexcept;
	};
	
	template<Concepts::Enumeration T>
	template<T Value>
	inline constexpr const Elysium::Core::Template::Text::String<char8_t> Enumeration<T>::GetName() noexcept
	{
		constexpr const Elysium::Core::Template::System::size SkipFront = 262;	// const class Elysium::Core::Template::Text::String<char8_t,struct Elysium::Core::Template::Text::CharacterTraits<char8_t>,class Elysium::Core::Template::Memory::DefaultAllocator<char8_t> > __cdecl Elysium::Core::Template::RunTimeTypeInformation::Enumeration<enum 
		constexpr const Elysium::Core::Template::System::size SkipBack = 16;	// >(void) noexcept
		constexpr const char* Name = __FUNCSIG__;

		constexpr const char* NameInitialStart = &Name[SkipFront];
		constexpr const Elysium::Core::Template::System::size InitialLength =
			Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(NameInitialStart);

		constexpr const Elysium::Core::Template::System::size StartIndex =
			Elysium::Core::Template::Text::CharacterTraits<char>::LastIndexOf(NameInitialStart, InitialLength, ':');
		if (StartIndex == static_cast<Elysium::Core::Template::System::size>(-1))
		{
			return Elysium::Core::Template::Text::String<char8_t>();
		}

		constexpr const char* NameStart = &NameInitialStart[StartIndex + 1];
		constexpr const Elysium::Core::Template::System::size RequiredLength =
			Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(NameStart) - SkipBack;

		return Elysium::Core::Template::Text::String<char8_t>((char8_t*)NameStart, RequiredLength);
	}

	template<Concepts::Enumeration T>
	inline constexpr const Elysium::Core::Template::Text::String<char8_t> Enumeration<T>::GetValues() noexcept
	{
		return Elysium::Core::Template::Text::String<char8_t>();
	}

	template<Concepts::Enumeration T>
	inline constexpr const Elysium::Core::Template::Text::String<char8_t> Enumeration<T>::ToString() noexcept
	{
		constexpr const Elysium::Core::Template::System::size SkipFront = 262;	// const class Elysium::Core::Template::Text::String<char8_t,struct Elysium::Core::Template::Text::CharacterTraits<char8_t>,class Elysium::Core::Template::Memory::DefaultAllocator<char8_t> > __cdecl Elysium::Core::Template::RunTimeTypeInformation::Enumeration<enum 
		constexpr const Elysium::Core::Template::System::size SkipBack = 26;	// >::ToString(void) noexcept
		constexpr const char* Name = __FUNCSIG__;

		constexpr const char* NameStart = &Name[SkipFront];
		constexpr const Elysium::Core::Template::System::size RequiredLength = Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(NameStart) - SkipBack;

		return Elysium::Core::Template::Text::String<char8_t>((char8_t*)NameStart, RequiredLength);
	}
}
#endif
