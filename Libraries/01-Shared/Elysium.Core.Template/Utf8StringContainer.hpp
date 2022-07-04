/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_UTF8STRINGCONTAINER
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_UTF8STRINGCONTAINER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISANYOF
#include "IsAnyOf.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_STRINGVIEW
#include "../Elysium.Core/StringView.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
	template<class T>
	concept Utf8StringContainer = TypeTraits::IsAnyOfValue<T, Utf8String> || TypeTraits::IsAnyOfValue<T, Utf8StringView>;
}
#endif
