/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_COLLECTIONS_DEFAULTALLOCATOR
#define ELYSIUM_CORE_TEMPLATE_COLLECTIONS_DEFAULTALLOCATOR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_NONCONSTANT
#include "NonConstant.hpp"
#endif

namespace Elysium::Core::Template::Collections
{
	template<Concepts::NonConstant T>
	class DefaultAllocator final
	{
	public:
		DefaultAllocator() noexcept;
		DefaultAllocator(const DefaultAllocator<T>& Source) = delete;
		DefaultAllocator(DefaultAllocator<T>&& Right) noexcept = delete;
		~DefaultAllocator();

		DefaultAllocator<T>& operator=(const DefaultAllocator<T>& Source) = delete;
		DefaultAllocator<T>& operator=(DefaultAllocator<T>&& Right) noexcept = delete;

		constexpr T* Allocate(const size_t Length);
		void Deallocate(T* First, const size_t Length);
	};

	template<Concepts::NonConstant T>
	inline DefaultAllocator<T>::DefaultAllocator() noexcept
	{ }
	template<Concepts::NonConstant T>
	inline DefaultAllocator<T>::~DefaultAllocator()
	{ }

	template<Concepts::NonConstant T>
	inline constexpr T* DefaultAllocator<T>::Allocate(const size_t Length)
	{
		if (Length == 0)
		{
			return nullptr;
		}

		return new T[Length];
	}

	template<Concepts::NonConstant T>
	inline void DefaultAllocator<T>::Deallocate(T* First, const size_t Length)
	{
		if (First == nullptr)
		{
			return;
		}

		delete[] First;
		First = nullptr;
	}
}
#endif
