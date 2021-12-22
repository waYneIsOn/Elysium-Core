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

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REMOVEREFERENCE
#include "RemoveReference.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTDELETER
#include "DefaultDeleter.hpp"
#endif

namespace Elysium::Core::Template::Memory
{
	template <class T, class Deleter = DefaultDeleter<T>>
	class UniquePointer
	{
	public:
		using Pointer = Functional::RemoveReferenceType<T>*;
	public:
		UniquePointer(Pointer Data);

		UniquePointer(const UniquePointer& Source) = delete;

		UniquePointer(UniquePointer&& Right) noexcept;

		~UniquePointer();
	public:
		UniquePointer<T, Deleter>& operator=(const UniquePointer& Source) = delete;

		UniquePointer<T, Deleter>& operator=(UniquePointer&& Right) noexcept;
	public:
		UniquePointer<T, Deleter>::Pointer operator->() const noexcept;
	public:
		UniquePointer<T, Deleter>::Pointer GetUnderlyingPointer() const noexcept;

		UniquePointer<T, Deleter>::Pointer Release() noexcept;
	private:
		inline static Deleter _Deleter = Deleter();
	private:
		Pointer _Data;
	};

	template<class T, class Deleter>
	inline UniquePointer<T, Deleter>::UniquePointer(Pointer Data)
		: _Data(Data)
	{ }

	template<class T, class Deleter>
	inline UniquePointer<T, Deleter>::UniquePointer(UniquePointer&& Right) noexcept
		: _Data(nullptr)
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
	}

	template<class T, class Deleter>
	inline UniquePointer<T, Deleter>::~UniquePointer()
	{
		_Deleter(_Data);
	}

	template<class T, class Deleter>
	inline UniquePointer<T, Deleter>& UniquePointer<T, Deleter>::operator=(UniquePointer<T, Deleter>&& Right) noexcept
	{
		if (this != &Right)
		{
			_Deleter(_Data);

			_Data = Elysium::Core::Template::Functional::Move(Right._Data);

			Right._Data = nullptr;
		}
		return *this;
	}

	template<class T, class Deleter>
	inline UniquePointer<T, Deleter>::Pointer UniquePointer<T, Deleter>::operator->() const noexcept
	{
		return _Data;
	}

	template<class T, class Deleter>
	inline UniquePointer<T, Deleter>::Pointer UniquePointer<T, Deleter>::GetUnderlyingPointer() const noexcept
	{
		return _Data;
	}

	template<class T, class Deleter>
	inline UniquePointer<T, Deleter>::Pointer UniquePointer<T, Deleter>::Release() noexcept
	{
		Pointer TemporaryData = _Data;
		_Data = nullptr;

		return TemporaryData;
	}
}
#endif
