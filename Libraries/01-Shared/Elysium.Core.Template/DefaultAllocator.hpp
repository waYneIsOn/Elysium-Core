/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTALLOCATOR
#define ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTALLOCATOR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_NONCONSTANT
#include "NonConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMSET
#include "MemSet.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

namespace Elysium::Core::Template::Memory
{
	/// <summary>
	/// 
	/// </summary>
	template<Elysium::Core::Template::Concepts::NonConstant T>
	class DefaultAllocator final
	{
	public:
		using Pointer = T*;
	private:
		static const Elysium::Core::Template::System::size ElementSize = sizeof(T);
	public:
		/// <summary>
		/// Creates a new instance.
		/// </summary>
		constexpr DefaultAllocator() noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Source"></param>
		DefaultAllocator(const DefaultAllocator& Source) = delete;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Right"></param>
		DefaultAllocator(DefaultAllocator&& Right) noexcept = delete;

		/// <summary>
		/// Destroys this instance.
		/// </summary>
		constexpr ~DefaultAllocator();
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="Source"></param>
		/// <returns></returns>
		DefaultAllocator<T>& operator=(const DefaultAllocator& Source) = delete;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Right"></param>
		/// <returns></returns>
		DefaultAllocator<T>& operator=(DefaultAllocator&& Right) noexcept = delete;
	public:
		/// <summary>
		/// Allocates the exact amount of memory required for given number of elements using operator new[].
		/// This will not initialize the block of memory though!
		/// </summary>
		/// <param name="NumberOfElements"></param>
		/// <returns></returns>
		constexpr Pointer Allocate(const Elysium::Core::Template::System::size NumberOfElements);

		/// <summary>
		/// Calls destructor for the first number of instantiated elements before cleaning up the previously allocated memory using operator delete[].
		/// </summary>
		/// <param name="First">Pointer to the starting element.</param>
		/// <param name="NumberOfInstantiatedElements">Number of elements the destructors needs to be called for.</param>
		void Deallocate(Pointer First, const Elysium::Core::Template::System::size NumberOfInstantiatedElements);
	};

	template<Elysium::Core::Template::Concepts::NonConstant T>
	inline constexpr DefaultAllocator<T>::DefaultAllocator() noexcept
	{ }

	template<Elysium::Core::Template::Concepts::NonConstant T>
	inline constexpr DefaultAllocator<T>::~DefaultAllocator()
	{ }

	template<Elysium::Core::Template::Concepts::NonConstant T>
	inline constexpr Elysium::Core::Template::Memory::DefaultAllocator<T>::Pointer DefaultAllocator<T>::Allocate(const Elysium::Core::Template::System::size NumberOfElements)
	{
		if (NumberOfElements == 0)
		{
			return nullptr;
		}

		// @ToDo: this will not call any constructors and might cause problems with certain types. will have to see!
		void* Data = operator new[](ElementSize * NumberOfElements);
		Elysium::Core::Template::Memory::MemSet(Data, 0x00, ElementSize * NumberOfElements);
		
		return static_cast<T*>(Data);
	}

	template<Elysium::Core::Template::Concepts::NonConstant T>
	inline void DefaultAllocator<T>::Deallocate(Elysium::Core::Template::Memory::DefaultAllocator<T>::Pointer First, const Elysium::Core::Template::System::size NumberOfInstantiatedElements)
	{
		if (First == nullptr)
		{
			return;
		}

		for (Elysium::Core::Template::System::size i = 0; i < NumberOfInstantiatedElements; i++)
		{
			First[i].~T();
		}

		operator delete[](First);
		First = nullptr;
	}
}
#endif
