/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REVERSE
#define ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REVERSE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_MOVEASSIGNABLEANDCONSTRUCTIBLE
#include "MoveAssignableAndConstructible.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_POINTER
#include "Pointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_SWAP
#include "Swap.hpp"
#endif

namespace Elysium::Core::Template::Functional
{
	template <Concepts::MoveAssignableAndConstructible T>
	constexpr void Reverse(T& First, T& Last) noexcept
	{
		while (First != Last && First != --Last)
		{
			Swap(First++, Last);
		}
	}

	template <Concepts::Pointer T>
	constexpr void Reverse(T First, T Last) noexcept
	{
		while (First != Last && First != --Last)
		{
			Swap(*First++, *Last);
		}
	}
}
#endif
