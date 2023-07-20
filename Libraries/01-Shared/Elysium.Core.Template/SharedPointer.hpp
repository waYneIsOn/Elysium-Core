/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_SHAREPOINTER
#define ELYSIUM_CORE_TEMPLATE_MEMORY_SHAREPOINTER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REMOVEREFERENCE
#include "RemoveReference.hpp"
#endif

namespace Elysium::Core::Template::Memory
{
	/*
	template <class T>
	class SharedPointer
	{
	public:
		using Pointer = Functional::RemoveReferenceType<T>*;
	public:
		constexpr SharedPointer(Pointer Data) noexcept;

		constexpr SharedPointer(const SharedPointer& Source);

		constexpr SharedPointer(SharedPointer&& Right) noexcept;

		constexpr ~SharedPointer();
	public:
		constexpr SharedPointer<T>& operator=(const SharedPointer& Source);

		constexpr SharedPointer<T>& operator=(SharedPointer&& Right) noexcept;
	public:
		constexpr SharedPointer<T>::Pointer operator->() const noexcept;
	public:
		constexpr SharedPointer<T>::Pointer GetUnderlyingPointer() const noexcept;

		constexpr SharedPointer<T>::Pointer Release() noexcept;
	private:
		Pointer _Data;
	};
	*/
}
#endif
