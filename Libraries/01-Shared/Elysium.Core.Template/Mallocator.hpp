/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_MALLOCATOR
#define ELYSIUM_CORE_TEMPLATE_MALLOCATOR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NONCONSTANT
#include "NonConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_OUTOFMEMORYEXCEPTION
#include "../Elysium.Core/OutOfMemoryException.hpp"
#endif

namespace Elysium::Core::Template
{
	template<NonConstant T>
	class Mallocator final
	{
	public:
		Mallocator() noexcept;
		Mallocator(const Mallocator<T>& Source) = delete;
		Mallocator(Mallocator<T>&& Right) noexcept = delete;
		~Mallocator();

		Mallocator<T>& operator=(const Mallocator<T>& Source) = delete;
		Mallocator<T>& operator=(Mallocator<T>&& Right) noexcept = delete;

		constexpr T* Allocate(const size_t Count);
		void Deallocate(const T* First, const size_t Count);
	private:

	};

	template<NonConstant T>
	inline Mallocator<T>::Mallocator() noexcept
	{ }
	template<NonConstant T>
	inline Mallocator<T>::~Mallocator()
	{ }

	template<NonConstant T>
	inline constexpr T* Mallocator<T>::Allocate(const size_t Count)
	{
		if (Count == 0)
		{
			return nullptr;
		}
		if (Count > static_cast<size_t>(-1) / sizeof(T))
		{
			// ToDo:
			//throw OutOfMemoryException();
			throw 1;
		}

		void Result = malloc(Count * sizeof(T));
		if (Result == nullptr)
		{
			// ToDo:
			//throw OutOfMemoryException();
			throw 1;
		}

		return static_cast<T*>(Result);
	}

	template<NonConstant T>
	inline void Mallocator<T>::Deallocate(const T* First, const size_t Count)
	{
		free(First);
	}
}
#endif
