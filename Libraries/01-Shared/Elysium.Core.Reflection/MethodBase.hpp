/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_REFLECTION_METHODBASE
#define ELYSIUM_CORE_REFLECTION_METHODBASE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_REFLECTION_MEMBERINFO
#include "MemberInfo.hpp"
#endif

namespace Elysium::Core::Reflection
{
	class ELYSIUM_CORE_API MethodBase : public MemberInfo
	{
	public:
		virtual ~MethodBase();
	protected:
		MethodBase();
	};
}
#endif
