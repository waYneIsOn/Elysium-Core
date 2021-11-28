/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_OBJECT
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_OBJECT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_POINTER
#include "Pointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_REFERENCE
#include "Reference.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_VALUE
#include "Value.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	class Object final
	{
	public:
		Object() = delete;

		Object(const Object& Source) = delete;

		Object(Object&& Right) noexcept = delete;

		~Object() = delete;
	public:
		Object& operator=(const Object& Source) = delete;

		Object& operator=(Object&& Right) noexcept = delete;
	public:
		template <Concepts::Pointer T>
		static Elysium::Core::size GetHashCode(const T Key);
		
		template <Concepts::Reference T>
		static Elysium::Core::size GetHashCode(const T Key);
		
		template <Concepts::Value T>
		static Elysium::Core::size GetHashCode(const T Key);
	};

	template<Concepts::Pointer T>
	inline Elysium::Core::size Object::GetHashCode(const T Key)
	{
		return Key->GetHashCode();
	}
	
	template<Concepts::Reference T>
	inline Elysium::Core::size Object::GetHashCode(const T Key)
	{
		return Key.GetHashCode();
	}

	template<Concepts::Value T>
	inline Elysium::Core::size Object::GetHashCode(const T Key)
	{
		return Key.GetHashCode();
	}

	template<>
	inline Elysium::Core::size Object::GetHashCode<Elysium::Core::uint8_t>(const Elysium::Core::uint8_t Key)
	{
		return static_cast<Elysium::Core::size>(Key);
	}
}
#endif
