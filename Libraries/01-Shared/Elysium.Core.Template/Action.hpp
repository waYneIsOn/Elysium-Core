/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_ACTION
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_ACTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DELEGATE
#include "Delegate.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	template<class ...T>
	using Action = Delegate<void, T...>;
}
#endif
