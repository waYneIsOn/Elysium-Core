/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_REFLECTION_METHODINFO
#define ELYSIUM_CORE_REFLECCTION_METHODINFO

#ifndef ELYSIUM_CORE_REFLECTION_METHODBASE
#include "MethodBase.hpp"
#endif

namespace Elysium::Core::Reflection
{
	class ELYSIUM_CORE_API MethodInfo : public MethodBase
	{
	public:
		virtual ~MethodInfo();
	protected:
		MethodInfo();
	};
}
#endif
