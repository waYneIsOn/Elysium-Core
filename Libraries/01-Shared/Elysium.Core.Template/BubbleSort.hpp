/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_ALGORITHMS_SORTING_BUBBLESORT
#define ELYSIUM_CORE_TEMPLATE_ALGORITHMS_SORTING_BUBBLESORT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_POINTER
#include "Pointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REMOVERPOINTER
#include "RemovePointer.hpp"
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
	constexpr void BubbleSort(const T First, const Elysium::Core::size Count, const Compare Comparer)
	{
		if (First == nullptr || Count < 2)
		{
			return;
		}

		const Elysium::Core::size ReducedCount = Count - 1;
		for (Elysium::Core::size i = 0; i < ReducedCount; i++)
		{
			for (Elysium::Core::size j = 0; j < ReducedCount; j++)
			{
				if (Comparer.operator()(First[j], First[j + 1]))
				{
					Functional::Swap(First[j], First[j + 1]);
				}
			}
		}
	}

	template <Concepts::Pointer T, class Compare>
	constexpr void BubbleSort(const T First, const T Last, const Compare Comparer)
	{
		if (First == nullptr || Last == nullptr)
		{
			return;
		}
		if (First >= Last)
		{
			return;
		}
		/*
		T CurrentOuter = First;
		T CurrentInner = First;
		while (CurrentOuter != Last)
		{
			while (CurrentInner != First)
			{
				if (Comparer.operator()(CurrentOuter, CurrentInner))
				{
					Utility::Swap(CurrentOuter, CurrentInner);
				}
				CurrentInner++;
			}
			CurrentOuter++;
		}
		*/
		// ToDo: need to make use of size of T or implement it directly using pointer
		const Elysium::Core::size Count = Last - First + 1;
		BubbleSort(First, Count, Comparer);
	}

	template <Concepts::Pointer T>
	constexpr void BubbleSort(const T First, const Elysium::Core::size Count)
	{
		BubbleSort<T>(First, Count, Operators::Greater<Functional::RemovePointerType<T>>());
	}

	template <Concepts::Pointer T>
	constexpr void BubbleSort(const T First, const T Last)
	{
		BubbleSort<T>(First, Last, Operators::Greater<Functional::RemovePointerType<T>>());
	}
}
#endif
