/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_UNIQUEPOINTER
#define ELYSIUM_CORE_TEMPLATE_MEMORY_UNIQUEPOINTER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_POINTER
#include "Pointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REMOVEREFERENCE
#include "RemoveReference.hpp"
#endif

namespace Elysium::Core::Template::Memory
{
	template <class T>
	class UniquePointer
	{
	public:
		//using Pointer = Functional::RemoveReference<T>::Type;
		using Pointer = T*;
	public:
		UniquePointer(Pointer Data);

		UniquePointer(const UniquePointer& Source) = delete;

		UniquePointer(UniquePointer&& Right) noexcept;

		~UniquePointer();
	public:
		UniquePointer<T>& operator=(const UniquePointer& Source) = delete;

		UniquePointer<T>& operator=(UniquePointer&& Right) noexcept;

		UniquePointer<T>::Pointer operator->() const noexcept;
	public:
		UniquePointer<T>::Pointer Get() const;
	private:
		Pointer _Data;
	};

	template<class T>
	inline UniquePointer<T>::UniquePointer(Pointer Data)
		: _Data(Data)
	{ }

	template<class T>
	inline UniquePointer<T>::UniquePointer(UniquePointer && Right) noexcept
		: _Data(nullptr)
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
	}

	template<class T>
	inline UniquePointer<T>::~UniquePointer()
	{
		if (_Data != nullptr)
		{
			delete _Data;
			_Data = nullptr;
		}
	}

	template<class T>
	inline UniquePointer<T>& UniquePointer<T>::operator=(UniquePointer&& Right) noexcept
	{
		if (this != &Right)
		{
			if (_Data != nullptr)
			{
				delete[] _Data;
				_Data = nullptr;
			}

			_Data = Right._Data;

			Right._Data = nullptr;
		}
		return *this;
	}

	template<class T>
	inline UniquePointer<T>::Pointer UniquePointer<T>::operator->() const noexcept
	{
		return _Data;
	}

	template<class T>
	inline UniquePointer<T>::Pointer UniquePointer<T>::Get() const
	{
		return _Data;
	}
}
#endif
