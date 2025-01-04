/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_LINQ_WHEREDEFERREDITERATOR
#define ELYSIUM_CORE_TEMPLATE_LINQ_WHEREDEFERREDITERATOR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_NONCONSTANT
#include "../NonConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_LINQ_DEFERREDITERATOR
#include "DeferredIterator.hpp"
#endif

namespace Elysium::Core::Template::Linq
{
	template <Concepts::NonConstant T>
	class WhereDeferredIterator
		: public DeferredIterator<T>
	{
	protected:
		constexpr WhereDeferredIterator() = default;
	public:
		constexpr WhereDeferredIterator(const WhereDeferredIterator& Source) = delete;

		constexpr WhereDeferredIterator(WhereDeferredIterator&& Right) noexcept = delete;

		constexpr ~WhereDeferredIterator() = default;
	public:
		constexpr WhereDeferredIterator<T>& operator=(const WhereDeferredIterator& Source) = delete;

		constexpr WhereDeferredIterator<T>& operator=(WhereDeferredIterator&& Right) noexcept = delete;
	public:
		virtual const bool MoveNext() override;
	public:
		//Elysium::Core::Template::Container::Vector<T> ToVector();
	private:

	};

	template<Concepts::NonConstant T>
	inline const bool WhereDeferredIterator<T>::MoveNext()
	{
		return false;
	}
}
#endif