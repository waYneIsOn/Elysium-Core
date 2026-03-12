/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_COMMANDTYPE
#define ELYSIUM_CORE_DATA_COMMANDTYPE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../Elysium.Core.Template/System/OperatingSystem.hpp"
#endif

namespace Elysium::Core::Data
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class CommandType 
		: Elysium::Core::uint32_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class CommandType
#else
#error "undefined os"
#endif
	{
		Text = 1,

		StoredProcedure = 4,

		TableDirect = 512
	};
}
#endif
