/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_ALGORITHMS_CLEAR
#define ELYSIUM_CORE_TEMPLATE_ALGORITHMS_CLEAR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_COPYASSIGNABLEANDCONSTRUCTIBLE
#include "CopyAssignableAndConstructible.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_POINTER
#include "Pointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_REFERENCE
#include "Reference.hpp"
#endif


namespace Elysium::Core::Template::Algorithms
{
	template <class Source>
	constexpr void Clear(Source& First, Source& Last) noexcept
	{
		Source* FirstAddress = &First;
		Source* LastAddress = &Last;

		while (FirstAddress <= LastAddress)
		{
			*FirstAddress = Source();

			FirstAddress++;
		}
	}

	template <Concepts::Pointer Source>
	constexpr void Clear(Source& First, Source& Last) noexcept
	{
		Clear(*First, *Last);
	}
}
#endif
