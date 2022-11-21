/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_UNICODECHARACTER
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_UNICODECHARACTER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISUNICODECHARACTER
#include "IsUnicodeCharacter.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
	template<class T>
	concept UnicodeCharacter = TypeTraits::IsUnicodeCharacterValue<T>;
}
#endif
