/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_REFLECTION_FIELDINFO
#define ELYSIUM_CORE_REFLECTION_FIELDINFO

#ifndef ELYSIUM_CORE_REFLECTION_MEMBERINFO
#include "MemberInfo.hpp"
#endif

namespace Elysium::Core::Reflection
{
	class ELYSIUM_CORE_API FieldInfo : public MemberInfo
	{
	public:
		virtual ~FieldInfo();
	protected:
		FieldInfo();

		void* _Address;
	};
}
#endif
