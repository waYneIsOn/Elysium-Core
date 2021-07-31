/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_REMOVECONST
#define ELYSIUM_CORE_TEMPLATE_REMOVECONST

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template
{
	template <class T>
	struct RemoveConst
	{
		using Type = T;
	};

	template <class T>
	struct RemoveConst<const T>
	{
		using Type = T;
	};

	template <class T>
	using RemoveConstType = typename RemoveConst<T>::Type;
}
#endif
