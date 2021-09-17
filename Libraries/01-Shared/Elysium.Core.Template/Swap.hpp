/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_UTILITY_SWAP
#define ELYSIUM_CORE_TEMPLATE_UTILITY_SWAP

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::Utility
{
	// ToDo: perform checks to make sure T can be move-constructed and -assigned without any problems!
	// (use concepts?)

	template <class T>
	constexpr void Swap(T& Left, T& Right) noexcept
	{
		T TemporaryValue = TypeTraits::Move(Left);
		Left = TypeTraits::Move(Right);
		Right = TypeTraits::Move(TemporaryValue);
	}
}
#endif
