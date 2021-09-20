/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_ALGORITHMS_SORTING_QUICKSORT
#define ELYSIUM_CORE_TEMPLATE_ALGORITHMS_SORTING_QUICKSORT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_POINTER
#include "Pointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_SWAP
#include "Swap.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_OPERATORS_GREATER
#include "Greater.hpp"
#endif

namespace Elysium::Core::Template::Algorithms::Sorting
{
	template <Concepts::Pointer T, class Compare>
	constexpr const size_t QuickSortPartition(const T First, const size_t Low, const size_t High, const Compare Comparer)
	{
		const T Pivot = &First[High];
		size_t PivotIndex = Low - 1;

		for (size_t i = Low; i < High; i++)
		{
			if (!Comparer.operator()(First[i], *Pivot))
			//if (Comparer.operator()(*Pivot, First[i]))
			{
				PivotIndex++;
				Functional::Swap(First[PivotIndex], First[i]);
			}
		}

		Functional::Swap(First[PivotIndex + 1], First[High]);
		return PivotIndex + 1;
	}

	template <Concepts::Pointer T, class Compare>
	constexpr void QuickSort(const T First, const size_t Low, const size_t High, const Compare Comparer)
	{
		if (First == nullptr)
		{
			return;
		}

		if (Low < High)
		{
			const size_t PartitioningIndex = QuickSortPartition<T, Compare>(First, Low, High, Comparer);

			QuickSort<T, Compare>(First, Low, PartitioningIndex - 1, Comparer);
			QuickSort<T, Compare>(First, PartitioningIndex + 1, High, Comparer);
		}
	}

	template <Concepts::Pointer T, class Compare>
	constexpr void QuickSort(const T First, const size_t Count, const Compare Comparer)
	{
		if (First == nullptr || Count < 2)
		{
			return;
		}

		QuickSort<T, Compare>(First, 0, Count - 1, Comparer);
	}

	template <Concepts::Pointer T, class Compare>
	constexpr void QuickSort(const T First, const T Last, const Compare Comparer)
	{
		if (First == nullptr || Last == nullptr)
		{
			return;
		}
		if (First >= Last)
		{
			return;
		}

		// ToDo: need to make use of size of T or implement it directly using pointer
		const size_t Count = Last - First + 1;
		BubbleSort(First, Count, Comparer);
	}

	template <Concepts::Pointer T>
	constexpr void QuickSort(const T First, const size_t Count)
	{
		QuickSort<T>(First, Count, Operators::Greater<TypeTraits::RemovePointerType<T>>());
	}

	template <Concepts::Pointer T>
	constexpr void QuickSort(const T First, const T Last)
	{
		QuickSort<T>(First, Last, Operators::Greater<TypeTraits::RemovePointerType<T>>());
	}
}
#endif
