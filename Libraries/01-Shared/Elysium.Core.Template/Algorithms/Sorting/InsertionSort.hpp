/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_ALGORITHMS_SORTING_INSERTIONSORT
#define ELYSIUM_CORE_TEMPLATE_ALGORITHMS_SORTING_INSERTIONSORT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ALGORITHMS_SORTING_QUICKSORT
#include "QuickSort.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_POINTER
#include "../../Concepts/Pointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../../Functional/Move.hhp"
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
	inline constexpr void InsertionSort(const T First, const Elysium::Core::Template::System::size Count, const Compare Comparer)
	{
		for (Elysium::Core::Template::System::size i = 1; i < Count; ++i)
		{
			Functional::RemovePointerType<T> Temporary = Elysium::Core::Template::Functional::Move(First[i]);

			Elysium::Core::Template::System::size j = i;
			while (j > 0 && Comparer(Temporary, First[j - 1]))
			{
				First[j] = Elysium::Core::Template::Functional::Move(First[j - 1]);
				--j;
			}

			First[j] = Elysium::Core::Template::Functional::Move(Temporary);
		}
	}

	template <Elysium::Core::Template::Concepts::Pointer T>
	inline constexpr void InsertionSort(const T First, const Elysium::Core::Template::System::size Count)
	{
		InsertionSort(First, Count, Operators::Greater<Functional::RemovePointerType<T>>());
	}
}
#endif
