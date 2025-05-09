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

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_INITIALIZERLIST
#include "../InitializerList.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_ABSOLUTE
#include "../Absolute.hpp"
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

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_HASOPERATORBITWISEAND
#include "../TypeTraits/HasOperatorBitwiseAnd.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_HASOPERATORBITWISEOR
#include "../TypeTraits/HasOperatorBitwiseOr.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_UNDERLYINGTYPE
#include "../TypeTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_UTILITY_MAKEINTEGERSEQUENCE
#include "../Utility/__MakeIntegerSequence.hpp"
#endif

namespace Elysium::Core::Template::RunTimeTypeInformation
{
	template <Concepts::Enumeration T>
	class Enumeration
	{
	public:
		using ConstValue = const T;
	public:
		/// <summary>
		/// Returns the full name of given type (namespace and enumeration-name).
		/// </summary>
		/// <returns></returns>
		static constexpr const Elysium::Core::Template::Text::String<char8_t> GetFullName() noexcept;
	public:
		/// <summary>
		/// Returns true if given value for given enum is defined, false otherwise.
		/// </summary>
		/// <typeparam name="Value"></typeparam>
		/// <returns></returns>
		template <T Value>
		static constexpr const bool IsDefinedValue() noexcept;

		/// <summary>
		/// Returns the name of given value for given enum (if defined) or it's underlying value.
		/// </summary>
		/// <typeparam name="Value"></typeparam>
		/// <returns></returns>
		template <T Value>
		static constexpr const Elysium::Core::Template::Text::String<char8_t> GetNamedValue() noexcept;
	public:
		/*
		* ATTENTION:
		* The following methods only work on specific enums since c++ does not support reflections out of the box yet.
		* That's why they need the additional concept ReflectableEnumeration - hopefully only for now. 
		*/

		/// <summary>
		/// Returns all defined values of given enum.
		/// </summary>
		/// <typeparam name="RE"></typeparam>
		/// <returns></returns>
		template <Concepts::ReflectableEnumeration RE = T>
		static constexpr const Elysium::Core::Template::Container::Vector<T> GetDefinedValues() noexcept;
		
		template <Concepts::ReflectableEnumeration RE = T>
		static constexpr const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::TypeTraits::UnderlyingTypeType<T>> GetUnderlyingValues() noexcept;
		
		template <Concepts::ReflectableEnumeration RE = T>
		static constexpr const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Text::String<char8_t>> GetNamedValues() noexcept;
	private:
		template <Elysium::Core::Template::Concepts::UnsignedInteger UI>
		static constexpr const Elysium::Core::Template::Container::Vector<T> GetDefinedValuesUsingUnderlyingType() noexcept;

		template <Elysium::Core::Template::Concepts::SignedInteger SI>
		static constexpr const Elysium::Core::Template::Container::Vector<T> GetDefinedValuesUsingUnderlyingType() noexcept;

		template <Elysium::Core::Template::System::uint64_t... Indices>
		static constexpr const Elysium::Core::Template::Container::Vector<T> CollectDefinedValues(const Elysium::Core::Template::Utility::IntegerSequence<Elysium::Core::Template::System::uint64_t, Indices...>&) noexcept;

		template <Elysium::Core::Template::System::int64_t... Indices>
		static constexpr const Elysium::Core::Template::Container::Vector<T> CollectDefinedValues(const Elysium::Core::Template::Utility::IntegerSequence<Elysium::Core::Template::System::int64_t, Indices...>&) noexcept;

		template <Elysium::Core::Template::Concepts::UnsignedInteger UI>
		static constexpr const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Text::String<char8_t>> GetNamedValuesUsingUnderlyingType() noexcept;

		template <Elysium::Core::Template::Concepts::SignedInteger SI>
		static constexpr const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Text::String<char8_t>> GetNamedValuesUsingUnderlyingType() noexcept;

		template <Elysium::Core::Template::System::uint64_t... Indices>
		static constexpr const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Text::String<char8_t>> CollectNamedValues(const Elysium::Core::Template::Utility::IntegerSequence<Elysium::Core::Template::System::uint64_t, Indices...>&) noexcept;

		template <Elysium::Core::Template::System::int64_t... Indices>
		static constexpr const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Text::String<char8_t>> CollectNamedValues(const Elysium::Core::Template::Utility::IntegerSequence<Elysium::Core::Template::System::int64_t, Indices...>&) noexcept;
	};

	template<Concepts::Enumeration T>
	inline constexpr const Elysium::Core::Template::Text::String<char8_t> Enumeration<T>::GetFullName() noexcept
	{
		constexpr const Elysium::Core::Template::System::size SkipFront = 66;	// Elysium::Core::Template::RunTimeTypeInformation::Enumeration<enum 
		constexpr const Elysium::Core::Template::System::size SkipBack = 14;	// >::GetFullName
		constexpr const char* FullName = __FUNCTION__;

		constexpr const char* NameStart = &FullName[SkipFront];
		constexpr const Elysium::Core::Template::System::size RequiredLength = Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(NameStart) - SkipBack;

		return Elysium::Core::Template::Text::String<char8_t>(reinterpret_cast<const char8_t*>(NameStart), RequiredLength);
	}

	template<Concepts::Enumeration T>
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
	
	template<Concepts::Enumeration T>
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

	template<Concepts::Enumeration T>
	template<Concepts::ReflectableEnumeration RE>
	inline constexpr const Elysium::Core::Template::Container::Vector<T> Enumeration<T>::GetDefinedValues() noexcept
	{
		return GetDefinedValuesUsingUnderlyingType<Elysium::Core::Template::TypeTraits::UnderlyingTypeType<T>>();
	}

	template<Concepts::Enumeration T>
	template<Concepts::ReflectableEnumeration RE>
	inline constexpr const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::TypeTraits::UnderlyingTypeType<T>> Enumeration<T>::GetUnderlyingValues() noexcept
	{
		const Elysium::Core::Template::Container::Vector<T> DefinedValues = GetDefinedValues();

		Elysium::Core::Template::Container::Vector<Elysium::Core::Template::TypeTraits::UnderlyingTypeType<T>> Result = 
			Elysium::Core::Template::Container::Vector<Elysium::Core::Template::TypeTraits::UnderlyingTypeType<T>>(DefinedValues.GetLength());
		Result.Clear();

		for (typename Elysium::Core::Template::Container::Vector<T>::ConstIterator Iterator = DefinedValues.GetBegin(); Iterator != DefinedValues.GetEnd(); ++Iterator)
		{
			Result.PushBack(static_cast<Elysium::Core::Template::TypeTraits::UnderlyingTypeType<T>>(*Iterator));
		}

		return Result;
	}
	
	template<Concepts::Enumeration T>
	template<Concepts::ReflectableEnumeration RE>
	inline constexpr const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Text::String<char8_t>> Enumeration<T>::GetNamedValues() noexcept
	{
		return GetNamedValuesUsingUnderlyingType<Elysium::Core::Template::TypeTraits::UnderlyingTypeType<T>>();
	}

	template<Concepts::Enumeration T>
	template<Elysium::Core::Template::Concepts::UnsignedInteger UI>
	inline constexpr const Elysium::Core::Template::Container::Vector<T> Enumeration<T>::GetDefinedValuesUsingUnderlyingType() noexcept
	{
		/*
		* Why use Elysium::Core::Template::System::uint64_t here? (Example: uint8_t)
		* The created integer sequence should contain values from minimum to maxmimum so in my example from 0 to 255.
		* MakeIntegerSequence takes the number of elements though which would be 256 (i.e. maximum + 1) which would cause an
		* overflow if I were to use the underlying type, meaning I need to use a bigger type and
		* I just decided to use "largest" integer type in general.
		*
		* There's still another issue:
		* The overflow is going to occurre regardless if the underlying type of given enum is 32 bit on 32 bit hardware or
		* 64 bit on 64 bit hardware.
		* Since I created the concept, ReflectableEnumeration, to only allow enums with an underlying type having a size of
		* 16 bit or less, this is not an issue for now!
		*/
		constexpr const Elysium::Core::Template::System::uint64_t RangeStart =
			Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::Template::TypeTraits::UnderlyingTypeType<T>>::Minimum;

		constexpr const Elysium::Core::Template::System::uint64_t RangeEnd =
			Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::Template::TypeTraits::UnderlyingTypeType<T>>::Maximum + 1;

		constexpr const Elysium::Core::Template::Utility::IntegerSequence Sequence =
			Elysium::Core::Template::Utility::MakeIntegerSequence<Elysium::Core::Template::System::uint64_t, RangeEnd>();

		return CollectDefinedValues(Sequence);
	}

	template<Concepts::Enumeration T>
	template<Elysium::Core::Template::Concepts::SignedInteger SI>
	inline constexpr const Elysium::Core::Template::Container::Vector<T> Enumeration<T>::GetDefinedValuesUsingUnderlyingType() noexcept
	{
		/*
		* Why use Elysium::Core::Template::System::int64_t here? (Example: int8_t)
		* The created integer sequence should contain values from minimum to maxmimum so in my example from -128 to 127.
		* MakeIntegerSequence takes the number of elements though which would be 256 which would cause an
		* overflow if I were to use the underlying type, meaning I need to use a bigger type and
		* I just decided to use "largest" integer type in general.
		*
		* There's still another issue:
		* The overflow is going to occurre regardless if the underlying type of given enum is 32 bit on 32 bit hardware or
		* 64 bit on 64 bit hardware.
		* Since I created the concept, ReflectableEnumeration, to only allow enums with an underlying type having a size of
		* 16 bit or less, this is not an issue for now!
		*/
		constexpr const Elysium::Core::Template::System::int64_t RangeStart =
			Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::Template::TypeTraits::UnderlyingTypeType<T>>::Minimum;

		constexpr const Elysium::Core::Template::System::int64_t Offset = Elysium::Core::Template::Math::Absolute(RangeStart);

		constexpr const Elysium::Core::Template::System::int64_t RangeEnd = Offset +
			Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::Template::TypeTraits::UnderlyingTypeType<T>>::Maximum + 1;

		constexpr const Elysium::Core::Template::Utility::IntegerSequence Sequence =
			Elysium::Core::Template::Utility::MakeIntegerSequence<Elysium::Core::Template::System::int64_t, RangeEnd>();

		return CollectDefinedValues(Sequence);
	}
	
	template<Concepts::Enumeration T>
	template<Elysium::Core::Template::System::uint64_t ...Indices>
	inline constexpr const Elysium::Core::Template::Container::Vector<T> Enumeration<T>::CollectDefinedValues(const Elysium::Core::Template::Utility::IntegerSequence<Elysium::Core::Template::System::uint64_t, Indices...>&) noexcept
	{
		using Sequence = typename Elysium::Core::Template::Utility::IntegerSequence<Elysium::Core::Template::System::uint64_t, Indices...>;
		
		Elysium::Core::Template::Container::Vector<T> Result = Elysium::Core::Template::Container::Vector<T>();
		(void)(..., 
			(Elysium::Core::Template::RunTimeTypeInformation::Enumeration<T>::IsDefinedValue<static_cast<T>(Indices)>() ? 
				(Result.PushBack(static_cast<T>(Indices)), 0) : 0)
			);

		return Result;
	}

	template<Concepts::Enumeration T>
	template<Elysium::Core::Template::System::int64_t ...Indices>
	inline constexpr const Elysium::Core::Template::Container::Vector<T> Enumeration<T>::CollectDefinedValues(const Elysium::Core::Template::Utility::IntegerSequence<Elysium::Core::Template::System::int64_t, Indices...>&) noexcept
	{
		using Sequence = typename Elysium::Core::Template::Utility::IntegerSequence<Elysium::Core::Template::System::int64_t, Indices...>;
		
		Elysium::Core::Template::Container::Vector<T> Result = Elysium::Core::Template::Container::Vector<T>();
		(void)(...,
			(Elysium::Core::Template::RunTimeTypeInformation::Enumeration<T>::IsDefinedValue<static_cast<T>(Indices)>() ?
				(Result.PushBack(static_cast<T>(Indices)), 0) : 0)
			);

		return Result;
	}

	template<Concepts::Enumeration T>
	template<Elysium::Core::Template::Concepts::UnsignedInteger UI>
	inline constexpr const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Text::String<char8_t>> Enumeration<T>::GetNamedValuesUsingUnderlyingType() noexcept
	{
		/*
		* Why use Elysium::Core::Template::System::uint64_t here? (Example: uint8_t)
		* The created integer sequence should contain values from minimum to maxmimum so in my example from 0 to 255.
		* MakeIntegerSequence takes the number of elements though which would be 256 (i.e. maximum + 1) which would cause an
		* overflow if I were to use the underlying type, meaning I need to use a bigger type and
		* I just decided to use "largest" integer type in general.
		*
		* There's still another issue:
		* The overflow is going to occurre regardless if the underlying type of given enum is 32 bit on 32 bit hardware or
		* 64 bit on 64 bit hardware.
		* Since I created the concept, ReflectableEnumeration, to only allow enums with an underlying type having a size of
		* 16 bit or less, this is not an issue for now!
		*/
		constexpr const Elysium::Core::Template::System::uint64_t RangeStart =
			Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::Template::TypeTraits::UnderlyingTypeType<T>>::Minimum;

		constexpr const Elysium::Core::Template::System::uint64_t RangeEnd =
			Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::Template::TypeTraits::UnderlyingTypeType<T>>::Maximum + 1;

		constexpr const Elysium::Core::Template::Utility::IntegerSequence Sequence =
			Elysium::Core::Template::Utility::MakeIntegerSequence<Elysium::Core::Template::System::uint64_t, RangeEnd>();

		return CollectNamedValues(Sequence);
	}
	
	template<Concepts::Enumeration T>
	template<Elysium::Core::Template::Concepts::SignedInteger SI>
	inline constexpr const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Text::String<char8_t>> Enumeration<T>::GetNamedValuesUsingUnderlyingType() noexcept
	{
		/*
		* Why use Elysium::Core::Template::System::int64_t here? (Example: int8_t)
		* The created integer sequence should contain values from minimum to maxmimum so in my example from -128 to 127.
		* MakeIntegerSequence takes the number of elements though which would be 256 which would cause an
		* overflow if I were to use the underlying type, meaning I need to use a bigger type and
		* I just decided to use "largest" integer type in general.
		*
		* There's still another issue:
		* The overflow is going to occurre regardless if the underlying type of given enum is 32 bit on 32 bit hardware or
		* 64 bit on 64 bit hardware.
		* Since I created the concept, ReflectableEnumeration, to only allow enums with an underlying type having a size of
		* 16 bit or less, this is not an issue for now!
		*/
		constexpr const Elysium::Core::Template::System::int64_t RangeStart =
			Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::Template::TypeTraits::UnderlyingTypeType<T>>::Minimum;

		constexpr const Elysium::Core::Template::System::int64_t Offset = Elysium::Core::Template::Math::Absolute(RangeStart);

		constexpr const Elysium::Core::Template::System::int64_t RangeEnd = Offset +
			Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::Template::TypeTraits::UnderlyingTypeType<T>>::Maximum + 1;

		constexpr const Elysium::Core::Template::Utility::IntegerSequence Sequence =
			Elysium::Core::Template::Utility::MakeIntegerSequence<Elysium::Core::Template::System::int64_t, RangeEnd>();

		return CollectNamedValues(Sequence);
	}

	template<Concepts::Enumeration T>
	template<Elysium::Core::Template::System::uint64_t ...Indices>
	inline constexpr const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Text::String<char8_t>> Enumeration<T>::CollectNamedValues(const Elysium::Core::Template::Utility::IntegerSequence<Elysium::Core::Template::System::uint64_t, Indices...>&) noexcept
	{
		using Sequence = typename Elysium::Core::Template::Utility::IntegerSequence<Elysium::Core::Template::System::uint64_t, Indices...>;

		Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Text::String<char8_t>> Result =
			Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Text::String<char8_t>>();
		(void)(...,
			(Elysium::Core::Template::RunTimeTypeInformation::Enumeration<T>::IsDefinedValue<static_cast<T>(Indices)>() ?
				(Result.PushBack(GetNamedValue<static_cast<T>(Indices)>()), 0) : 0)
			);

		return Result;
	}

	template<Concepts::Enumeration T>
	template<Elysium::Core::Template::System::int64_t ...Indices>
	inline constexpr const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Text::String<char8_t>> Enumeration<T>::CollectNamedValues(const Elysium::Core::Template::Utility::IntegerSequence<Elysium::Core::Template::System::int64_t, Indices...>&) noexcept
	{
		using Sequence = typename Elysium::Core::Template::Utility::IntegerSequence<Elysium::Core::Template::System::int64_t, Indices...>;

		Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Text::String<char8_t>> Result = 
			Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Text::String<char8_t>>();
		(void)(...,
			(Elysium::Core::Template::RunTimeTypeInformation::Enumeration<T>::IsDefinedValue<static_cast<T>(Indices)>() ?
				(Result.PushBack(GetNamedValue<static_cast<T>(Indices)>()), 0) : 0)
			);

		return Result;
	}
}
#endif
