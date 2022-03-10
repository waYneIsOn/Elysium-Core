/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_ACTION
#define ELYSIUM_CORE_ACTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DELEGATE
#include "../Elysium.Core.Template/Delegate.hpp"
#endif

namespace Elysium::Core
{
	template<class ...T>
	using Action = Elysium::Core::Template::Container::Delegate<void, T...>;
}
#endif
