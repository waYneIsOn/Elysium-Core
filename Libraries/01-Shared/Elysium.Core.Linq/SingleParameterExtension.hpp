/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_LINQ_SINGLEPARAMETEREXTENSION
#define ELYSIUM_CORE_LINQ_SINGLEPARAMETEREXTENSION

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Linq
{
	// this struct is used by Extension as a wrapper-functionality
	template<class LinqContainerType, class ParameterType>
	struct SingleParameterExtension
	{
		SingleParameterExtension(ParameterType Value)
			: Value(Value)
		{}

		ParameterType Value;

		template<class ContainerType>
		friend auto operator>>(ContainerType && Container, SingleParameterExtension && Input)
		{
			return LinqContainerType()(std::forward<ContainerType>(Container), Input.Value);
		}
	};
}
#endif
