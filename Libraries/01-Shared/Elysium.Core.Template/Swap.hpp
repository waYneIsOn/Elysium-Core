/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_SWAP
#define ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_SWAP

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_MOVEASSIGNABLEANDCONSTRUCTIBLE
#include "MoveAssignableAndConstructible.hpp"
#endif

namespace Elysium::Core::Template::Functional
{
	template <Concepts::MoveAssignableAndConstructible T>
	constexpr void Swap(T& Left, T& Right) noexcept
	{
		T TemporaryValue = Functional::Move(Left);
		Left = Functional::Move(Right);
		Right = Functional::Move(TemporaryValue);
	}
}
#endif
