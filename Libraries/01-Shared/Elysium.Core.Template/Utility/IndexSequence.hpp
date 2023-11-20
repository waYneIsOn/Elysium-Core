/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_UTILITY_INDEXSEQUENCE
#define ELYSIUM_CORE_TEMPLATE_UTILITY_INDEXSEQUENCE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_UTILITY_INTEGERSEQUENCE
#include "IntegerSequence.hpp"
#endif

namespace Elysium::Core::Template::Utility
{
	template<Elysium::Core::Template::System::size... Indices>
	using IndexSequence = Elysium::Core::Template::Utility::IntegerSequence<Elysium::Core::Template::System::size, Indices...>;

	template<Elysium::Core::Template::System::size Length>
	using MakeIndexSequence = MakeIntegerSequence<Elysium::Core::Template::System::size, Length>;
}
#endif
