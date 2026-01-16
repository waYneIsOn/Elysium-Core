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

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_MOVEASSIGNABLEANDCONSTRUCTIBLE
#include "MoveAssignableAndConstructible.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_FORWARD
#include "Functional/Forward.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="...TRest"></typeparam>
	template <Concepts::MoveAssignableAndConstructible ...TRest>
	class Tuple;

	/// <summary>
	/// 
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
		Tuple<>& operator=(const Tuple<>& Source) = default;

		Tuple<>& operator=(Tuple<>&& Right) noexcept = default;
	public:
		inline static constexpr const Elysium::Core::Template::System::size NumberOfElements = 0;
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

		constexpr Tuple(First&& Element, Rest&&... Args);

		constexpr Tuple(const Tuple<First, Rest...>& Source) = default;

		constexpr Tuple(Tuple<First, Rest...>&& Right) noexcept = default;

		constexpr ~Tuple() = default;
	public:
		Tuple<First, Rest...>& operator=(const Tuple<First, Rest...>& Source) = default;

		Tuple<First, Rest...>& operator=(Tuple<First, Rest...>&& Right) noexcept = default;
	public:
		inline static constexpr const Elysium::Core::Template::System::size NumberOfElements = 1 + sizeof...(Rest);
	public:
		First& GetFirst() noexcept;

		const First& GetFirst() const noexcept;
	private:
		First _Element;
	};

	template<class First, class ...Rest>
	inline constexpr Tuple<First, Rest...>::Tuple(First&& Element, Rest&& ...Args)
		: Tuple<Rest...>(Elysium::Core::Template::Functional::Forward<Rest>(Args)...),
		_Element(Elysium::Core::Template::Functional::Forward<First>(Element))
	{ }

	template<class First, class ...Rest>
	inline First& Tuple<First, Rest...>::GetFirst() noexcept
	{
		return _Element;
	}

	template<class First, class ...Rest>
	inline const First& Tuple<First, Rest...>::GetFirst() const noexcept
	{
		return _Element;
	}
}
#endif
