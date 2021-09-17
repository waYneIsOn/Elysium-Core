/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_VOIDTYPE
#define ELYSIUM_CORE_TEMPLATE_VOIDTYPE

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template
{
	template <class... Types>
	using VoidType = void;
}
#endif

