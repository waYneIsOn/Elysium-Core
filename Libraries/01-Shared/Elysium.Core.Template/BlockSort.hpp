/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_ALGORITHMS_SORTING_BLOCKSORT
#define ELYSIUM_CORE_TEMPLATE_ALGORITHMS_SORTING_BLOCKSORT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REMOVERPOINTER
#include "RemovePointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_POINTER
#include "Pointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_OPERATORS_GREATER
#include "Greater.hpp"
#endif

namespace Elysium::Core::Template::Algorithms::Sorting
{
	template <Concepts::Pointer T, class Compare>
	constexpr void BlockSort(const T First, const size_t Count, const Compare Comparer)
	{
		throw 1;
	}

	template <Concepts::Pointer T, class Compare>
	constexpr void BlockSort(const T First, const T Last, const Compare Comparer)
	{
		throw 1;
	}

	template <Concepts::Pointer T>
	constexpr void BlockSort(const T First, const size_t Count)
	{
		BlockSort<T>(First, Count, Operators::Greater<Functional::RemovePointerType<T>>());
	}

	template <Concepts::Pointer T>
	constexpr void BlockSort(const T First, const T Last)
	{
		BlockSort<T>(First, Last, Operators::Greater<Functional::RemovePointerType<T>>());
	}
}
#endif
