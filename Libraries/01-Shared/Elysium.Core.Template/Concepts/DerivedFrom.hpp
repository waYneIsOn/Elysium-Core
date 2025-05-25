/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_DERIVEDFROM
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_DERIVEDFROM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISDERIVEDFROM
#include "../TypeTraits/IsDerivedFrom.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
	template <class Base, class PotentiallyDerived>
	concept DerivedFrom = TypeTraits::IsDerivedFromValue<Base, PotentiallyDerived>;
}
#endif
