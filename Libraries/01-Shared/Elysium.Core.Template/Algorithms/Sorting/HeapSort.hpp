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

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_SWAP
#include "../../Functional/Swap.hpp"
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
	inline constexpr void HeapSortHeapify(const T First, const Elysium::Core::Template::System::size Count, const Elysium::Core::Template::System::size RootIndex, const Compare Comparer)
	{
		const Elysium::Core::Template::System::size LeftIndex = 2 * RootIndex + 1;
		const Elysium::Core::Template::System::size RightIndex = 2 * RootIndex + 2;

		Elysium::Core::Template::System::size LargestIndex = RootIndex;

		if (LeftIndex < Count && Comparer(First[LargestIndex], First[LeftIndex]))
		{
			LargestIndex = LeftIndex;
		}

		if (RightIndex < Count && Comparer(First[LargestIndex], First[RightIndex]))
		{
			LargestIndex = RightIndex;
		}

		if (LargestIndex != RootIndex)
		{
			Elysium::Core::Template::Functional::Swap(First[LargestIndex], First[RootIndex]);
			HeapSortHeapify(First, Count, LargestIndex, Comparer);
		}
	}

	template <Elysium::Core::Template::Concepts::Pointer T, class Compare>
	inline constexpr void HeapSort(const T First, const Elysium::Core::Template::System::size Count, const Compare Comparer)
	{
		if (Count < 2)
		{
			return;
		}

		for (Elysium::Core::Template::System::size i = Count / 2; i-- > 0;)
		{
			HeapSortHeapify(First, Count, i, Comparer);
		}

		for (Elysium::Core::Template::System::size i = Count; i-- > 1;)
		{
			Functional::Swap(First[0], First[i]);

			HeapSortHeapify(First, i, 0, Comparer);
		}
	}

	template <Elysium::Core::Template::Concepts::Pointer T>
	inline constexpr void HeapSort(const T First, const Elysium::Core::Template::System::size Count)
	{
		HeapSort(First, Count, Operators::Greater<Functional::RemovePointerType<T>>());
	}
}
#endif
