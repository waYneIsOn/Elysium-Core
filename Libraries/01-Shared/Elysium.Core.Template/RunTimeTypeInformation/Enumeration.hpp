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

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_REFLECTABLEENUMERATION
#include "../Concepts/ReflectableEnumeration.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_SIGNEDINTEGER
#include "../SignedInteger.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_UNSIGNEDINTEGER
#include "../UnsignedInteger.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_ARRAY
#include "../Array.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_NUMERICTRAITS
#include "../NumericTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_RUNTIMETYPEINFORMATION_SOURCELOCATION
#include "SourceLocation.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#include "../CharacterTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "../String.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_UNDERLYINGTYPE
#include "../TypeTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_UTILITY_MAKEINTEGERSEQUENCE
#include "../Utility/__MakeIntegerSequence.hpp"
#endif

namespace Elysium::Core::Template::RunTimeTypeInformation
{
	template <Concepts::ReflectableEnumeration T>
	class Enumeration
	{
	public:
		using ConstValue = const T;
	public:
		template <T Value>
		static constexpr const Elysium::Core::Template::Text::String<char8_t> GetNamedValue() noexcept;

		//static constexpr const Elysium::Core::Template::Text::String<char8_t> GetNamedValues() noexcept;

		//static constexpr const Elysium::Core::Template::Text::String<char8_t> GetUnderlyingValues() noexcept;

		static constexpr const Elysium::Core::Template::Text::String<char8_t> GetFullName() noexcept;
		
		template <T Value>
		static constexpr const bool IsDefinedValue() noexcept;
		
		static constexpr const Elysium::Core::Template::Container::Vector<T> GetDefinedValues() noexcept;

		//static constexpr const bool IsFlag(ConstReference Value) noexcept;
	public: // @ToDo: make private or remove
		template <T... Values>
		static constexpr const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Text::String<char8_t>> GetNamedValues() noexcept;

		template <T... Values>
		static constexpr const Elysium::Core::Template::Container::Vector<typename Elysium::Core::Template::TypeTraits::UnderlyingType<T>::Type> 
			GetUnderlyingValues() noexcept;
	private:
		template <Elysium::Core::Template::System::size... Indices>
		static constexpr Elysium::Core::Template::Container::Array<bool, sizeof...(Indices)>
			GenerateAreDefinedValues(Elysium::Core::Template::Utility::IntegerSequence<Elysium::Core::Template::System::size, Indices...>);
	};

	template<Concepts::ReflectableEnumeration T>
	template<T Value>
	inline constexpr const Elysium::Core::Template::Text::String<char8_t> Enumeration<T>::GetNamedValue() noexcept
	{
		constexpr const Elysium::Core::Template::System::size SkipFront = 262;	// const class Elysium::Core::Template::Text::String<char8_t,struct Elysium::Core::Template::Text::CharacterTraits<char8_t>,class Elysium::Core::Template::Memory::DefaultAllocator<char8_t> > __cdecl Elysium::Core::Template::RunTimeTypeInformation::Enumeration<enum 
		constexpr const Elysium::Core::Template::System::size SkipBack = 16;	// >(void) noexcept
		constexpr const char* FullName = __FUNCSIG__;

		constexpr const char* InitialStart = &FullName[SkipFront];
		constexpr const Elysium::Core::Template::System::size InitialLength =
			Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(InitialStart);

		constexpr const Elysium::Core::Template::System::size StartIndexOfFullName =
			Elysium::Core::Template::Text::CharacterTraits<char>::LastIndexOf(InitialStart, InitialLength, '<') + sizeof(char);
		constexpr const char* FullNameStart = &FullName[SkipFront + StartIndexOfFullName];
		constexpr const Elysium::Core::Template::System::size FullNameLengthWithSkippedBack =
			Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(FullNameStart) - SkipBack;

		// Handle undefined value which looks like this: (enum SomeEnum)0xAB>(void) noexcept
		if (FullNameStart[0] == '(')
		{
			constexpr const Elysium::Core::Template::System::size StartIndex =
				Elysium::Core::Template::Text::CharacterTraits<char>::IndexOf(FullNameStart, FullNameLengthWithSkippedBack, ')') + sizeof(char);
			constexpr const char* NameStart = &FullNameStart[StartIndex];

			return Elysium::Core::Template::Text::String<char8_t>(reinterpret_cast<const char8_t*>(NameStart), FullNameLengthWithSkippedBack - StartIndex);

			// @ToDo: alternatively I could just remove everything in this scope and return a fixed value like so:
			//return Elysium::Core::Template::Text::String<char8_t>(u8"<undefined>");
		}

		constexpr const Elysium::Core::Template::System::size LastIndexOfNamespace =
			Elysium::Core::Template::Text::CharacterTraits<char>::LastIndexOf(FullNameStart, FullNameLengthWithSkippedBack, ':');

		// Handle global enums (no namespace, no ':')
		if (LastIndexOfNamespace == -1)
		{
			return Elysium::Core::Template::Text::String<char8_t>(reinterpret_cast<const char8_t*>(FullNameStart), FullNameLengthWithSkippedBack);
		}

		constexpr const char* NameStart = &FullNameStart[LastIndexOfNamespace] + sizeof(char);
		return Elysium::Core::Template::Text::String<char8_t>(reinterpret_cast<const char8_t*>(NameStart),
			FullNameLengthWithSkippedBack - LastIndexOfNamespace - sizeof(char));
	}

	template<Concepts::ReflectableEnumeration T>
	inline constexpr const Elysium::Core::Template::Text::String<char8_t> Enumeration<T>::GetFullName() noexcept
	{
		constexpr const Elysium::Core::Template::System::size SkipFront = 66;	// Elysium::Core::Template::RunTimeTypeInformation::Enumeration<enum 
		constexpr const Elysium::Core::Template::System::size SkipBack = 14;	// >::GetFullName
		constexpr const char* FullName = __FUNCTION__;

		constexpr const char* NameStart = &FullName[SkipFront];
		constexpr const Elysium::Core::Template::System::size RequiredLength = Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(NameStart) - SkipBack;

		return Elysium::Core::Template::Text::String<char8_t>(reinterpret_cast<const char8_t*>(NameStart), RequiredLength);
	}

	template<Concepts::ReflectableEnumeration T>
	template<T Value>
	inline constexpr const bool Enumeration<T>::IsDefinedValue() noexcept
	{
		constexpr const Elysium::Core::Template::System::size SkipFront = 85;	// const bool __cdecl Elysium::Core::Template::RunTimeTypeInformation::Enumeration<enum 
		constexpr const Elysium::Core::Template::System::size SkipBack = 16;	// >(void) noexcept
		constexpr const char* FullName = __FUNCSIG__;

		constexpr const char* InitialStart = &FullName[SkipFront];
		constexpr const Elysium::Core::Template::System::size InitialLength = 
			Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(InitialStart);

		constexpr const Elysium::Core::Template::System::size StartIndexOfName =
			Elysium::Core::Template::Text::CharacterTraits<char>::LastIndexOf(InitialStart, InitialLength, '<') + sizeof(char);
		constexpr const char* NameStart = &FullName[SkipFront + StartIndexOfName];
		constexpr const Elysium::Core::Template::System::size NameLength =
			Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(NameStart) - SkipBack;

		// NameStart for a defined value looks something like this: SomeName>(void) noexcept
		// while an invalid name might look something like this: (enum SomeEnum)0x7b>(void) noexcept
		// Ergo looking up '(' within the bounds of SkipBack will tell whether a value is defined or not.
		constexpr const Elysium::Core::Template::System::size UndefinedIndex =
			Elysium::Core::Template::Text::CharacterTraits<char>::LastIndexOf(NameStart, NameLength, '(');

		return UndefinedIndex == static_cast<Elysium::Core::Template::System::size>(-1) ? true : false;
	}

	template<Concepts::ReflectableEnumeration T>
	inline constexpr const Elysium::Core::Template::Container::Vector<T> Enumeration<T>::GetDefinedValues() noexcept
	{
		/*
		* Why use Elysium::Core::Template::System::size here? (Example: uint8_t)
		* The created integer sequence should contain values from minimum to maxmimum so in my example from 0 to 255.
		* MakeIntegerSequence takes the number of elements though which would be 256 (i.e. maximum + 1) which would cause an
		* overflow if I were to use the underlying type, meaning I need to use a bigger type and 
		* I just decided to use "largest" type in general.
		* 
		* This still causes another issue:
		* The overflow still is going to occurre if the underlying type of given enum is 32 bit on 32 bit hardware or
		* 64 bit on 64 bit hardware.
		* Since I only allow enums with an underlying type of 16bit or less, this is not an issue for now!
		* 
		*/

		constexpr const Elysium::Core::Template::System::size RangeStart =
			Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::Template::TypeTraits::UnderlyingTypeType<T>>::Minimum;

		constexpr const Elysium::Core::Template::System::size RangeEnd =
			Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::Template::TypeTraits::UnderlyingTypeType<T>>::Maximum + 1;

		// @ToDo: The created integer sequence only works for underlying UNSIGNED integer types atm!
		constexpr const Elysium::Core::Template::Utility::IntegerSequence Sequence =
			Elysium::Core::Template::Utility::MakeIntegerSequence<Elysium::Core::Template::System::size, RangeEnd>();

		constexpr const Elysium::Core::Template::Container::Array<bool, RangeEnd> AreDefinedValues = GenerateAreDefinedValues(Sequence);

		Elysium::Core::Template::Container::Vector<T> DefinedValues = Elysium::Core::Template::Container::Vector<T>();
		for (Elysium::Core::Template::System::size i = RangeStart; i < RangeEnd; i++)
		{
			if (AreDefinedValues[i])
			{
				DefinedValues.PushBack(static_cast<T>(i));
			}
		}

		return DefinedValues;
	}

	template<Concepts::ReflectableEnumeration T>
	template<T... Values>
	inline constexpr const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Text::String<char8_t>> Enumeration<T>::GetNamedValues() noexcept
	{
		constexpr const Elysium::Core::Template::System::size SkipFront = 629;	// const class Elysium::Core::Template::Container::Vector<class Elysium::Core::Template::Text::String<char8_t,struct Elysium::Core::Template::Text::CharacterTraits<char8_t>,class Elysium::Core::Template::Memory::DefaultAllocator<char8_t> >,class Elysium::Core::Template::Memory::DefaultAllocator<class Elysium::Core::Template::Text::String<char8_t,struct Elysium::Core::Template::Text::CharacterTraits<char8_t>,class Elysium::Core::Template::Memory::DefaultAllocator<char8_t> > > > __cdecl Elysium::Core::Template::RunTimeTypeInformation::Enumeration<enum UnitTests::Core::Template::Reflection::SomeInt32EnumClass>::GetNamedValues<
		constexpr const Elysium::Core::Template::System::size SkipBack = 16;	// >(void) noexcept
		constexpr const char* FullName = __FUNCSIG__;

		char* NameStart = const_cast<char*>(&FullName[SkipFront]);
		Elysium::Core::Template::System::size RemainingLength = Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(NameStart) - SkipBack;

		constexpr const Elysium::Core::Template::System::size ParameterPackLength =
			Elysium::Core::Template::Utility::IntegerSequence<T, Values...>::GetLength();
		Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Text::String<char8_t>> Result =
			Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Text::String<char8_t>>(ParameterPackLength);

		for (Elysium::Core::Template::System::size i = 0; i < ParameterPackLength; i++)
		{
			char* CurrentFullName = NameStart;
			char* RemainingNames = Elysium::Core::Template::Text::CharacterTraits<char>::Find(NameStart, RemainingLength, ',');

			const Elysium::Core::Template::System::size CurrentFullNameSize = RemainingNames == nullptr ?
				RemainingLength - SkipBack : RemainingNames - NameStart;
			const Elysium::Core::Template::System::size CurrentNameSpaceEndIndex =
				Elysium::Core::Template::Text::CharacterTraits<char>::LastIndexOf(CurrentFullName, CurrentFullNameSize, ':');
			const char* CurrentName = &CurrentFullName[CurrentNameSpaceEndIndex + sizeof(char)];

			Result.PushBack(Elysium::Core::Template::Functional::Move(
				Elysium::Core::Template::Text::String<char8_t>(reinterpret_cast<const char8_t*>(CurrentName), RemainingNames - CurrentName)));

			NameStart = RemainingNames + sizeof(char);
			RemainingLength -= (RemainingNames - NameStart + sizeof(char));
		}

		return Result;
	}

	template<Concepts::ReflectableEnumeration T>
	template<T ...Values>
	inline constexpr const Elysium::Core::Template::Container::Vector<typename Elysium::Core::Template::TypeTraits::UnderlyingType<T>::Type> Enumeration<T>::GetUnderlyingValues() noexcept
	{
		constexpr const Elysium::Core::Template::System::size ParameterPackLength =
			Elysium::Core::Template::Utility::IntegerSequence<T, Values...>::GetLength();
		Elysium::Core::Template::Container::Vector<Elysium::Core::Template::TypeTraits::UnderlyingTypeType<T>> Result =
			Elysium::Core::Template::Container::Vector<Elysium::Core::Template::TypeTraits::UnderlyingTypeType<T>>(ParameterPackLength);

		for (const T Value : { Values... })
		{
			Result.PushBack(static_cast<Elysium::Core::Template::TypeTraits::UnderlyingType<T>::Type>(Value));
		}

		return Result;
	}

	template<Concepts::ReflectableEnumeration T>
	template<Elysium::Core::Template::System::size ...Indices>
	inline constexpr Elysium::Core::Template::Container::Array<bool, sizeof...(Indices)> Enumeration<T>::GenerateAreDefinedValues(Elysium::Core::Template::Utility::IntegerSequence<Elysium::Core::Template::System::size, Indices...>)
	{
		//return { (static_cast<T>(Indices))... };
		//return { Elysium::Core::Template::RunTimeTypeInformation::Enumeration<T>::IsDefinedValue<(static_cast<T>(1))>() };
		return { (Elysium::Core::Template::RunTimeTypeInformation::Enumeration<T>::IsDefinedValue<static_cast<T>(Indices)>())... };
	}
}
#endif
