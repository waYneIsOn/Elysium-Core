/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_DISPATCH_SIGNAL
#define ELYSIUM_CORE_TEMPLATE_DISPATCH_SIGNAL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_DISPATCH_EVENT
#include "Event.hpp"
#endif

namespace Elysium::Core::Template::Dispatch
{
	template <class ReturnType, class ...Args>
	using Signal = Elysium::Core::Template::Dispatch::Event<false, false, ReturnType, Args...>;
}
#endif
