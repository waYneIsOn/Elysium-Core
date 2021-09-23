/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DEFAULTALLOCATOR
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_DEFAULTALLOCATOR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_NONCONSTANT
#include "NonConstant.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	/// <summary>
	/// 
	/// </summary>
	template<Concepts::NonConstant T>
	class DefaultAllocator final
	{
	private:
		static const size_t ElementSize = sizeof(T);
	public:
		/// <summary>
		/// Creates a new instance.
		/// </summary>
		DefaultAllocator() noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Source"></param>
		DefaultAllocator(const DefaultAllocator<T>& Source) = delete;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Right"></param>
		DefaultAllocator(DefaultAllocator<T>&& Right) noexcept = delete;

		/// <summary>
		/// Destroys this instance.
		/// </summary>
		~DefaultAllocator();

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Source"></param>
		/// <returns></returns>
		DefaultAllocator<T>& operator=(const DefaultAllocator<T>& Source) = delete;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Right"></param>
		/// <returns></returns>
		DefaultAllocator<T>& operator=(DefaultAllocator<T>&& Right) noexcept = delete;

		/// <summary>
		/// Allocates the exact amount of memory required for given number of elements using operator new[].
		/// This will not initialize the block of memory though!
		/// </summary>
		/// <param name="NumberOfElements"></param>
		/// <returns></returns>
		constexpr T* Allocate(const size_t NumberOfElements);

		/// <summary>
		/// Calls destructor for the first number of instantiated elements before cleaning up the previously allocated memory using operator delete[].
		/// </summary>
		/// <param name="First">Pointer to the starting element.</param>
		/// <param name="NumberOfInstantiatedElements">Number of elements the destructors needs to be called for.</param>
		void Deallocate(T* First, const size_t NumberOfInstantiatedElements);
	};

	template<Concepts::NonConstant T>
	inline DefaultAllocator<T>::DefaultAllocator() noexcept
	{ }

	template<Concepts::NonConstant T>
	inline DefaultAllocator<T>::~DefaultAllocator()
	{ }

	template<Concepts::NonConstant T>
	inline constexpr T* DefaultAllocator<T>::Allocate(const size_t NumberOfElements)
	{
		if (NumberOfElements == 0)
		{
			return nullptr;
		}

		return static_cast<T*>(operator new[](ElementSize * NumberOfElements));
	}

	template<Concepts::NonConstant T>
	inline void DefaultAllocator<T>::Deallocate(T* First, const size_t NumberOfInstantiatedElements)
	{
		if (First == nullptr)
		{
			return;
		}

		for (size_t i = 0; i < NumberOfInstantiatedElements; i++)
		{
			First[i].~T();
		}
		operator delete[](First);
		First = nullptr;
	}
}
#endif
