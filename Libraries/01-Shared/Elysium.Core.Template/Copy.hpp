/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_ALGORITHMS_COPY
#define ELYSIUM_CORE_TEMPLATE_ALGORITHMS_COPY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_COPYASSIGNABLEANDCONSTRUCTIBLE
#include "CopyAssignableAndConstructible.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_POINTER
#include "Pointer.hpp"
#endif

namespace Elysium::Core::Template::Algorithms
{
	/*
	template <Concepts::CopyAssignableAndConstructible Source, Concepts::CopyAssignableAndConstructible Target>
	constexpr Target Copy(Source First, Source Last, Target Destination) noexcept
	{
		while (First <= Last)
		{
			*Destination = *First;

			First++;
			Destination++;
		}

		return Destination;
	}
	*/
	template <Concepts::Pointer Source, Concepts::Pointer Target>
	constexpr Target Copy(Source First, Source Last, Target Destination) noexcept
	{
		while (First <= Last)
		{
			*Destination = *First;

			First++;
			Destination++;
		}

		return Destination;
	}
}
#endif
