/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_VOIDTYPE
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_VOIDTYPE

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::TypeTraits
{
	template <class... Types>
	using VoidType = void;
}
#endif

