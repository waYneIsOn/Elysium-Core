/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_MALLOCATOR
#define ELYSIUM_CORE_COLLECTIONS_TEMPLATE_MALLOCATOR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_OUTOFMEMORYEXCEPTION
#include "OutOfMemoryException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NONCONSTANT
#include "../Elysium.Core.Template/NonConstant.hpp"
#endif

namespace Elysium::Core::Collections::Template
{
	template<Elysium::Core::Template::NonConstant T>
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
	};

	template<Elysium::Core::Template::NonConstant T>
	inline Mallocator<T>::Mallocator() noexcept
	{ }
	template<Elysium::Core::Template::NonConstant T>
	inline Mallocator<T>::~Mallocator()
	{ }

	template<Elysium::Core::Template::NonConstant T>
	inline constexpr T* Mallocator<T>::Allocate(const size_t Count)
	{
		if (Count == 0)
		{
			return nullptr;
		}
		if (Count > static_cast<size_t>(-1) / sizeof(T))
		{
			throw OutOfMemoryException();
		}

		void Result = malloc(Count * sizeof(T));
		if (Result == nullptr)
		{
			throw OutOfMemoryException();
		}

		return static_cast<T*>(Result);
	}

	template<Elysium::Core::Template::NonConstant T>
	inline void Mallocator<T>::Deallocate(const T* First, const size_t Count)
	{
		free(First);
	}
}
#endif
