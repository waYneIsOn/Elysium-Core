/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_SLIDINGWINDOW
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_SLIDINGWINDOW

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_NONCONSTANT
#include "../Concepts/NonConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_FIXEDSIZEBUFFER
#include "FixedSizeBuffer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTALLOCATOR
#include "../Memory/DefaultAllocator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	template <Elysium::Core::Template::Concepts::NonConstant T, class Allocator = Elysium::Core::Template::Memory::DefaultAllocator<T>>
	class SlidingWindow
	{
	public:
		constexpr SlidingWindow() = delete;

		inline constexpr SlidingWindow(const Elysium::Core::Template::System::size Length)
			: _Buffer(Length), _Position(0)
		{ }

		constexpr SlidingWindow(const SlidingWindow& Source) = delete;

		constexpr SlidingWindow(SlidingWindow&& Right) noexcept = delete;

		inline ~SlidingWindow() = default;
	public:
		constexpr SlidingWindow& operator=(const SlidingWindow& Source) = delete;

		constexpr SlidingWindow& operator=(SlidingWindow&& Right) noexcept = delete;
	private:
		FixedSizeBuffer<T, Allocator> _Buffer;
		Elysium::Core::Template::System::size _Position;
	};
}
#endif
