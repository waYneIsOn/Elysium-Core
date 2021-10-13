/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_LINQ_COUNT
#define ELYSIUM_CORE_LINQ_COUNT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_LINQ_API
#include "API.hpp"
#endif

namespace Elysium::Core::Linq
{
	struct ELYSIUM_CORE_LINQ_API CountContainer
	{
		template<class ContainerType>
		const Elysium::Core::size operator()(const ContainerType& Container) const;
	};

	template<class ContainerType>
	inline const Elysium::Core::size CountContainer::operator()(const ContainerType & Container) const
	{
		Elysium::Core::size Count = 0;
		for (const auto Element : Container)
		{
			Count++;
		}
		return Count;
	}
}
#endif
