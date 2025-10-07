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

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMCMP
#include "MemCmp.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMCPY
#include "MemCpy.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMORYORDER
#include "MemoryOrder.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_COMPILER
#include "Compiler.hpp"
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

		constexpr _AtomicBase(const _AtomicBase& Source) = delete;

		constexpr _AtomicBase(_AtomicBase&& Right) noexcept = delete;

		constexpr ~_AtomicBase() = default;
	public:
		constexpr _AtomicBase& operator=(const _AtomicBase& Source) = delete;

		constexpr _AtomicBase& operator=(_AtomicBase&& Right) noexcept = delete;
	protected:
		T Load(const Elysium::Core::Template::Memory::MemoryOrder Order = Elysium::Core::Template::Memory::MemoryOrder::SequentiallyConsistent) const noexcept;
		
		void Store(const T Value, const Elysium::Core::Template::Memory::MemoryOrder Order = Elysium::Core::Template::Memory::MemoryOrder::SequentiallyConsistent) noexcept; 
		
		T Exchange(const T Value, const Elysium::Core::Template::Memory::MemoryOrder Order = Elysium::Core::Template::Memory::MemoryOrder::SequentiallyConsistent) noexcept;
		
		bool CompareExchangeStrong(T& Expected, const T Desired, const Elysium::Core::Template::Memory::MemoryOrder Order = Elysium::Core::Template::Memory::MemoryOrder::SequentiallyConsistent) noexcept;
	private:
		void ValidateMemoryOrderLoad(const Elysium::Core::Template::Memory::MemoryOrder Order) const noexcept;

		void ValidateMemoryOrderStore(const Elysium::Core::Template::Memory::MemoryOrder Order) const noexcept;

		void ValidateMemoryOrder(const Elysium::Core::Template::Memory::MemoryOrder Order) const noexcept;
	protected:
		T _Value;
	private:
		mutable SharedMutex _SlimReaderWriterLock;
	};

	template<class T, Elysium::Core::Template::System::size SizeOfT>
	inline constexpr _AtomicBase<T, SizeOfT>::_AtomicBase(Elysium::Core::Template::TypeTraits::ConditionalType<Elysium::Core::Template::TypeTraits::IsReferenceValue<T>, T, const T> Value) noexcept
		: _Value(Value), _SlimReaderWriterLock()
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
	inline void _AtomicBase<T, SizeOfT>::Store(const T Value, const Elysium::Core::Template::Memory::MemoryOrder Order) noexcept
	{
		ValidateMemoryOrderStore(Order);

		_SlimReaderWriterLock.LockExclusive();
		T CopiedValue = _Value;
		_Value = Value;
		_SlimReaderWriterLock.UnlockExclusive();
	}

	template<class T, Elysium::Core::Template::System::size SizeOfT>
	inline T _AtomicBase<T, SizeOfT>::Exchange(const T Value, const Elysium::Core::Template::Memory::MemoryOrder Order) noexcept
	{
		ValidateMemoryOrder(Order);

		_SlimReaderWriterLock.LockExclusive();
		T CopiedValue = _Value;
		_Value = Value;
		_SlimReaderWriterLock.UnlockExclusive();

		return CopiedValue;
	}

	template<class T, Elysium::Core::Template::System::size SizeOfT>
	inline bool _AtomicBase<T, SizeOfT>::CompareExchangeStrong(T& Expected, const T Desired, const Elysium::Core::Template::Memory::MemoryOrder Order) noexcept
	{
		ValidateMemoryOrder(Order);

		bool Result = false;
		void* AddressOfValue = static_cast<void*>(Elysium::Core::Template::System::Compiler::AddressOf(_Value));
		void* AddressOfExpected = static_cast<void*>(Elysium::Core::Template::System::Compiler::AddressOf(Expected));

		_SlimReaderWriterLock.LockExclusive();
		// @ToDo: MemCmp is possible as long as atomics are only using trivial types like primitives, enums, pointers etc.
		Result = Elysium::Core::Template::Memory::MemCmp(AddressOfValue, AddressOfExpected, sizeof(T)) == 0;
		if (Result)
		{
			const void* AddressOfDesired = static_cast<const void*>(Elysium::Core::Template::System::Compiler::AddressOf(Desired));
			Elysium::Core::Template::Memory::MemCpy(AddressOfValue, AddressOfDesired, sizeof(T));
		}
		else
		{
			Elysium::Core::Template::Memory::MemCpy(AddressOfExpected, AddressOfValue, sizeof(T));
		}
		_SlimReaderWriterLock.UnlockExclusive();

		return Result;
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

	template<class T, Elysium::Core::Template::System::size SizeOfT>
	inline void _AtomicBase<T, SizeOfT>::ValidateMemoryOrder(const Elysium::Core::Template::Memory::MemoryOrder Order) const noexcept
	{
		if (Order > Elysium::Core::Template::Memory::MemoryOrder::SequentiallyConsistent)
		{
#if defined _DEBUG
			_invalid_parameter(L"Incorrect memory order.", L"", __WFILE__, __LINE__, 0);
#else
			_invalid_parameter_noinfo_noreturn();
#endif
		}
	}
}
#endif
