/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REMOVECONSTVOLATILE
#define ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REMOVECONSTVOLATILE

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::Functional
{
	template <class T>
	struct RemoveConstVolatile
	{
		using Type = T;
	};

	template <class T>
	struct RemoveConstVolatile<const T>
	{
		using Type = T;
	};

	template <class T>
	struct RemoveConstVolatile<volatile T>
	{
		using Type = T;
	};

	template <class T>
	struct RemoveConstVolatile<const volatile T>
	{
		using Type = T;
	};

	template <class T>
	using RemoveConstVolatileType = typename RemoveConstVolatile<T>::Type;
}
#endif
