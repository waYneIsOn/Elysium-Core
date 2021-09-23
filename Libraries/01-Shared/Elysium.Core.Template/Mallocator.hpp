/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_MALLOCATOR
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_MALLOCATOR

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
	class MAllocator final
	{
	private:
		static const size_t ElementSize = sizeof(T);
	public:
		/// <summary>
		/// Creates a new instance.
		/// </summary>
		MAllocator() noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Source"></param>
		MAllocator(const MAllocator<T>& Source) = delete;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Right"></param>
		MAllocator(MAllocator<T>&& Right) noexcept = delete;

		/// <summary>
		/// Destroys this instance.
		/// </summary>
		~MAllocator();

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Source"></param>
		/// <returns></returns>
		MAllocator<T>& operator=(const MAllocator<T>& Source) = delete;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Right"></param>
		/// <returns></returns>
		MAllocator<T>& operator=(MAllocator<T>&& Right) noexcept = delete;

		/// <summary>
		/// Allocates the exact amount of memory required for given number of elements using malloc(...).
		/// This will not initialize the block of memory though!
		/// </summary>
		/// <param name="NumberOfElements"></param>
		/// <returns></returns>
		constexpr T* Allocate(const size_t NumberOfElements);

		/// <summary>
		/// Calls destructor for the first number of instantiated elements before cleaning up the previously allocated memory using free(...).
		/// </summary>
		/// <param name="First">Pointer to the starting element.</param>
		/// <param name="NumberOfInstantiatedElements">Number of elements the destructors needs to be called for.</param>
		void Deallocate(T* First, const size_t NumberOfInstantiatedElements);
	};

	template<Concepts::NonConstant T>
	inline MAllocator<T>::MAllocator() noexcept
	{ }

	template<Concepts::NonConstant T>
	inline MAllocator<T>::~MAllocator()
	{ }

	template<Concepts::NonConstant T>
	inline constexpr T* MAllocator<T>::Allocate(const size_t NumberOfElements)
	{
		if (NumberOfElements == 0)
		{
			return nullptr;
		}

		return static_cast<T*>(malloc(ElementSize * NumberOfElements));
	}

	template<Concepts::NonConstant T>
	inline void MAllocator<T>::Deallocate(T* First, const size_t NumberOfInstantiatedElements)
	{
		if (First == nullptr)
		{
			return;
		}

		for (size_t i = 0; i < NumberOfInstantiatedElements; i++)
		{
			First[i].~T();
		}
		free(First);
		First = nullptr;
	}
}
#endif
