/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_PIPIES_PIPETRANSMISSIONMODE
#define ELYSIUM_CORE_IO_PIPIES_PIPETRANSMISSIONMODE

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
	/// Specifies the transmission mode of the pipe.
	/// </summary>
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class PipeTransmissionMode
		: Elysium::Core::Template::System::uint8_t
#else
#error "undefined os"
#endif
	{
		/// <summary>
		/// Indicates that data in the pipe is transmitted and read as a stream of bytes.
		/// </summary>
		Byte = 0,

		/// <summary>
		/// Indicates that data in the pipe is transmitted and read as a stream of messages.
		/// </summary>
		Message = 1
	};
}
#endif
