/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_COMMON_ENABLEIF
#define ELYSIUM_CORE_TEMPLATE_COMMON_ENABLEIF

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::Common
{
	template <bool Condition, class T = void>
	struct EnableIf
	{ };

	template <class T>
	struct EnableIf<true, T>
	{
		using Type = T;
	};

	template <bool Condition, class T = void>
	using EnableIfType = typename EnableIf<Condition, T>::Type;
}
#endif
