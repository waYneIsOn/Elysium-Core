/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

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
		size_t operator()(ContainerType & Container)
		{
			size_t Count = 0;
			for (auto Element : Container)
			{
				Count++;
			}
			return Count;
		}
	};
}
#endif
