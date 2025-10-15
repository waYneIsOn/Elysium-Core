/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_UTILITY_REPEAT
#define ELYSIUM_CORE_TEMPLATE_UTILITY_REPEAT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_UTILITY_INTEGERSEQUENCE
#include "IntegerSequence.hpp"
#endif

namespace Elysium::Core::Template::Utility
{
	template<class T, Elysium::Core::Template::System::size... Values>
	class __Repeat
	{ };

	template<class T, T... Values, Elysium::Core::Template::System::size... AdditionalValues>
	class __Repeat<IntegerSequence<T, Values...>, AdditionalValues...>
	{
	public:
		typedef IntegerSequence<T, 
			Values...,
			static_cast<T>(sizeof...(Values) + Values)...,
			static_cast<T>(2 * sizeof...(Values) + Values)...,
			static_cast<T>(3 * sizeof...(Values) + Values)...,
			static_cast<T>(4 * sizeof...(Values) + Values)...,
			static_cast<T>(5 * sizeof...(Values) + Values)...,
			static_cast<T>(6 * sizeof...(Values) + Values)...,
			static_cast<T>(7 * sizeof...(Values) + Values)...,
			AdditionalValues...> Type;
	};
}
#endif
