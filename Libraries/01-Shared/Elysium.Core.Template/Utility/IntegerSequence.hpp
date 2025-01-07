/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_UTILITY_INTEGERSEQUENCE
#define ELYSIUM_CORE_TEMPLATE_UTILITY_INTEGERSEQUENCE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_ENUMERATIONORINTEGRAL
#include "../EnumerationOrIntegral.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

namespace Elysium::Core::Template::Utility
{
	template <Concepts::EnumerationOrIntegral T, T... Values>
	class IntegerSequence
	{
	private:
	public:
		static constexpr const Elysium::Core::Template::System::size Length = sizeof...(Values);
	public:
		template <Elysium::Core::Template::System::size Index>
		static constexpr T GetAt() noexcept;
	private:
		template <T First, T... Rest>
		static constexpr T GetFirst() noexcept;

		template <Elysium::Core::Template::System::size Index, T First, T... Rest>
		static constexpr T GetAtRecursive() noexcept;
	public:
		static constexpr const T First = GetFirst<Values...>();

		static constexpr const T Last = (Values, ...);
	};

	template<Concepts::EnumerationOrIntegral T, T ...Values>
	template<Elysium::Core::Template::System::size Index>
	inline constexpr T IntegerSequence<T, Values...>::GetAt() noexcept
	{
		if constexpr (Index < sizeof...(Values))
		{
			return GetAtRecursive<Index, Values...>();
			/*
			if constexpr (Index == 0)
			{
				return (Values && ...);	// return first value using fold expression "trick"
				//return (Values, ...);	// return last value in sequence
			}
			else
			{
				return IntegerSequence<T, Values...>::template GetAt<Index - 1>();
			}
			*/
		}
		else
		{
			static_assert(false, "Elysium::Core::Template::Utility::IntegerSequence<...>::GetAt(): Index out of range!");
		}
	}

	template<Concepts::EnumerationOrIntegral T, T ...Values>
	template<T First, T ...Rest>
	inline constexpr T IntegerSequence<T, Values...>::GetFirst() noexcept
	{
		return First;
	}

	template<Concepts::EnumerationOrIntegral T, T ...Values>
	template <Elysium::Core::Template::System::size Index, T First, T... Rest>
	inline constexpr T IntegerSequence<T, Values...>::GetAtRecursive() noexcept
	{
		if constexpr (Index == 0)
		{
			return First;
		}
		else 
		{
			return GetAtRecursive<Index - 1, Rest...>();
		}
	}
}
#endif
