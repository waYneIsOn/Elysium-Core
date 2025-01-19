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

#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_INTERNAL_TEXTDIRECTION
#include "TextDirection.hpp"
#endif

namespace Elysium::Core::Template::Globalization::Internal
{
	class Script
	{
		// https://en.wikipedia.org/wiki/List_of_writing_systems
		// - text: left to right, right to left
	private:
		TextDirection _TextDirection;
		TextDirection _NumberDirection;
	};

	using Latin = Script;
	using Runic = Script;
}
#endif
