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

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
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
		Array() = delete;

		Array(const Array& Source) = delete;

		Array(Array&& Right) noexcept = delete;

		~Array() = delete;
	public:
		Array<T>& operator=(const Array& Source) = delete;

		Array<T>& operator=(Array&& Right) noexcept = delete;
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="First"></param>
		/// <param name="NumberOfElements"></param>
		static void Clear(T* First, const System::size NumberOfElements);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Source"></param>
		/// <param name="Destination"></param>
		/// <param name="NumberOfElements"></param>
		static void Copy(const T* Source, T* Destination, const System::size NumberOfElements);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Source"></param>
		/// <param name="Destination"></param>
		/// <param name="NumberOfElements"></param>
		/// <returns></returns>
		static void Move(T* Source, T* Destination, const System::size NumberOfElements) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="First"></param>
		/// <param name="NumberOfElements"></param>
		/// <returns></returns>
		static void Reverse(T* First, const System::size NumberOfElements) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="First"></param>
		/// <param name="Value"></param>
		/// <param name="NumberOfElements"></param>
		/// <returns></returns>
		static constexpr const System::size IndexOf(const T* First, const T& Value, const System::size NumberOfElements);
	};
	
	template<class T>
	inline void Array<T>::Clear(T* First, const Elysium::Core::Template::System::size NumberOfElements)
	{
		if (First == nullptr || NumberOfElements == 0)
		{
			return;
		}

		for (Elysium::Core::Template::System::size i = 0; i < NumberOfElements; i++)
		{
			//First[i]~();
			First[i] = T();
		}
	}
	
	template<class T>
	inline void Array<T>::Copy(const T* Source, T* Destination, const Elysium::Core::Template::System::size NumberOfElements)
	{
		if (Source == nullptr || Destination == nullptr || NumberOfElements == 0)
		{
			return;
		}

		for (Elysium::Core::Template::System::size i = 0; i < NumberOfElements; i++)
		{
			Destination[i] = Source[i];
		}
	}

	template<class T>
	inline void Array<T>::Move(T* Source, T* Destination, const Elysium::Core::Template::System::size NumberOfElements) noexcept
	{
		if (Source == nullptr || Destination == nullptr || NumberOfElements == 0)
		{
			return;
		}

		for (Elysium::Core::Template::System::size i = 0; i < NumberOfElements; i++)
		{
			Destination[i] = Functional::Move(Source[i]);
		}
	}

	template<class T>
	inline void Array<T>::Reverse(T* First, const Elysium::Core::Template::System::size NumberOfElements) noexcept
	{
		if (First == nullptr || NumberOfElements < 2)
		{
			return;
		}

		Elysium::Core::Template::Functional::Reverse(First, &First[NumberOfElements - 1]);
	}

	template<class T>
	inline constexpr const Elysium::Core::Template::System::size Array<T>::IndexOf(const T* First, const T& Value, const Elysium::Core::Template::System::size NumberOfElements)
	{
		if (First == nullptr || NumberOfElements < 1)
		{
			return;
		}

		for (Elysium::Core::Template::System::size i = 0; i < NumberOfElements; i++)
		{
			if (First[i] == Value)
			{
				return i;
			}
		}
		return static_cast<Elysium::Core::Template::System::size>(-1);
	}
}
#endif
