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

		UniquePointer(UniquePointer&& Right) noexcept = delete;

		~UniquePointer();
	public:
		UniquePointer<T>& operator=(const UniquePointer& Source) = delete;

		UniquePointer<T>& operator=(UniquePointer&& Right) noexcept = delete;

		UniquePointer<T>::Pointer operator->() const noexcept;
	public:
		UniquePointer<T>::Pointer GetUnderlyingPointer() const noexcept;

		UniquePointer<T>::Pointer Release() noexcept;
	private:
		Pointer _Data;
	};

	template<class T>
	inline UniquePointer<T>::UniquePointer(Pointer Data)
		: _Data(Data)
	{ }

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
	inline UniquePointer<T>::Pointer UniquePointer<T>::operator->() const noexcept
	{
		return _Data;
	}

	template<class T>
	inline UniquePointer<T>::Pointer UniquePointer<T>::GetUnderlyingPointer() const noexcept
	{
		return _Data;
	}

	template<class T>
	inline UniquePointer<T>::Pointer UniquePointer<T>::Release() noexcept
	{
		Pointer TemporaryData = _Data;
		_Data = nullptr;

		return TemporaryData;
	}
}
#endif
