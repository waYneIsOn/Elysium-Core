/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICBASE
#define ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICBASE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMORYORDER
#include "MemoryOrder.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_SHAREDMUTEX
#include "SharedMutex.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_CONDITIONAL
#include "Conditional.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISREFERENCE
#include "IsReference.hpp"
#endif

#ifndef __WFILE__
// @ToDo: get rid of these lines asap
#define _CRT_WIDE_(s) L ## s
#define _CRT_WIDE(s) _CRT_WIDE_(s)
#define __WFILE__     _CRT_WIDE(__FILE__)
#endif

namespace Elysium::Core::Template::Threading
{
	template <class T, Elysium::Core::Template::System::size SizeOfT>
	class _AtomicBase
	{
	public:
		constexpr _AtomicBase() noexcept = default;

		constexpr _AtomicBase(Elysium::Core::Template::TypeTraits::ConditionalType<Elysium::Core::Template::TypeTraits::IsReferenceValue<T>, T, const T> Value) noexcept;

		_AtomicBase(const _AtomicBase& Source) = delete;

		_AtomicBase(_AtomicBase&& Right) noexcept = delete;

		~_AtomicBase() = default;
	public:
		_AtomicBase& operator=(const _AtomicBase& Source) = delete;

		_AtomicBase& operator=(_AtomicBase&& Right) noexcept = delete;
	protected:
		T Load(const Elysium::Core::Template::Memory::MemoryOrder Order = Elysium::Core::Template::Memory::MemoryOrder::SequentiallyConsistent) const noexcept;
		
		T Store(const T Value, const Elysium::Core::Template::Memory::MemoryOrder Order = Elysium::Core::Template::Memory::MemoryOrder::SequentiallyConsistent) noexcept; private:
	private:
		void ValidateMemoryOrderLoad(const Elysium::Core::Template::Memory::MemoryOrder Order) const noexcept;

		void ValidateMemoryOrderStore(const Elysium::Core::Template::Memory::MemoryOrder Order) const noexcept;
	protected:
		T _Value;
	private:
		mutable SharedMutex _SlimReaderWriterLock;
	};

	template<class T, Elysium::Core::Template::System::size SizeOfT>
	inline constexpr _AtomicBase<T, SizeOfT>::_AtomicBase(Elysium::Core::Template::TypeTraits::ConditionalType<Elysium::Core::Template::TypeTraits::IsReferenceValue<T>, T, const T> Value) noexcept
		: _Value(Value)
	{ }

	template<class T, Elysium::Core::Template::System::size SizeOfT>
	inline T _AtomicBase<T, SizeOfT>::Load(const Elysium::Core::Template::Memory::MemoryOrder Order) const noexcept
	{
		ValidateMemoryOrderLoad(Order);

		_SlimReaderWriterLock.LockExclusive();
		T CopiedValue = _Value;
		_SlimReaderWriterLock.UnlockExclusive();

		return CopiedValue;
	}

	template<class T, Elysium::Core::Template::System::size SizeOfT>
	inline T _AtomicBase<T, SizeOfT>::Store(const T Value, const Elysium::Core::Template::Memory::MemoryOrder Order) noexcept
	{
		ValidateMemoryOrderStore(Order);

		_SlimReaderWriterLock.LockExclusive();
		T CopiedValue = _Value;
		_Value = Value;
		_SlimReaderWriterLock.UnlockExclusive();

		return CopiedValue;
	}

	template<class T, Elysium::Core::Template::System::size SizeOfT>
	inline void _AtomicBase<T, SizeOfT>::ValidateMemoryOrderLoad(const Elysium::Core::Template::Memory::MemoryOrder Order) const noexcept
	{
		switch (Order)
		{
		case Elysium::Core::Template::Memory::MemoryOrder::Release:
		case Elysium::Core::Template::Memory::MemoryOrder::AcquireRelease:
#if defined _DEBUG
			_invalid_parameter(L"Incorrect memory order when loading atomic value.", L"", __WFILE__, __LINE__, 0);
#else
			_invalid_parameter_noinfo_noreturn();
#endif
			break;
		default:
			// all other memory order values should be ok for loading
			return;
		}
	}

	template<class T, Elysium::Core::Template::System::size SizeOfT>
	inline void _AtomicBase<T, SizeOfT>::ValidateMemoryOrderStore(const Elysium::Core::Template::Memory::MemoryOrder Order) const noexcept
	{
		switch (Order)
		{
		case Elysium::Core::Template::Memory::MemoryOrder::Consume:
		case Elysium::Core::Template::Memory::MemoryOrder::Acquire:
		case Elysium::Core::Template::Memory::MemoryOrder::AcquireRelease:
#if defined _DEBUG
			_invalid_parameter(L"Incorrect memory order when storing atomic value.", L"", __WFILE__, __LINE__, 0);
#else
			_invalid_parameter_noinfo_noreturn();
#endif
			break;
		default:
			// all other memory order values should be ok for storing
			return;
		}
	}
}
#endif
