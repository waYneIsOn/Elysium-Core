/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_INTERNAL_SCRIPT
#define ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_INTERNAL_SCRIPT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_INTERNAL_SCRIPTDIRECTION
#include "ScriptDirection.hpp"
#endif

namespace Elysium::Core::Template::Globalization::Internal
{
	class Script
	{
		// https://en.wikipedia.org/wiki/List_of_writing_systems
		// - text can be right to left, while numbers are written left to right etc.
	private:
		ScriptDirection _TextDirection;
		ScriptDirection _NumberDirection;
	};
	/*
	using Latin = Script;
	using Runic = Script;
	*/
}
#endif
