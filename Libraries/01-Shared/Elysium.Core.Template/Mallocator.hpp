/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MALLOCATOR
#define ELYSIUM_CORE_TEMPLATE_MEMORY_MALLOCATOR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_NONCONSTANT
#include "NonConstant.hpp"
#endif

#ifndef _INC_CRTDBG
#include <cstdlib>
#endif

namespace Elysium::Core::Template::Memory
{
	/// <summary>
	/// 
	/// </summary>
	template<Concepts::NonConstant T>
	class MAllocator final
	{
	private:
		static const Elysium::Core::size ElementSize = sizeof(T);
	public:
		/// <summary>
		/// Creates a new instance.
		/// </summary>
		MAllocator() noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Source"></param>
		MAllocator(const MAllocator& Source) = delete;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Right"></param>
		MAllocator(MAllocator&& Right) noexcept = delete;

		/// <summary>
		/// Destroys this instance.
		/// </summary>
		~MAllocator();

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Source"></param>
		/// <returns></returns>
		MAllocator<T>& operator=(const MAllocator& Source) = delete;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Right"></param>
		/// <returns></returns>
		MAllocator<T>& operator=(MAllocator&& Right) noexcept = delete;

		/// <summary>
		/// Allocates the exact amount of memory required for given number of elements using malloc(...).
		/// This will not initialize the block of memory though!
		/// </summary>
		/// <param name="NumberOfElements"></param>
		/// <returns></returns>
		constexpr T* Allocate(const Elysium::Core::size NumberOfElements);

		/// <summary>
		/// Calls destructor for the first number of instantiated elements before cleaning up the previously allocated memory using free(...).
		/// </summary>
		/// <param name="First">Pointer to the starting element.</param>
		/// <param name="NumberOfInstantiatedElements">Number of elements the destructors needs to be called for.</param>
		void Deallocate(T* First, const Elysium::Core::size NumberOfInstantiatedElements);
	};

	template<Concepts::NonConstant T>
	inline MAllocator<T>::MAllocator() noexcept
	{ }

	template<Concepts::NonConstant T>
	inline MAllocator<T>::~MAllocator()
	{ }

	template<Concepts::NonConstant T>
	inline constexpr T* MAllocator<T>::Allocate(const Elysium::Core::size NumberOfElements)
	{
		if (NumberOfElements == 0)
		{
			return nullptr;
		}

		return static_cast<T*>(std::malloc(ElementSize * NumberOfElements));
	}

	template<Concepts::NonConstant T>
	inline void MAllocator<T>::Deallocate(T* First, const Elysium::Core::size NumberOfInstantiatedElements)
	{
		if (First == nullptr)
		{
			return;
		}

		for (Elysium::Core::size i = 0; i < NumberOfInstantiatedElements; i++)
		{
			First[i].~T();
		}
		std::free(First);
		First = nullptr;
	}
}
#endif
