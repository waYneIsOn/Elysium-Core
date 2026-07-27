/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_PAIR
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_PAIR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Functional/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REMOVECONSTVOLATILE
#include "../Functional/RemoveConstVolatile.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_CALLTRAITS
#include "../TypeTraits/CallTraits.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	template <class T1, class T2>
	class Pair
	{
	public:
		using FirstType = Elysium::Core::Template::Functional::RemoveConstVolatileType<T1>;
		using SecondType = Elysium::Core::Template::Functional::RemoveConstVolatileType<T2>;

		using FirstParameterType = Elysium::Core::Template::TypeTraits::CallTraits<FirstType>::ParameterType;
		using SecondParameterType = Elysium::Core::Template::TypeTraits::CallTraits<SecondType>::ParameterType;

		using FirstReturnType = FirstParameterType;
		using SecondReturnType = SecondParameterType;
	public:
		constexpr Pair() = delete;

		inline constexpr Pair(FirstParameterType First, SecondParameterType Second)
			: _First(First), _Second(Second)
		{ }

		inline constexpr Pair(const Pair& Source)
			: _First(Source._First), _Second(Source._Second)
		{ }

		inline constexpr Pair(Pair&& Right) noexcept
			: _First(), _Second()
		{
			*this = Elysium::Core::Template::Functional::Move(Right);
		}

		inline constexpr ~Pair() = default;
	public:
		inline constexpr Pair<T1, T2>& operator=(const Pair& Source)
		{
			if (this != &Source)
			{
				_First = Source._First;
				_Second = Source._Second;
			}
			return *this;
		}

		inline constexpr Pair<T1, T2>& operator=(Pair&& Right) noexcept
		{
			if (this != &Right)
			{
				_First = Functional::Move(Right._First);
				_Second = Functional::Move(Right._Second);
			}
			return *this;
		}
	public:
		inline constexpr FirstReturnType GetFirst() const
		{
			return _First;
		}

		inline constexpr SecondReturnType GetSecond() const
		{
			return _Second;
		}
	private:
		T1 _First;
		T2 _Second;
	};
}
#endif
