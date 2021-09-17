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

#ifndef ELYSIUM_CORE_TEMPLATE_POINTER
#include "Pointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SWAP
#include "Swap.hpp"
#endif

namespace Elysium::Core::Template::Algorithms::Sorting
{
	template <Concepts::Pointer T>
	constexpr void BubbleSort(const T First, const size_t Count)
	{
		if (First == nullptr || Count < 2)
		{
			return;
		}

		const size_t ReducedCount = Count - 1;
		for (size_t i = 0; i < ReducedCount; i++)
		{
			for (size_t j = 0; j < ReducedCount; j++)
			{
				if (First[j] > First[j + 1])
				{
					Utility::Swap(First[j], First[j + 1]);
				}
			}
		}
	}

	template <Concepts::Pointer T>
	constexpr void BubbleSort(const T First, const T Last)
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
		BubbleSort(First, Count);
	}
}
#endif
