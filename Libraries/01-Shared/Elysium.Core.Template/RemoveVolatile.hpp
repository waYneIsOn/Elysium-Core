/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_REMOVEVOLATILE
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_REMOVEVOLATILE

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::TypeTraits
{
	template <class T>
	struct RemoveVolatile
	{
		using Type = T;
	};

	template <class T>
	struct RemoveVolatile<volatile T>
	{
		using Type = T;
	};

	template <class T>
	using RemoveVolatileType = typename RemoveVolatile<T>::Type;
}
#endif
