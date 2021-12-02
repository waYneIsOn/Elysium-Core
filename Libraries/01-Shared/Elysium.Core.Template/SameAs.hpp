/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_SAMEAS
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_SAMEAS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISSAME
#include "IsSame.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
	template<class TFirst, class TSecond>
	concept SameAs = TypeTraits::IsSame<TFirst, TSecond>::Value;
}
#endif
