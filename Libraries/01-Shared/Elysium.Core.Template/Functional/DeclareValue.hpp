/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_DECLAREVALUE
#define ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_DECLAREVALUE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_ADDRIGHTVALUEREFERENCE
#include "../AddRightValueReference.hpp"
#endif

namespace Elysium::Core::Template::Functional
{
	template <class T>
	Elysium::Core::Template::Functional::AddRightValueReferenceType<T> DeclareValue() noexcept
	{
		static_assert(false, "Elysium::Core::Template::Functional<T>::DeclareValue()");
	}
}
#endif
