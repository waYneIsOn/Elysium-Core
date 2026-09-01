/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_TUPLE
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_TUPLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_FORWARD
#include "../Functional/Forward.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Functional/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_UTILITY_INDEXSEQUENCE
#include "../Utility/IndexSequence.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="...Args"></typeparam>
	template <class ...Args>
	class Tuple;

	/// <summary>
	/// Specialization for any empty Tuple.
	/// </summary>
	template <>
	class Tuple<>
	{
	public:
		constexpr Tuple() noexcept = default;

		constexpr Tuple(const Tuple<>& Source) = default;

		constexpr Tuple(Tuple<>&& Right) noexcept = default;

		constexpr ~Tuple() = default;
	public:
		constexpr Tuple<>& operator=(const Tuple<>& Source) = default;

		constexpr Tuple<>& operator=(Tuple<>&& Right) noexcept = default;
	public:
		inline static constexpr const Elysium::Core::Template::System::size NumberOfElements = 0;
	public:
		template <class F, class... FurtherElements>
		inline constexpr decltype(auto) Unpack(F&& Callable, FurtherElements&&... Elements) const
		{
			return Elysium::Core::Template::Functional::Forward<F>(Callable)(Elysium::Core::Template::Functional::Forward<FurtherElements>(Elements)...);
		}
	};

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="First"></typeparam>
	/// <typeparam name="...Rest"></typeparam>
	template <class First, class... Rest>
	class Tuple<First, Rest...>
		: private Tuple<Rest...>
	{
	public:
		constexpr Tuple() = default;

		constexpr Tuple(First&& Element, Rest&&... Args)
			: Tuple<Rest...>(Elysium::Core::Template::Functional::Forward<Rest>(Args)...),
			_Element(Elysium::Core::Template::Functional::Forward<First>(Element))
		{ }

		constexpr Tuple(const Tuple<First, Rest...>& Source) = default;

		constexpr Tuple(Tuple<First, Rest...>&& Right) noexcept = default;

		constexpr ~Tuple() = default;
	public:
		constexpr Tuple<First, Rest...>& operator=(const Tuple<First, Rest...>& Source) = default;

		constexpr Tuple<First, Rest...>& operator=(Tuple<First, Rest...>&& Right) noexcept = default;
	public:
		inline static constexpr const Elysium::Core::Template::System::size NumberOfElements = 1 + sizeof...(Rest);
	public:
		inline constexpr First& GetFirst() noexcept
		{
			return _Element;
		}

		inline constexpr const First& GetFirst() const noexcept
		{
			return _Element;
		}
	public:
		template<Elysium::Core::Template::System::size Index>
		inline auto& GetAt()
		{
			if constexpr (NumberOfElements <= Index)
			{
				static_assert(false, "Elysium::Core::Template::Container::Tuple<...>::GetAt(): Index out of range!");
			}
			else if constexpr (Index == 0)
			{
				return _Element;
			}
			else
			{
				Tuple<Rest...>& RemainingTuple = *this;
				return RemainingTuple.template GetAt<Index - 1>();
			}
		}
		
		template<Elysium::Core::Template::System::size Index>
		inline const auto& GetAt() const
		{
			if constexpr (NumberOfElements <= Index)
			{
				static_assert(false, "Elysium::Core::Template::Container::Tuple<...>::GetAt() const: Index out of range!");
			}
			else if constexpr (Index == 0)
			{
				return _Element;
			}
			else
			{
				const Tuple<Rest...>& RemainingTuple = *this;
				return RemainingTuple.template GetAt<Index - 1>();
			}
		}
	public:
		template <class F, class... FurtherElements>
		inline constexpr decltype(auto) Unpack(F&& Callable, FurtherElements&&... Elements) const
		{
			return Tuple<Rest...>::Unpack(Elysium::Core::Template::Functional::Forward<F>(Callable), Elysium::Core::Template::Functional::Forward<FurtherElements>(Elements)..., _Element);
		}
	public:
		First _Element;
	};
}
#endif
