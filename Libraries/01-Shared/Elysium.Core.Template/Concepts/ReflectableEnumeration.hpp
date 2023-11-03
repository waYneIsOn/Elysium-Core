/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_REFLECTABLEENUMERATION
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_REFLECTABLEENUMERATION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISENUMERATION
#include "IsEnumeration.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_UNDERLYINGTYPE
#include "../UnderlyingType.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
	/// <summary>
	/// A template class is a reflectable enum if:
	///		- it's an actual enum
	///		- the size of the underlying type is 16 bit or less (since there currently is no compiler magic available, I have to create this limit!)
	///			@ToDo:
	///				check this when using newer c++ compilers. c++23 onwards hopefully might have what I'm looking for!
	///				if so, I can completely ditch this concept and simply Elysium::Core::Template::Concepts::Enumeration!
	/// </summary>
	template<class T>
	concept ReflectableEnumeration = TypeTraits::IsEnumerationValue<T> && sizeof(TypeTraits::UnderlyingTypeType<T>) <= 2;
}
#endif
