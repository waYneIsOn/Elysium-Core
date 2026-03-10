/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_WEAKPOINTER
#define ELYSIUM_CORE_TEMPLATE_MEMORY_WEAKPOINTER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REMOVEREFERENCE
#include "RemoveReference.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_SHAREDPOINTER
#include "SharedPointer.hpp"
#endif

namespace Elysium::Core::Template::Memory
{
	/*
	template <class T>
	class WeakPointer
	{
	public:
		using Pointer = Functional::RemoveReferenceType<T>*;
	public:
		constexpr WeakPointer(Pointer Data) noexcept;

		constexpr WeakPointer(const WeakPointer& Source);

		constexpr WeakPointer(WeakPointer&& Right) noexcept;

		constexpr ~WeakPointer();
	public:
		constexpr WeakPointer<T>& operator=(const WeakPointer& Source);

		constexpr WeakPointer<T>& operator=(WeakPointer&& Right) noexcept;
	public:
		constexpr WeakPointer<T>::Pointer operator->() const noexcept;
	public:
		constexpr WeakPointer<T>::Pointer GetUnderlyingPointer() const noexcept;

		constexpr WeakPointer<T>::Pointer Release() noexcept;
	private:
		Pointer _Data;
	};
	*/
}
#endif
