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
		constexpr UniquePointer(Pointer Data) noexcept;

		constexpr UniquePointer(const UniquePointer& Source) = delete;

		constexpr UniquePointer(UniquePointer&& Right) noexcept;

		constexpr ~UniquePointer();
	public:
		constexpr UniquePointer<T, Deleter>& operator=(const UniquePointer& Source) = delete;

		constexpr UniquePointer<T, Deleter>& operator=(UniquePointer&& Right) noexcept;
	public:
		/*
		template <class... Args>
		static constexpr UniquePointer<T, Deleter> MakeUnique(Args&&...) noexcept;
		*/
	public:
		constexpr UniquePointer<T, Deleter>::Pointer operator->() const noexcept;
	public:
		constexpr UniquePointer<T, Deleter>::Pointer GetUnderlyingPointer() const noexcept;

		constexpr UniquePointer<T, Deleter>::Pointer Release() noexcept;
	private:
		inline static Deleter _Deleter = Deleter();
	private:
		Pointer _Data;
	};

	template<class T, class Deleter>
	inline constexpr UniquePointer<T, Deleter>::UniquePointer(Pointer Data) noexcept
		: _Data(Data)
	{ }
	
	template<class T, class Deleter>
	inline constexpr UniquePointer<T, Deleter>::UniquePointer(UniquePointer&& Right) noexcept
		: _Data(nullptr)
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
	}
	
	template<class T, class Deleter>
	inline constexpr UniquePointer<T, Deleter>::~UniquePointer()
	{
		if (_Data != nullptr)
		{
			_Deleter(_Data);
			_Data = nullptr;
		}
	}
	
	template<class T, class Deleter>
	inline constexpr UniquePointer<T, Deleter>& UniquePointer<T, Deleter>::operator=(UniquePointer<T, Deleter>&& Right) noexcept
	{
		if (this != &Right)
		{
			if (_Data == nullptr)
			{
				_Deleter(_Data);
			}

			_Data = Elysium::Core::Template::Functional::Move(Right._Data);

			Right._Data = nullptr;
		}
		return *this;
	}
	/*
	template<class T, class Deleter>
	template<class ...Args>
	inline constexpr UniquePointer<T, Deleter> UniquePointer<T, Deleter>::MakeUnique(Args && ...) noexcept
	{
		// @ToDo: forward arguments
		return UniquePointer<T, Deleter>(new T( Args... ));
	}
	*/
	template<class T, class Deleter>
	inline constexpr UniquePointer<T, Deleter>::Pointer UniquePointer<T, Deleter>::operator->() const noexcept
	{
		return _Data;
	}

	template<class T, class Deleter>
	inline constexpr UniquePointer<T, Deleter>::Pointer UniquePointer<T, Deleter>::GetUnderlyingPointer() const noexcept
	{
		return _Data;
	}

	template<class T, class Deleter>
	inline constexpr UniquePointer<T, Deleter>::Pointer UniquePointer<T, Deleter>::Release() noexcept
	{
		Pointer TemporaryData = _Data;
		_Data = nullptr;

		return TemporaryData;
	}
}
#endif
