/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_UTILITY_MAKEINTEGERSEQUENCE
#define ELYSIUM_CORE_TEMPLATE_UTILITY_MAKEINTEGERSEQUENCE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_ENUMERATIONORINTEGRAL
#include "../EnumerationOrIntegral.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_UTILITY_INTEGERSEQUENCE
#include "IntegerSequence.hpp"
#endif

namespace Elysium::Core::Template::Utility
{
	template<Concepts::EnumerationOrIntegral T, T Length>
	using MakeIntegerSequence = __make_integer_seq<IntegerSequence, T, Length>;
}
#endif
