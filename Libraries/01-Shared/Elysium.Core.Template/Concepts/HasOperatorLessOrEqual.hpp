/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_HASOPERATORLESSOREQUAL
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_HASOPERATORLESSOREQUAL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_SAMEAS
#include "SameAs.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
	template<class T>
	concept HasOperatorLessOrEqual = requires(const T & Left, const T & Right)
	{
		{ Left <= Right } -> SameAs<bool>;
	};
}
#endif
