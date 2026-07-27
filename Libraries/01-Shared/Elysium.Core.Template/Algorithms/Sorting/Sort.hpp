/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_ALGORITHMS_SORTING_SORT
#define ELYSIUM_CORE_TEMPLATE_ALGORITHMS_SORTING_SORT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ALGORITHMS_SORTING_INTROSPECTIVESORT
#include "IntrospectiveSort.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_POINTER
#include "../../Concepts/Pointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REMOVERPOINTER
#include "../../Functional/RemovePointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_FLOOR
#include "../../Math/Floor.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_LOGARITHM
#include "../../Math/Logarithm.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_OPERATORS_GREATER
#include "../../Operators/Greater.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Algorithms::Sorting
{
	template <Elysium::Core::Template::Concepts::Pointer T, class Compare>
	inline constexpr void Sort(const T First, const Elysium::Core::Template::System::size Count, const Compare Comparer)
	{
		const Elysium::Core::Template::System::size MaxDepth = 2 * Elysium::Core::Template::Math::Floor(Elysium::Core::Template::Math::Logarithm2(Count));

		IntrospectiveSort<T, Compare>(First, Count, Comparer, MaxDepth);
	}

	template <Concepts::Pointer T>
	inline constexpr void Sort(const T First, const Elysium::Core::Template::System::size Count)
	{
		Sort(First, Count, Operators::Greater<Functional::RemovePointerType<T>>());
	}
}
#endif
