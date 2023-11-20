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

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Vector.hpp"
#endif

namespace Elysium::Core::Template::Utility
{
	template <class T, T... Values>
	class IntegerSequence
	{
	public:
		static constexpr const Elysium::Core::Template::System::size GetLength() noexcept;
	};

	template<class T, T ...Values>
	inline constexpr const Elysium::Core::Template::System::size IntegerSequence<T, Values...>::GetLength() noexcept
	{
		return sizeof...(Values);
	}

	template<class T, T Length>
	using MakeIntegerSequence = __make_integer_seq<IntegerSequence, T, Length>;
}
#endif
