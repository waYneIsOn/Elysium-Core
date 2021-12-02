/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_HASMETHOD
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_HASMETHOD

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_SAMEAS
#include "SameAs.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISMEMBERFUNCTIONPOINTER
#include "IsMemberFunctionPointer.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
	template<class T, class ReturnType, class ...Args>
	concept HasMethod = requires(T& Instance)
	{
		{ Instance.GetHashCode() } -> SameAs<ReturnType>;
	};
}
#endif
