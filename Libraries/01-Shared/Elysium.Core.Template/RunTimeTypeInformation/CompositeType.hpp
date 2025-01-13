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
		template <class Field>
		static constexpr const Elysium::Core::Template::Text::String<char8_t> GetFieldTypeName() noexcept
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
			constexpr const Elysium::Core::Template::System::size IndexOfSpace =
				Elysium::Core::Template::Text::CharacterTraits<char>::IndexOf(TypeNameStart, TypeNameLength, ' ') + sizeof(char);

			if constexpr (IndexOfGreaterThan > IndexOfSpace)
			{	// "enum xy", "class xy", "struct xy" etc.
				constexpr const char* ComplexTypeNameStart = &TypeNameStart[IndexOfSpace];
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
	};
}
#endif
