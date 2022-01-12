/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_COLLECTIONS_VECTOROFSTRING
#define ELYSIUM_CORE_COLLECTIONS_VECTOROFSTRING

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Elysium.Core.Template/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

namespace Elysium::Core
{
	template class ELYSIUM_CORE_API Elysium::Core::Template::Container::Vector<Elysium::Core::Utf8String>;

	using VectorOfUtf8String = Elysium::Core::Template::Container::Vector<Elysium::Core::Utf8String>;
}
#endif
