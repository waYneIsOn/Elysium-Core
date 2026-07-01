/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_CALLTRAITS
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_CALLTRAITS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REMOVEREFERENCE
#include "../Functional/RemoveReference.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_CONDITIONAL
#include "Conditional.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISTRIVIALLYCOPYABLE
#include "IsTriviallyCopyable.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
	template <class T>
	class CallTraits
	{
	public:
		using ValueType = Elysium::Core::Template::Functional::RemoveReferenceType<T>;
		using ConstType = const ValueType;

		using Reference = ValueType&;
		using ConstReference = const ValueType&;

		using Pointer = ValueType*;
		using ConstPointer = const ValueType*;

		using ParameterType = Elysium::Core::Template::TypeTraits::ConditionalType<sizeof(T) <= 2 * sizeof(void*) && Elysium::Core::Template::TypeTraits::IsTriviallyCopyableValue<T>,
			ValueType, ConstReference>;
	};
}
#endif
