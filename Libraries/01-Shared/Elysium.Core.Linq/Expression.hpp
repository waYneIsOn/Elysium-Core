/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_LINQ_EXPRESSIONS_EXPRESSION
#define ELYSIUM_CORE_LINQ_EXPRESSIONS_EXPRESSION

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
