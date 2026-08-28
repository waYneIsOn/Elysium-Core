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
#include "Functional/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REMOVEREFERENCE
#include "Functional/RemoveReference.hpp"
#endif
/*
#ifndef ELYSIUM_CORE_TEMPLATE_EXPORT_MODULE
import Elysium.Core.Template.Functional;
#endif
*/
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
		using Pointer = Elysium::Core::Template::Functional::RemoveReferenceType<T>*;

		using ConstPointer = const Pointer;
	public:
		constexpr ObserverPointer() noexcept = default;
		
		inline constexpr ObserverPointer(Pointer Data) noexcept
			: _Data(Data)
		{ }

		constexpr ObserverPointer(const ObserverPointer& Source) = default;

		constexpr ObserverPointer(ObserverPointer&& Right) noexcept = default;
		
		constexpr ~ObserverPointer() = default;
	public:
		constexpr ObserverPointer<T>& operator=(const ObserverPointer& Source) = default;

		constexpr ObserverPointer<T>& operator=(ObserverPointer&& Right) noexcept = default;
	public:
		inline ObserverPointer<T>::Pointer operator->() noexcept
		{
			return _Data;
		}

		inline constexpr ObserverPointer<T>::ConstPointer operator->() const noexcept
		{
			return _Data;
		}
	public:
		inline explicit operator ObserverPointer<T>::Pointer()
		{
			return _Data;
		}
	private:
		Pointer _Data;
	};
}
#endif
