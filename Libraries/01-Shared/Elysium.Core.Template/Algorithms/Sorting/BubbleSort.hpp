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

#ifndef ELYSIUM_CORE_TEMPLATE_OPERATORS_LESS
#include "../../Operators/Less.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Algorithms::Sorting
{
	template <Concepts::Pointer T, class Compare>
	inline constexpr void BubbleSort(const T First, const Elysium::Core::Template::System::size Count, const Compare Comparer)
	{
		if (nullptr == First || 2 > Count)
		{
			return;
		}

		const Elysium::Core::Template::System::size ReducedCount = Count - 1;
		for (Elysium::Core::Template::System::size i = 0; i < ReducedCount; ++i)
		{
			for (Elysium::Core::Template::System::size j = 0; j < ReducedCount; ++j)
			{
				if (Comparer.operator()(First[j], First[j + 1]))
				{
					Functional::Swap(First[j], First[j + 1]);
				}
			}
		}
	}

	template <Concepts::Pointer T, class Compare>
	inline constexpr void BubbleSort(const T First, const T Last, const Compare Comparer)
	{
		if (nullptr == First || nullptr == Last)
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
		// @ToDo: need to make use of size of T or implement it directly using pointer
		const Elysium::Core::Template::System::size Count = Last - First + 1;
		BubbleSort(First, Count, Comparer);
	}

	template <Concepts::Pointer T>
	inline constexpr void BubbleSort(const T First, const Elysium::Core::Template::System::size Count)
	{
		BubbleSort<T>(First, Count, Operators::Less<Functional::RemovePointerType<T>>());
	}

	template <Concepts::Pointer T>
	inline constexpr void BubbleSort(const T First, const T Last)
	{
		BubbleSort<T>(First, Last, Operators::Less<Functional::RemovePointerType<T>>());
	}

	// @ToDo: concept
	template <class Iterator>
	inline constexpr void BubbleSort(Iterator First, Iterator Last)
	{
		const Elysium::Core::Template::System::size Count = Last - First;
		const Iterator::CollectionReference DereferencedIterator = *First;
		const Iterator::CollectionPointer ElementAddress = &DereferencedIterator;

		BubbleSort(ElementAddress, Count);
	}
}
#endif
