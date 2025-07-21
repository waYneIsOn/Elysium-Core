/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_OBSERVERPOINTER
#define ELYSIUM_CORE_TEMPLATE_MEMORY_OBSERVERPOINTER

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
	template<typename T>
	using ObserverPointer = T*;
	*/

	template<typename T>
	class ObserverPointer
	{
	public:
		using Pointer = Functional::RemoveReferenceType<T>*;
	public:
		constexpr ObserverPointer() noexcept = default;
		
		//constexpr ObserverPointer(Pointer Data) noexcept;

		constexpr ObserverPointer(const ObserverPointer& Source) = default;

		constexpr ObserverPointer(ObserverPointer&& Right) noexcept = default;
		
		constexpr ~ObserverPointer() = default;
	public:
		constexpr ObserverPointer<T>& operator=(const ObserverPointer& Source) = default;

		constexpr ObserverPointer<T>& operator=(ObserverPointer&& Right) noexcept = default;
	public:
		//constexpr UniquePointer<T, Deleter>::Pointer operator->() const noexcept;
	public:
		//constexpr UniquePointer<T, Deleter>::Pointer GetUnderlyingPointer() const noexcept;

		//constexpr UniquePointer<T, Deleter>::Pointer Release() noexcept;
	private:
		Pointer _Data;
	};
}
#endif
