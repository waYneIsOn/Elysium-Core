/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_EVENT
#define ELYSIUM_CORE_EVENT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_DISPATCH_EVENT
#include "../Elysium.Core.Template/Dispatch/Event.hpp"
#endif

namespace Elysium::Core
{
	template <class ReturnType, class ...Args>
	using Event = Elysium::Core::Template::Dispatch::Event<false, true, true, ReturnType, Args...>;
}
#endif
