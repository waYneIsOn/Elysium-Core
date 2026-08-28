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
#include "../Functional/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REMOVEREFERENCE
#include "../Functional/RemoveReference.hpp"
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
		constexpr UniquePointer() = delete;

		inline constexpr UniquePointer(Pointer Data) noexcept
			: _Deleter{}, _Data(Data)
		{ }

		constexpr UniquePointer(const UniquePointer& Source) = delete;

		inline constexpr UniquePointer(UniquePointer&& Right) noexcept
			: _Deleter{}, _Data {}
		{
			*this = Elysium::Core::Template::Functional::Move(Right);
		}

		inline constexpr ~UniquePointer()
		{
			if (nullptr != _Data)
			{
				_Deleter(_Data);
				_Data = nullptr;
			}
		}
	public:
		constexpr UniquePointer<T, Deleter>& operator=(const UniquePointer& Source) = delete;

		inline constexpr UniquePointer<T, Deleter>& operator=(UniquePointer&& Right) noexcept
		{
			if (this != &Right)
			{
				if (nullptr == _Data)
				{
					_Deleter(_Data);
				}

				_Data = Elysium::Core::Template::Functional::Move(Right._Data);

				Right._Data = nullptr;
			}
			return *this;
		}
	public:
		/*
		template <class... Args>
		static constexpr UniquePointer<T, Deleter> MakeUnique(Args&&...) noexcept;
		*/
	public:
		inline constexpr UniquePointer<T, Deleter>::Pointer operator->() const noexcept
		{
			return _Data;
		}
	public:
		inline constexpr UniquePointer<T, Deleter>::Pointer GetUnderlyingPointer() const noexcept
		{
			return _Data;
		}

		inline constexpr UniquePointer<T, Deleter>::Pointer Release() noexcept
		{
			Pointer TemporaryData = _Data;
			_Data = nullptr;

			return TemporaryData;
		}
	private:
		Deleter _Deleter;
		Pointer _Data;
	};

	/*
	template<class T, class Deleter>
	template<class ...Args>
	inline constexpr UniquePointer<T, Deleter> UniquePointer<T, Deleter>::MakeUnique(Args && ...) noexcept
	{
		// @ToDo: forward arguments
		return UniquePointer<T, Deleter>(new T( Args... ));
	}
	*/
}
#endif
