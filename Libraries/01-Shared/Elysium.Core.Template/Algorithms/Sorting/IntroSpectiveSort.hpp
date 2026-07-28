/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_ALGORITHMS_SORTING_INTROSPECTIVESORT
#define ELYSIUM_CORE_TEMPLATE_ALGORITHMS_SORTING_INTROSPECTIVESORT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ALGORITHMS_SORTING_HEAPSORT
#include "HeapSort.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ALGORITHMS_SORTING_INSERTIONSORT
#include "InsertionSort.hpp"
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
	inline constexpr void IntrospectiveSort(const T First, const Elysium::Core::Template::System::size Count, const Compare Comparer, Elysium::Core::Template::System::size DepthLimit,
		const Elysium::Core::Template::System::size Threshold = 16)
	{
		if (1 > Count)
		{
			return;
		}

		if (Threshold >= Count)
		{
			InsertionSort(First, Count, Comparer);
		}
		else if (0 == DepthLimit)
		{
			HeapSort(First, Count, Comparer);
		}
		else
		{
			const Elysium::Core::Template::System::size PartitioningIndex = QuickSortPartition<T, Compare>(First, 0, Count - 1, Comparer);
			--DepthLimit;

			IntrospectiveSort(First, PartitioningIndex, Comparer, DepthLimit, Threshold);
			IntrospectiveSort(&First[PartitioningIndex + 1], Count - PartitioningIndex - 1, Comparer, DepthLimit, Threshold);
		}
	}

	template <Concepts::Pointer T>
	inline constexpr void IntrospectiveSort(const T First, const Elysium::Core::Template::System::size Count)
	{
		IntrospectiveSort<T>(First, Count, Operators::Greater<Functional::RemovePointerType<T>>());
	}
}
#endif
