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

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_NUMERICTRAITS
#include "../NumericTraits.hpp"
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

#ifndef ELYSIUM_CORE_TEMPLATE_UTILITY_INTEGERSEQUENCE
#include "../Utility/IntegerSequence.hpp"
#endif

namespace Elysium::Core::Template::RunTimeTypeInformation
{
	template <Concepts::Enumeration T>
	class Enumeration
	{
	public:
		using ConstValue = const T;
		using ConstReference = const T&;
	public:
		template <T Value>
		static constexpr const Elysium::Core::Template::Text::String<char8_t> GetNamedValue() noexcept;

		//static constexpr const Elysium::Core::Template::Text::String<char8_t> GetNamedValues() noexcept;

		//static constexpr const Elysium::Core::Template::Text::String<char8_t> GetUnderlyingValues() noexcept;

		static constexpr const Elysium::Core::Template::Text::String<char8_t> GetFullName() noexcept;
		
		template <T Value>
		static constexpr const bool IsDefinedValue() noexcept;
		
		static constexpr const bool IsDefinedValue(ConstValue Value) noexcept;

		static constexpr const T GetMinimumValue() noexcept;

		//static constexpr const bool IsFlag(ConstReference Value) noexcept;
	public: // @ToDo: private:
		template <T... Values>
		static constexpr const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Text::String<char8_t>> GetNamedValues() noexcept;

		template <T... Values>
		static constexpr const Elysium::Core::Template::Container::Vector<typename Elysium::Core::Template::TypeTraits::UnderlyingType<T>::Type> 
			GetUnderlyingValues() noexcept;
	};
	
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
		constexpr const Elysium::Core::Template::System::size NameLength =
			Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(FullNameStart) - SkipBack;




		// @ToDo: doesn't work with global enums
		constexpr const Elysium::Core::Template::System::size StartIndex =
			Elysium::Core::Template::Text::CharacterTraits<char>::LastIndexOf(InitialStart, InitialLength, ':');
		if (StartIndex == static_cast<Elysium::Core::Template::System::size>(-1))
		{
			return Elysium::Core::Template::Text::String<char8_t>();
		}

		constexpr const char* NameStartX = &InitialStart[StartIndex + 1];
		constexpr const Elysium::Core::Template::System::size RequiredLength =
			Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(NameStartX) - SkipBack;

		return Elysium::Core::Template::Text::String<char8_t>((char8_t*)NameStartX, RequiredLength);
	}

	template<Concepts::Enumeration T>
	inline constexpr const Elysium::Core::Template::Text::String<char8_t> Enumeration<T>::GetFullName() noexcept
	{
		constexpr const Elysium::Core::Template::System::size SkipFront = 66;	// Elysium::Core::Template::RunTimeTypeInformation::Enumeration<enum 
		constexpr const Elysium::Core::Template::System::size SkipBack = 14;	// >::GetFullName
		constexpr const char* FullName = __FUNCTION__;

		constexpr const char* NameStart = &FullName[SkipFront];
		constexpr const Elysium::Core::Template::System::size RequiredLength = Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(NameStart) - SkipBack;

		return Elysium::Core::Template::Text::String<char8_t>((char8_t*)NameStart, RequiredLength);
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
	inline constexpr const bool Enumeration<T>::IsDefinedValue(ConstValue Value) noexcept
	{
		constexpr const Elysium::Core::Template::System::size SkipFront = 85;	// 
		constexpr const Elysium::Core::Template::System::size SkipBack = 10;	// ) noexcept
		constexpr const char* FullName1 = __FUNCTION__;
		constexpr const char* FullName2 = __FUNCDNAME__;
		constexpr const char* FullName3 = __FUNCSIG__;
		constexpr const wchar_t* FullName4 = __FUNCTIONW__;
		constexpr const char* FullName5 = __func__;
		//constexpr const char* FullName6 = __PRETTY_FUNCTION__;
		constexpr const int FullName7 = __LINE__;
		constexpr const char* FullName8 = __FILE__;


		return false;
	}

	template<Concepts::Enumeration T>
	inline constexpr const T Enumeration<T>::GetMinimumValue() noexcept
	{
		constexpr const Elysium::Core::Template::TypeTraits::UnderlyingTypeType<T> RangeStart =
			Elysium::Core::Template::Numeric::NumericTraits<UnderlyingTypeType<T>>::Minimum;

		constexpr const Elysium::Core::Template::TypeTraits::UnderlyingTypeType<T> RangeEnd =
			Elysium::Core::Template::Numeric::NumericTraits<UnderlyingTypeType<T>>::Maximum;
		
		for (Elysium::Core::Template::TypeTraits::UnderlyingTypeType<T> i = RangeStart; i < RangeEnd; i++)
		{
			const T CurrentValue = static_cast<T>(i);

			IsDefinedValue(CurrentValue);
			//IsDefinedValue<&CurrentValue>();
			/*
			const bool kjsdf1 = Enumeration<T>::IsDefinedValue<CurrentValue>();
			const bool kjsdf2 = Enumeration<T>::IsDefinedValue(CurrentValue);
			*/
			bool dfg = false;
		}
		
		return T();
	}

	template<Concepts::Enumeration T>
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
				Elysium::Core::Template::Text::String<char8_t>((char8_t*)CurrentName, RemainingNames - CurrentName)));




			Elysium::Core::Template::Text::String<char> CurrentFullNameX =
				Elysium::Core::Template::Text::String<char>(CurrentName, RemainingNames - CurrentName);



			/*
			if (RemainingNames == nullptr)
			{
				Elysium::Core::Template::Text::String<char> CurrentFullName =
					Elysium::Core::Template::Text::String<char>(NameStart, RemainingLength - SkipBack);
				
				Result.PushBack(Elysium::Core::Template::Functional::Move(
					Elysium::Core::Template::Text::String<char8_t>((char8_t*)NameStart, RemainingLength - SkipBack)));
			}
			else
			{
				Elysium::Core::Template::Text::String<char> CurrentFullName =
					Elysium::Core::Template::Text::String<char>(NameStart, RemainingNames - NameStart);
				
				Result.PushBack(Elysium::Core::Template::Functional::Move(
					Elysium::Core::Template::Text::String<char8_t>((char8_t*)NameStart, RemainingNames - NameStart)));
			}
			*/


			NameStart = RemainingNames + sizeof(char);
			RemainingLength -= (RemainingNames - NameStart + sizeof(char));
		}

		return Result;
	}

	template<Concepts::Enumeration T>
	template<T ...Values>
	inline constexpr const Elysium::Core::Template::Container::Vector<typename Elysium::Core::Template::TypeTraits::UnderlyingType<T>::Type> Enumeration<T>::GetUnderlyingValues() noexcept
	{
		constexpr const Elysium::Core::Template::System::size ParameterPackLength =
			Elysium::Core::Template::Utility::IntegerSequence<T, Values...>::GetLength();
		Elysium::Core::Template::Container::Vector<Elysium::Core::Template::TypeTraits::UnderlyingType<T>::Type> Result =
			Elysium::Core::Template::Container::Vector<Elysium::Core::Template::TypeTraits::UnderlyingType<T>::Type>(ParameterPackLength);

		for (const T Value : { Values... })
		{
			Result.PushBack(static_cast<Elysium::Core::Template::TypeTraits::UnderlyingType<T>::Type>(Value));
		}

		return Result;
	}
}
#endif
