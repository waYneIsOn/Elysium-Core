/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ALLOCATOR
#define ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ALLOCATOR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NONCONSTANT
#include "../Elysium.Core.Template/NonConstant.hpp"
#endif

namespace Elysium::Core::Collections::Template
{
	template<Elysium::Core::Template::NonConstant T>
	class Allocator final
	{
	public:
		Allocator() noexcept;
		Allocator(const Allocator<T>& Source) = delete;
		Allocator(Allocator<T>&& Right) noexcept = delete;
		~Allocator();

		Allocator<T>& operator=(const Allocator<T>& Source) = delete;
		Allocator<T>& operator=(Allocator<T>&& Right) noexcept = delete;

		constexpr T* Allocate(const size_t Count);
		void Deallocate(const T* First, const size_t Count);
	private:

	};

	template<Elysium::Core::Template::NonConstant T>
	inline Allocator<T>::Allocator() noexcept
	{ }
	template<Elysium::Core::Template::NonConstant T>
	inline Allocator<T>::~Allocator()
	{ }

	template<Elysium::Core::Template::NonConstant T>
	inline constexpr T* Allocator<T>::Allocate(const size_t Count)
	{
		if (Count == 0)
		{
			return nullptr;
		}

		throw 1;
	}

	template<Elysium::Core::Template::NonConstant T>
	inline void Allocator<T>::Deallocate(const T* First, const size_t Count)
	{
		throw 1;
	}
}
#endif
