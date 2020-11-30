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

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "../Elysium.Core/List.hpp"
#endif

namespace Elysium::Core::Linq
{
	struct ELYSIUM_CORE_LINQ_API AnyContainer
	{
		template<class ContainerType>
		bool operator()(ContainerType& Container);
	};

	template<class ContainerType>
	inline bool AnyContainer::operator()(ContainerType & Container)
	{
		for (auto Element : Container)
		{
			return true;
		}
		return false;
	}

	template<>
	inline bool AnyContainer::operator()<Elysium::Core::Collections::Template::Array<int>>(Elysium::Core::Collections::Template::Array<int>& Container)
	{
		return Container.GetLength() > 0;
	}

	template<>
	inline bool AnyContainer::operator()<const Elysium::Core::Collections::Template::Array<int>>(const Elysium::Core::Collections::Template::Array<int>& Container)
	{
		return Container.GetLength() > 0;
	}
}
#endif
