/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_ACTIVATOR
#define ELYSIUM_CORE_TEMPLATE_MEMORY_ACTIVATOR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_REFLECTION_TYPE
#include "../Elysium.Core.Reflection/Type.hpp"
#endif

namespace Elysium::Core::Template::Memory
{
	class Activator final
	{
	public:
		Activator() noexcept = delete;

		Activator(const Activator& Source) = delete;

		Activator(Activator&& Right) noexcept = delete;

		~Activator() = delete;
	public:
		Activator& operator=(const Activator& Source) = delete;

		Activator& operator=(Activator&& Right) noexcept = delete;
	public:
		template <class T>
		static T CreateInstance();

		template <class T, class ...Args>
		static T CreateInstance(Args... Arguments);
	};

	template<class T>
	inline T Activator::CreateInstance()
	{
		return T();
	}

	template<class T, class ...Args>
	inline T Activator::CreateInstance(Args... Arguments)
	{
		return T(Arguments...);
	}
}
#endif
