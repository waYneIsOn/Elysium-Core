/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_HASOPERATORGREATEROREQUAL
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_HASOPERATORGREATEROREQUAL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_SAMEAS
#include "SameAs.hpp"
#endif
/*
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_HASOPERATORGREATEROREQUAL
#include "../TypeTraits/HasOperatorGreaterOrEqual.hpp"
#endif
*/
namespace Elysium::Core::Template::Concepts
{
	template<class T>
	concept HasOperatorGreaterOrEqual = requires(const T& Left, const T& Right)
	{
		{ Left >= Right } -> SameAs<bool>;
	};
}
#endif
