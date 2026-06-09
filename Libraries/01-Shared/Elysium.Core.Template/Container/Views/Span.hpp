/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_SPAN
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_SPAN

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	template <class T, Elysium::Core::Template::System::size Extent>
	class Span final
	{
	public:
		using Pointer = T*;
	public:
		constexpr Span() = default;

		constexpr Span(const Span& Source) = delete;

		constexpr Span(Span&& Right) noexcept = delete;

		constexpr ~Span() = default;
	public:
		constexpr Span<T>& operator=(const Span& Source) = delete;

		constexpr Span<T>& operator=(Span&& Right) noexcept = delete;
	private:
		T* _First;
		Elysium::Core::Template::System::size _Length;
	};
}
#endif
