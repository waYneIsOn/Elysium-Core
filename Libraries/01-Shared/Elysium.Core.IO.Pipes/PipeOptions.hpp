/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_PIPIES_PIPEOPTIONS
#define ELYSIUM_CORE_IO_PIPIES_PIPEOPTIONS

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
	/// Provides options for creating a PipeStream object.
	/// This enumeration allows a bitwise combination of its member values.
	/// </summary>
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class PipeOptions
		: Elysium::Core::Template::System::uint32_t
#else
#error "undefined os"
#endif
	{
		/// <summary>
		/// Indicates that the system should write through any intermediate cache and go directly to the pipe.
		/// </summary>
		WriteThrough = -2147483648,

		/// <summary>
		/// Indicates that there are no additional parameters.
		/// </summary>
		None = 0,

		/// <summary>
		/// 
		/// </summary>
		FirstPipeInstance = 524288,

		/// <summary>
		/// When used to create a NamedPipeServerStream instance, indicates that the pipe can only be connected to a client created by 
		/// the same user. When used to create a NamedPipeClientStream instance, indicates that the pipe can only connect to a server 
		/// created by the same user. On Windows, it verifies both the user account and elevation level.
		/// </summary>
		CurrentUserOnly = 536870912,

		/// <summary>
		/// Indicates that the pipe can be used for asynchronous reading and writing.
		/// </summary>
		Asynchronous = 1073741824
	};

	inline PipeOptions operator|(const PipeOptions Left, const PipeOptions Right)
	{
		return static_cast<PipeOptions>(static_cast<int>(Left) | static_cast<int>(Right));
	}

	inline PipeOptions operator&(const PipeOptions Left, const PipeOptions Right)
	{
		return static_cast<PipeOptions>(static_cast<int>(Left) & static_cast<int>(Right));
	}
}
#endif
