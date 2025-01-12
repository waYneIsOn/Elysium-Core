/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_PIPIES_PIPEDIRECTION
#define ELYSIUM_CORE_IO_PIPIES_PIPEDIRECTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../Elysium.Core.Template/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

namespace Elysium::Core::IO::Pipes
{
	/// <summary>
	/// Specifies the direction of the pipe.
	/// </summary>
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class PipeDirection
		: Elysium::Core::Template::System::uint8_t
#else
#error "undefined os"
#endif
	{
		/// <summary>
		/// Specifies that the pipe direction is in.
		/// </summary>
		In = 1,

		/// <summary>
		/// Specifies that the pipe direction is out.
		/// </summary>
		Out = 2,

		/// <summary>
		/// Specifies that the pipe direction is two-way.
		/// </summary>
		InOut= 3
	};
}
#endif
