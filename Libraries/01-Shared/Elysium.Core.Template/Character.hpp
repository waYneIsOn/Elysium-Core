/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_CHARACTER
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_CHARACTER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISCHARACTER
#include "IsCharacter.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
	template<class T>
	concept Character = TypeTraits::IsCharacterValue<T>;
}
#endif
