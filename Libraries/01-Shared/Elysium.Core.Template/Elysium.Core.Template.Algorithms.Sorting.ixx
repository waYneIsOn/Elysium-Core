module;

#ifndef ELYSIUM_CORE_TEMPLATE_ALGORITHMS_SORTING_BLOCKSORT
#include "Algorithms/Sorting/BlockSort.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ALGORITHMS_SORTING_BUBBLESORT
#include "Algorithms/Sorting/BubbleSort.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ALGORITHMS_SORTING_HEAPSORT
#include "Algorithms/Sorting/HeapSort.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ALGORITHMS_SORTING_INSERTIONSORT
#include "Algorithms/Sorting/InsertionSort.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ALGORITHMS_SORTING_INTROSPECTIVESORT
#include "Algorithms/Sorting/IntrospectiveSort.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ALGORITHMS_SORTING_QUICKSORT
#include "Algorithms/Sorting/QuickSort.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ALGORITHMS_SORTING_SORT
#include "Algorithms/Sorting/Sort.hpp"
#endif

export module Elysium.Core.Template.Algorithms.Sorting;

export
{
	using Elysium::Core::Template::Algorithms::Sorting::BlockSort;
	using Elysium::Core::Template::Algorithms::Sorting::BubbleSort;
	using Elysium::Core::Template::Algorithms::Sorting::HeapSort;
	using Elysium::Core::Template::Algorithms::Sorting::InsertionSort;
	using Elysium::Core::Template::Algorithms::Sorting::IntrospectiveSort;
	using Elysium::Core::Template::Algorithms::Sorting::QuickSort;
	using Elysium::Core::Template::Algorithms::Sorting::Sort;
}
