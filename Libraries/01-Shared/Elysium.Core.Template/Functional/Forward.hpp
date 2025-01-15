/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_FORWARD
#define ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_FORWARD

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REMOVEREFERENCE
#include "../RemoveReference.hpp"
#endif

namespace Elysium::Core::Template::Functional
{
	template <class T>
	inline constexpr T&& Forward(Elysium::Core::Template::Functional::RemoveReferenceType<T>& Parameter) noexcept
	{
		return static_cast<T&&>(Parameter);
	}

	template <class T>
	inline constexpr T&& Forward(Elysium::Core::Template::Functional::RemoveReferenceType<T>&& Parameter) noexcept
	{
		return Parameter;
	}
}
#endif
