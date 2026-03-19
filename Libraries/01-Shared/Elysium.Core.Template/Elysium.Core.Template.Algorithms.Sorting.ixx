module;

#ifndef ELYSIUM_CORE_TEMPLATE_ALGORITHMS_SORTING_BLOCKSORT
#include "Algorithms/Sorting/BlockSort.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ALGORITHMS_SORTING_BUBBLESORT
#include "Algorithms/Sorting/BubbleSort.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ALGORITHMS_SORTING_QUICKSORT
#include "Algorithms/Sorting/QuickSort.hpp"
#endif

export module Elysium.Core.Template.Algorithms.Sorting;

export
{
	using Elysium::Core::Template::Algorithms::Sorting::BlockSort;
	using Elysium::Core::Template::Algorithms::Sorting::BubbleSort;
	using Elysium::Core::Template::Algorithms::Sorting::QuickSort;
}
