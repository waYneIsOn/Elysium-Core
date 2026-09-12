/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICPOINTER_WINDOWS
#define ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICPOINTER_WINDOWS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_POINTER
#include "../Concepts/Pointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICBASE
#include "_AtomicBase.hpp"
#endif

namespace Elysium::Core::Template::Threading
{
	/// <summary>
	/// 
	/// https://learn.microsoft.com/en-us/windows/win32/sync/interlocked-variable-access
	/// </summary>
	template <class T>
	class _AtomicPointer
		: public _AtomicBase<T, sizeof(void*)>
	{
	public:
		constexpr _AtomicPointer() noexcept = default;

		inline constexpr _AtomicPointer(Elysium::Core::Template::TypeTraits::ConditionalType<Elysium::Core::Template::TypeTraits::IsReferenceValue<T>, T, const T> Value) noexcept 
			: _AtomicBase<T, sizeof(void*)>(Value)
		{ }

		constexpr _AtomicPointer(const _AtomicPointer& Source) = delete;

		constexpr _AtomicPointer(_AtomicPointer&& Right) noexcept = delete;

		constexpr ~_AtomicPointer() = default;
	public:
		inline T operator++() noexcept
		{
#if ELYSIUM_CORE_BITNESS == 64
			return reinterpret_cast<T>(_InterlockedExchangeAdd64(reinterpret_cast<volatile Elysium::Core::Template::System::int64_t*>(this->_Value), 1));
#elif ELYSIUM_CORE_BITNESS == 32
			return reinterpret_cast<T>(_InterlockedExchangeAdd(reinterpret_cast<volatile long*>(this->_Value), 1));
#else
#error "unsupported os regarding bitness"
#endif
		}

		inline T operator++(Elysium::Core::Template::System::int32_t) noexcept
		{
#if ELYSIUM_CORE_BITNESS == 64
			Elysium::Core::Template::System::int64_t Result =
				_InterlockedExchangeAdd64(reinterpret_cast<volatile Elysium::Core::Template::System::int64_t*>(this->_Value), 1);
#elif ELYSIUM_CORE_BITNESS == 32
			Elysium::Core::Template::System::int32_t Result =
				_InterlockedExchangeAdd(reinterpret_cast<volatile long*>(this->_Value), 1);
#else
#error "unsupported os regarding bitness"
#endif

			--Result;
			return reinterpret_cast<T>(Result);
		}

		// @ToDo
	};
}
#endif
#endif
