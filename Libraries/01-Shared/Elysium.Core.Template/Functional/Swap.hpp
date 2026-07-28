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
#include "../Concepts/MoveAssignableAndConstructible.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_POINTER
#include "../Concepts/Pointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REMOVERPOINTER
#include "RemovePointer.hpp"
#endif

namespace Elysium::Core::Template::Functional
{
	template <Concepts::MoveAssignableAndConstructible T>
	inline constexpr void Swap(T& Left, T& Right) noexcept
	{
		T TemporaryValue = Functional::Move(Left);
		Left = Functional::Move(Right);
		Right = Functional::Move(TemporaryValue);
	}
	
	template <Concepts::Pointer T>
	inline constexpr void Swap(T Left, T Right) noexcept
	{
		RemovePointerType<T> TemporaryValue = Functional::Move(*Left);
		Left = Functional::Move(*Right);
		Right = Functional::Move(TemporaryValue);
	}
}
#endif
