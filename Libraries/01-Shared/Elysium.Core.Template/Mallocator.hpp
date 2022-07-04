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

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_NONCONSTANT
#include "NonConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
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
		static const System::size ElementSize = sizeof(T);
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
		constexpr T* Allocate(const System::size NumberOfElements);

		/// <summary>
		/// Calls destructor for the first number of instantiated elements before cleaning up the previously allocated memory using free(...).
		/// </summary>
		/// <param name="First">Pointer to the starting element.</param>
		/// <param name="NumberOfInstantiatedElements">Number of elements the destructors needs to be called for.</param>
		void Deallocate(T* First, const System::size NumberOfInstantiatedElements);
	};

	template<Concepts::NonConstant T>
	inline MAllocator<T>::MAllocator() noexcept
	{ }

	template<Concepts::NonConstant T>
	inline MAllocator<T>::~MAllocator()
	{ }

	template<Concepts::NonConstant T>
	inline constexpr T* MAllocator<T>::Allocate(const System::size NumberOfElements)
	{
		if (NumberOfElements == 0)
		{
			return nullptr;
		}

		void* Data = operator new[](ElementSize* NumberOfElements);
		memset(Data, 0x00, ElementSize * NumberOfElements);

		return static_cast<T*>(Data);
	}

	template<Concepts::NonConstant T>
	inline void MAllocator<T>::Deallocate(T* First, const System::size NumberOfInstantiatedElements)
	{
		if (First == nullptr)
		{
			return;
		}

		for (Elysium::Core::Template::System::size i = 0; i < NumberOfInstantiatedElements; i++)
		{
			First[i].~T();
		}
		//memset(First, 0x00, ElementSize* NumberOfInstantiatedElements);
		std::free(First);
		First = nullptr;
	}
}
#endif
