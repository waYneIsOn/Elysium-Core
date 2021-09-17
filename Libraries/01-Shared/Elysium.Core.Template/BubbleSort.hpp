/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_BUBBLESORT
#define ELYSIUM_CORE_TEMPLATE_BUBBLESORT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_POINTER
#include "Pointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SWAP
#include "Swap.hpp"
#endif

namespace Elysium::Core::Template
{
	template <Pointer T>
	constexpr void BubbleSort(const T First, const size_t Count)
	{
		const size_t ReducedCount = Count - 1;
		for (size_t i = 0; i < ReducedCount; i++)
		{
			for (size_t j = 0; j < ReducedCount; j++)
			{
				if (First[j] > First[j + 1])
				{
					Swap(First[j], First[j + 1]);
				}
			}
		}
	}

	template <Pointer T>
	constexpr void BubbleSort(const T First, const T Last)
	{
		// ToDo: need to make use of size of T or implement it directly using pointer
		const size_t Count = Last - First + 1;
		BubbleSort(First, Count);
	}
}
#endif
