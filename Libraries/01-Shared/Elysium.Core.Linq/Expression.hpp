/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_LINQ_EXPRESSIONS_EXPRESSION
#define ELYSIUM_CORE_LINQ_EXPRESSIONS_EXPRESSION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_LINQ_API
#include "API.hpp"
#endif

namespace Elysium::Core::Linq::Expressions
{
	class ELYSIUM_CORE_LINQ_API Expression
	{
	public:
		virtual ~Expression();
	protected:
		Expression();
	};
}
#endif
