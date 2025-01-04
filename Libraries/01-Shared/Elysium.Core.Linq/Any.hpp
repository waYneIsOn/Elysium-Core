/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_LINQ_ANY
#define ELYSIUM_CORE_LINQ_ANY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_LINQ_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../Elysium.Core/Array.hpp"
#endif

namespace Elysium::Core::Linq
{
	struct ELYSIUM_CORE_LINQ_API AnyContainer
	{
		template<class ContainerType>
		const bool operator()(const ContainerType& Container) const;
	};

	template<class ContainerType>
	inline const  bool AnyContainer::operator()(const ContainerType & Container) const
	{
		for (const auto Element : Container)
		{
			return true;
		}
		return false;
	}
}
#endif
