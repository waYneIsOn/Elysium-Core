/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_CODEANALYSIS_PYTHON_SYNTAXKIND
#define ELYSIUM_CORE_CODEANALYSIS_PYTHON_SYNTAXKIND

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../Elysium.Core.Template/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

namespace Elysium::Core::CodeAnalysis::Python
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class SyntaxKind : Elysium::Core::Template::System::uint16_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class SyntaxKind
#else
#error "undefined os"
#endif
	{
		None = 0,

		
	};
}
#endif
