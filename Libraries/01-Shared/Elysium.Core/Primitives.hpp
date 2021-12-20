/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_PRIMITIVES
#define ELYSIUM_CORE_PRIMITIVES

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "System.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_LITERALS
#include "../Elysium.Core.Template/Literals.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

namespace Elysium::Core
{
	using int8_t = Elysium::Core::Template::System::int8_t;
	using int16_t = Elysium::Core::Template::System::int16_t;
	using int32_t = Elysium::Core::Template::System::int32_t;
	using int64_t = Elysium::Core::Template::System::int64_t;

	using uint8_t = Elysium::Core::Template::System::uint8_t;
	using uint16_t = Elysium::Core::Template::System::uint16_t;
	using uint32_t = Elysium::Core::Template::System::uint32_t;
	using uint64_t = Elysium::Core::Template::System::uint64_t;

	using size = Elysium::Core::Template::System::size;
}
#endif
