/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_HASH
#define ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_HASH

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

namespace Elysium::Core::Template::Functional
{
	template<class T>
	class Hash
	{
	public:
		inline constexpr Elysium::Core::Template::System::size operator()(const T Value) const noexcept
		{
			return 0;
		}
	};

	template<>
	class Hash<float>
	{
	public:
		inline constexpr Elysium::Core::Template::System::size operator()(const float Value) const noexcept
		{
			return static_cast<Elysium::Core::Template::System::size>(Value);
		}
	};

	template<>
	class Hash<double>
	{
	public:
		inline constexpr Elysium::Core::Template::System::size operator()(const double Value) const noexcept
		{
			return static_cast<Elysium::Core::Template::System::size>(Value);
		}
	};
}
#endif
