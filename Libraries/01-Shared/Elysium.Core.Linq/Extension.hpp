/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_LINQ_EXTENSION
#define ELYSIUM_CORE_LINQ_EXTENSION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_LINQ_SINGLEPARAMETEREXTENSION
#include "SingleParameterExtension.hpp"
#endif

#ifndef ELYSIUM_CORE_LINQ_ANY
#include "Any.hpp"
#endif

#ifndef ELYSIUM_CORE_LINQ_CONTAINS
#include "Contains.hpp"
#endif

#ifndef ELYSIUM_CORE_LINQ_COUNT
#include "Count.hpp"
#endif

#ifndef ELYSIUM_CORE_LINQ_WHERE
#include "Where.hpp"
#endif

namespace Elysium::Core::Linq
{
	// this struct allows linq-structs to be wrapped with the purpose of being able to call the operator(...)
	template<class LinqExpressionType>
	struct Extension
	{
		// operators for extensions without any parameter
		Extension<LinqExpressionType>& operator()()
		{
			return *this;
		}
		const Extension<LinqExpressionType>& operator()() const
		{
			return *this;
		}

		// operators for extensions with one parameter
		template<class ParameterType>
		auto operator()(ParameterType && Parameter1)
		{
			return SingleParameterExtension<LinqExpressionType, ParameterType>(Parameter1);
		}
		template<class ParameterType>
		auto operator()(ParameterType && Parameter1) const
		{
			return SingleParameterExtension<LinqExpressionType, ParameterType>(Parameter1);
		}
	};

	// the following operator allows to chain together containers and extensions
	template<class ContainerType, class LinqExpressionType>
	auto operator>>(ContainerType & Container, const Extension<LinqExpressionType>)
	{
		return LinqExpressionType()(Container);
	};

	// create instances of Extension for each struct so they can be used in a extension-like manner
	Extension<AnyContainer> Any = {};
	Extension<ContainsContainer> Contains = {};
	Extension<CountContainer> Count = {};
	Extension<WhereContainer> Where = {};
}
#endif
