/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_MEMORY_SCOPED_ARENA
#define ELYSIUM_CORE_MEMORY_SCOPED_ARENA

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_SCOPED_ARENA
#include "../Elysium.Core.Template/Memory/Scoped/Arena.hpp"
#endif

namespace Elysium::Core::Memory::Scoped
{
	class ELYSIUM_CORE_API Elysium::Core::Template::Memory::Scoped::Arena;

	using Arena = Elysium::Core::Template::Memory::Scoped::Arena;
}
#endif
