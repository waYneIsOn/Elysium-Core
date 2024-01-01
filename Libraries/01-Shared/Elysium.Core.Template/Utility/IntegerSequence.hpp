/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_UTILITY_INTEGERSEQUENCE
#define ELYSIUM_CORE_TEMPLATE_UTILITY_INTEGERSEQUENCE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_ENUMERATIONORINTEGRAL
#include "../EnumerationOrIntegral.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

namespace Elysium::Core::Template::Utility
{
	template <Concepts::EnumerationOrIntegral T, T... Values>
	class IntegerSequence
	{
	public:
		static constexpr const Elysium::Core::Template::System::size GetLength() noexcept;
	};

	template<Concepts::EnumerationOrIntegral T, T ...Values>
	inline constexpr const Elysium::Core::Template::System::size IntegerSequence<T, Values...>::GetLength() noexcept
	{
		return sizeof...(Values);
	}
}
#endif
