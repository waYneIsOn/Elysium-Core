/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_UNDERLYINGTYPE
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_UNDERLYINGTYPE

#ifdef _MSC_VER
#pragma once
#endif


#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_ENUMERATION
#include "Concepts/Enumeration.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
	template <Concepts::Enumeration T>
	struct UnderlyingType
	{
		using Type = __underlying_type(T);
	};

	template <Concepts::Enumeration T>
	using UnderlyingTypeType = typename UnderlyingType<T>::Type;
}
#endif
