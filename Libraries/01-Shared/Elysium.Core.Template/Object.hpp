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

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_HASMETHOD
#include "HasMethod.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_INTEGER
#include "Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_POINTER
#include "Pointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_VALUE
#include "Value.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "String.hpp"
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
		template <class T> requires Concepts::Integer<T>
		static constexpr Elysium::Core::size GetHashCode(const T Key);
		
		template <class T> requires Concepts::HasMethod<T, Elysium::Core::size>
		static constexpr Elysium::Core::size GetHashCode(const T& Key);
		
		template <class T> requires Concepts::Pointer<T>
		static constexpr Elysium::Core::size GetHashCode(const T Key);
	};

	template<class T> requires Concepts::Integer<T>
	inline constexpr Elysium::Core::size Object::GetHashCode(const T Key)
	{
		return static_cast<Elysium::Core::size>(Key);
	}
	
	template<class T> requires Concepts::HasMethod<T, Elysium::Core::size>
	inline constexpr Elysium::Core::size Object::GetHashCode(const T& Key)
	{
		return Key.GetHashCode();
	}
	
	template<class T> requires Concepts::Pointer<T>
	inline constexpr Elysium::Core::size Object::GetHashCode(const T Key)
	{
		return GetHashCode(*Key);
	}
}
#endif
