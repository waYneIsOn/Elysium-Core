/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_COMMANDLINE_PARSING_TOKENTYPE
#define ELYSIUM_CORE_COMMANDLINE_PARSING_TOKENTYPE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../Elysium.Core.Template/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

namespace Elysium::Core::CommandLine::Parsing
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class TokenType 
		: Elysium::Core::Template::System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class TokenType
#else
#error "undefined os"
#endif
	{
		Argument,

		Command,

		Option
	};
}
#endif
