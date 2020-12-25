/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

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
		SingleParameterExtension(const ParameterType Value)
			: Value(Value)
		{ }

		const ParameterType Value;

		template<class ContainerType>
		friend auto operator>>(const ContainerType& Container, const SingleParameterExtension& Input)
		{
			return LinqContainerType()(Container, Input.Value);
		}
	};
}
#endif
