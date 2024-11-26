/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_ATOMIC
#define ELYSIUM_CORE_THREADING_ATOMIC

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMIC
#include "../Elysium.Core.Template/Atomic.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

namespace Elysium::Core::Threading
{
	template class ELYSIUM_CORE_API Elysium::Core::Template::Threading::Atomic<bool>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::byte>;

	using AtomicBool = Elysium::Core::Template::Threading::Atomic<bool>;
	using AtomicByte = Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::byte>;
}
#endif