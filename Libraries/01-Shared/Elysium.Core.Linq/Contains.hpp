/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_LINQ_CONTAINS
#define ELYSIUM_CORE_LINQ_CONTAINS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_LINQ_API
#include "API.hpp"
#endif

namespace Elysium::Core::Linq
{
	struct ELYSIUM_CORE_LINQ_API ContainsContainer
	{
		template<class ContainerType, class ItemType>
		const bool operator()(const ContainerType& Container, const ItemType& Item) const;
	};

	template<class ContainerType, class ItemType>
	inline const bool ContainsContainer::operator()(const ContainerType & Container, const ItemType & Item) const
	{
		for (const auto Element : Container)
		{
			if (Element == Item)
			{
				return true;
			}
		}
		return false;
	}
}
#endif
