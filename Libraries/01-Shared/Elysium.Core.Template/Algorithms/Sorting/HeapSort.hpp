/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_ALGORITHMS_SORTING_HEAPSORT
#define ELYSIUM_CORE_TEMPLATE_ALGORITHMS_SORTING_HEAPSORT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ALGORITHMS_SORTING_QUICKSORT
#include "QuickSort.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_POINTER
#include "../../Concepts/Pointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REMOVERPOINTER
#include "../../Functional/RemovePointer.hpp"
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
	inline constexpr void HeapSort(const T First, const Elysium::Core::Template::System::size Count, const Compare Comparer)
	{
		throw 1;
	}

	template <Elysium::Core::Template::Concepts::Pointer T>
	inline constexpr void HeapSort(const T First, const Elysium::Core::Template::System::size Count)
	{
		HeapSort(First, Count, Operators::Greater<Functional::RemovePointerType<T>>());
	}
}
#endif
