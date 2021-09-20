/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_COLLECTIONS_MALLOCATOR
#define ELYSIUM_CORE_TEMPLATE_COLLECTIONS_MALLOCATOR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_NONCONSTANT
#include "NonConstant.hpp"
#endif

namespace Elysium::Core::Template::Collections
{
	template<Concepts::NonConstant T>
	class MAllocator final
	{
	private:
		static const size_t ElementSize = sizeof(T);
	public:
		MAllocator() noexcept;
		MAllocator(const MAllocator<T>& Source) = delete;
		MAllocator(MAllocator<T>&& Right) noexcept = delete;
		~MAllocator();

		MAllocator<T>& operator=(const MAllocator<T>& Source) = delete;
		MAllocator<T>& operator=(MAllocator<T>&& Right) noexcept = delete;

		constexpr T* Allocate(const size_t Length);
		void Deallocate(T* First, const size_t Length);
	};

	template<Concepts::NonConstant T>
	inline MAllocator<T>::MAllocator() noexcept
	{ }
	template<Concepts::NonConstant T>
	inline MAllocator<T>::~MAllocator()
	{ }

	template<Concepts::NonConstant T>
	inline constexpr T* MAllocator<T>::Allocate(const size_t Length)
	{
		if (Length == 0)
		{
			return nullptr;
		}

		return (T*)malloc(Length * ElementSize);
	}

	template<Concepts::NonConstant T>
	inline void MAllocator<T>::Deallocate(T* First, const size_t Length)
	{
		if (First == nullptr)
		{
			return;
		}

		free(First);
		First = nullptr;
	}
}
#endif
