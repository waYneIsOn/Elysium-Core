module;

#ifndef _INITIALIZER_LIST_
#include <initializer_list>
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_ARCHTECTURE
#include "System/Architecture.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_COMPILER
#include "System/Compiler.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_LITERALS
#include "System/Literals.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "System/Primitives.hpp"
#endif

export module Elysium.Core.Template.System;

export
{
	using Elysium::Core::Template::System::Architecture;
	using Elysium::Core::Template::System::Compiler;

	// @ToDo?
	//using Elysium::Core::Template::System::Literals;

	using Elysium::Core::Template::System::OperatingSystem;

	// @ToDo?
	//using Elysium::Core::Template::System::Primitives;
}