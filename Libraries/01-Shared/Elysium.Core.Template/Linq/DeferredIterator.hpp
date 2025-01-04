/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_LINQ_DEFERREDITERATOR
#define ELYSIUM_CORE_TEMPLATE_LINQ_DEFERREDITERATOR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_NONCONSTANT
#include "../NonConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Vector.hpp"
#endif

namespace Elysium::Core::Template::Linq
{
	template <Concepts::NonConstant T>
	class DeferredIterator
	{
	protected:
		constexpr DeferredIterator() = default;
	public:
		constexpr DeferredIterator(const DeferredIterator& Source) = delete;

		constexpr DeferredIterator(DeferredIterator&& Right) noexcept = delete;

		constexpr ~DeferredIterator() = default;
	public:
		constexpr DeferredIterator<T>& operator=(const DeferredIterator& Source) = delete;

		constexpr DeferredIterator<T>& operator=(DeferredIterator&& Right) noexcept = delete;
	public:
		virtual const bool MoveNext() = 0;
	public:
		//Elysium::Core::Template::Container::Vector<T> ToVector();
	private:

	};
}
#endif