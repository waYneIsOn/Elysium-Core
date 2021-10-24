/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_ARRAY
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_ARRAY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REVERSE
#include "Reverse.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template <class T>
	class Array final
	{
	public:
		static void Clear(T* First, const Elysium::Core::size NumberOfElements) noexcept;

		static void Copy(const T* Source, T* Destination, const Elysium::Core::size NumberOfElements);

		static void Move(T* Source, T* Destination, const Elysium::Core::size NumberOfElements) noexcept;

		static void Reverse(T* First, const Elysium::Core::size NumberOfElements) noexcept;
	};

	template<class T>
	inline void Array<T>::Clear(T* First, const Elysium::Core::size NumberOfElements) noexcept
	{
		if (First == nullptr || NumberOfElements == 0)
		{
			return;
		}

		// ToDo: custom implementation (os-functionality or iterate byte by byte/element by element?)
		memset(First, 0x00, sizeof(T) * NumberOfElements);
	}

	template<class T>
	inline void Array<T>::Copy(const T* Source, T* Destination, const Elysium::Core::size NumberOfElements)
	{
		if (Source == nullptr || Destination == nullptr || NumberOfElements == 0)
		{
			return;
		}

		for (Elysium::Core::size i = 0; i < NumberOfElements; i++)
		{
			Destination[i] = Source[i];
		}
	}

	template<class T>
	inline void Array<T>::Move(T* Source, T* Destination, const Elysium::Core::size NumberOfElements) noexcept
	{
		if (Source == nullptr || Destination == nullptr || NumberOfElements == 0)
		{
			return;
		}

		for (Elysium::Core::size i = 0; i < NumberOfElements; i++)
		{
			Destination[i] = Functional::Move(Source[i]);
		}
	}

	template<class T>
	inline void Array<T>::Reverse(T* First, const Elysium::Core::size NumberOfElements) noexcept
	{
		if (First == nullptr || NumberOfElements < 2)
		{
			return;
		}

		Elysium::Core::Template::Functional::Reverse(First, &First[NumberOfElements - 1]);
	}
}
#endif
