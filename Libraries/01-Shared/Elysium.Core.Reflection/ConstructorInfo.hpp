/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_REFLECTION_CONSTRUCTORINFO
#define ELYSIUM_CORE_REFLECTION_CONSTRUCTORINFO

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_REFLECTION_METHODBASE
#include "MethodBase.hpp"
#endif

namespace Elysium::Core::Reflection
{
	class ELYSIUM_CORE_API ConstructorInfo : public MethodBase
	{
	public:
		virtual ~ConstructorInfo();
	protected:
		ConstructorInfo();
	};
}
#endif
