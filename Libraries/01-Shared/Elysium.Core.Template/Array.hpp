/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_COLLECTIONS_ARRAY
#define ELYSIUM_CORE_TEMPLATE_COLLECTIONS_ARRAY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COLLECTIONS_DEFAULTALLOCATOR
#include "DefaultAllocator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_MOVE
#include "Move.hpp"
#endif

namespace Elysium::Core::Template::Collections
{
	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template <class T>
	class Array final
	{
	private:
		static const size_t ElementSize = sizeof(T);
	public:

	public:
		static void Clear(T* First, const size_t Length) noexcept;

		static void Copy(const T* Source, T* Destination, const size_t Length);

		static void Move(T* Source, T* Destination, const size_t Length) noexcept;

		//static void Reverse(T* First, const size_t Length);
	};

	template<class T>
	inline void Array<T>::Clear(T* First, const size_t Length) noexcept
	{
		if (First == nullptr || Length == 0)
		{
			return;
		}

		std::memset(First, 0x00, Length * ElementSize);
		/*
		while (Length--)
		{
			*First[Length] = 0x00;
		}
		*/
	}

	template<class T>
	inline void Array<T>::Copy(const T* Source, T* Destination, const size_t Length)
	{
		if (Source == nullptr || Destination == nullptr || Length == 0)
		{
			return;
		}

		for (size_t i = 0; i < Length; i++)
		{
			Destination[i] = Source[i];
		}
	}

	template<class T>
	inline void Array<T>::Move(T* Source, T* Destination, const size_t Length) noexcept
	{
		if (Source == nullptr || Destination == nullptr || Length == 0)
		{
			return;
		}

		for (size_t i = 0; i < Length; i++)
		{
			Destination[i] = TypeTraits::Move(Source[i]);
		}
	}
}
#endif
