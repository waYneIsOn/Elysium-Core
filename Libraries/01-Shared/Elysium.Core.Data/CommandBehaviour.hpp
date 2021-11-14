/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_COMMANDBEHAVIOUR
#define ELYSIUM_CORE_DATA_COMMANDBEHAVIOUR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

namespace Elysium::Core::Data
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class CommandBehaviour : Elysium::Core::uint32_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class CommandBehaviour
#else
#error "undefined os"
#endif
	{
		Default = 0,

		SingleResult = 1,

		SchemaOnly = 2,

		KeyInfo = 4,

		SingleRow = 8,

		SequentialAccess = 16,

		CloseConnection = 32
	};
}
#endif
