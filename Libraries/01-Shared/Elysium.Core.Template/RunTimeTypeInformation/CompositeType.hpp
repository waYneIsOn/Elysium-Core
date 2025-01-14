/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_RUNTIMETYPEINFORMATION_COMPOSITETYPE
#define ELYSIUM_CORE_TEMPLATE_RUNTIMETYPEINFORMATION_COMPOSITETYPE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_COMPOSITETYPE
#include "../Concepts/CompositeType.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#include "../CharacterTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "../String.hpp"
#endif

namespace Elysium::Core::Template::RunTimeTypeInformation
{
	template <Elysium::Core::Template::Concepts::CompositeType T>
	class CompositeType
	{
	public:
		/// <summary>
		/// Returns whether composite-type is a class or not.
		/// </summary>
		/// <returns></returns>
		static constexpr const bool IsClass() noexcept;

		/// <summary>
		/// Returns whether composite-type is a struct or not.
		/// </summary>
		/// <returns></returns>
		static constexpr const bool IsStruct() noexcept;
	public:
		/// <summary>
		/// Returns the full name of given type (namespace and class-/stuct-name).
		/// </summary>
		/// <returns></returns>
		static constexpr const Elysium::Core::Template::Text::String<char8_t> GetFullName() noexcept;
	public:
		template <class Field>
		static constexpr const Elysium::Core::Template::Text::String<char8_t> GetFieldTypeName() noexcept;
	};

	template<Elysium::Core::Template::Concepts::CompositeType T>
	inline constexpr const bool CompositeType<T>::IsClass() noexcept
	{
		constexpr const Elysium::Core::Template::System::size SkipFront = 82;	// const bool __cdecl Elysium::Core::Template::RunTimeTypeInformation::CompositeType<
		constexpr const char* FullName = __FUNCSIG__;

		constexpr const char* InitialStart = &FullName[SkipFront];

		// InitialStart starts with "class " or "struct ", meaning I don't have to calculate the length
		return Elysium::Core::Template::Text::CharacterTraits<char>::StartsWith(InitialStart, 7, "class ", 6);
	}

	template<Elysium::Core::Template::Concepts::CompositeType T>
	inline constexpr const bool CompositeType<T>::IsStruct() noexcept
	{
		constexpr const Elysium::Core::Template::System::size SkipFront = 82;	// const bool __cdecl Elysium::Core::Template::RunTimeTypeInformation::CompositeType<
		constexpr const char* FullName = __FUNCSIG__;

		constexpr const char* InitialStart = &FullName[SkipFront];

		// InitialStart starts with "class " or "struct ", meaning I don't have to calculate the length
		return Elysium::Core::Template::Text::CharacterTraits<char>::StartsWith(InitialStart, 7, "struct ", 7);
	}

	template<Elysium::Core::Template::Concepts::CompositeType T>
	inline constexpr const Elysium::Core::Template::Text::String<char8_t> CompositeType<T>::GetFullName() noexcept
	{
		constexpr const Elysium::Core::Template::System::size SkipFront = 259;	// const class Elysium::Core::Template::Text::String<char8_t,struct Elysium::Core::Template::Text::CharacterTraits<char8_t>,class Elysium::Core::Template::Memory::DefaultAllocator<char8_t> > __cdecl Elysium::Core::Template::RunTimeTypeInformation::CompositeType<
		constexpr const Elysium::Core::Template::System::size SkipBack = 16;	// >(void) noexcept
		constexpr const char* FullName = __FUNCSIG__;

		constexpr const char* InitialStart = &FullName[SkipFront];

		// InitialStart starts with "class " or "struct ", meaning I don't have to calculate the length
		constexpr const Elysium::Core::Template::System::size IndexOfWhiteSpace =
			Elysium::Core::Template::Text::CharacterTraits<char>::IndexOf(InitialStart, 7, ' ') + sizeof(char);

		constexpr const char* FullNameStart = &InitialStart[IndexOfWhiteSpace];
		constexpr const Elysium::Core::Template::System::size FullNameLength =
			Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(FullNameStart);

		constexpr const Elysium::Core::Template::System::size IndexOfGreaterThan =
			Elysium::Core::Template::Text::CharacterTraits<char>::IndexOf(FullNameStart, FullNameLength, '>');

		return Elysium::Core::Template::Text::String<char8_t>(reinterpret_cast<const char8_t*>(FullNameStart), IndexOfGreaterThan);
	}

	template<Elysium::Core::Template::Concepts::CompositeType T>
	template<class Field>
	inline constexpr const Elysium::Core::Template::Text::String<char8_t> CompositeType<T>::GetFieldTypeName() noexcept
	{
		constexpr const Elysium::Core::Template::System::size SkipFront = 259;	// const class Elysium::Core::Template::Text::String<char8_t,struct Elysium::Core::Template::Text::CharacterTraits<char8_t>,class Elysium::Core::Template::Memory::DefaultAllocator<char8_t> > __cdecl Elysium::Core::Template::RunTimeTypeInformation::CompositeType<
		constexpr const Elysium::Core::Template::System::size SkipBack = 16;	// >(void) noexcept
		constexpr const char* FullName = __FUNCSIG__;

		constexpr const char* InitialStart = &FullName[SkipFront];
		constexpr const Elysium::Core::Template::System::size InitialLength =
			Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(InitialStart);

		constexpr const Elysium::Core::Template::System::size StartIndexOfMethodName =
			Elysium::Core::Template::Text::CharacterTraits<char>::IndexOf(InitialStart, InitialLength, '>') + sizeof(char);
		constexpr const char* MethodNameStart = &InitialStart[StartIndexOfMethodName];

		constexpr const Elysium::Core::Template::System::size SkipMethodName = 19; // ::GetFieldTypeName<
		constexpr const char* TypeNameStart = &MethodNameStart[SkipMethodName];

		constexpr const Elysium::Core::Template::System::size TypeNameLength =
			Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(TypeNameStart);
		constexpr const Elysium::Core::Template::System::size IndexOfGreaterThan =
			Elysium::Core::Template::Text::CharacterTraits<char>::IndexOf(TypeNameStart, TypeNameLength, '>') + sizeof(char);
		constexpr const Elysium::Core::Template::System::size IndexOfWhiteSpace =
			Elysium::Core::Template::Text::CharacterTraits<char>::IndexOf(TypeNameStart, TypeNameLength, ' ') + sizeof(char);

		if constexpr (IndexOfGreaterThan > IndexOfWhiteSpace)
		{	// "enum xy", "class xy", "struct xy" etc.
			constexpr const char* ComplexTypeNameStart = &TypeNameStart[IndexOfWhiteSpace];
			constexpr const Elysium::Core::Template::System::size ComplexTypeNameLengthWithSkippedBack =
				Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(ComplexTypeNameStart) - SkipBack;

			return Elysium::Core::Template::Text::String<char8_t>(reinterpret_cast<const char8_t*>(ComplexTypeNameStart), ComplexTypeNameLengthWithSkippedBack);
		}
		else
		{	// "int", "float" etc.
			constexpr const Elysium::Core::Template::System::size TypeNameLengthWithSkippedBack =
				Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(TypeNameStart) - SkipBack;
			return Elysium::Core::Template::Text::String<char8_t>(reinterpret_cast<const char8_t*>(TypeNameStart), TypeNameLengthWithSkippedBack);
		}
	}
}
#endif
