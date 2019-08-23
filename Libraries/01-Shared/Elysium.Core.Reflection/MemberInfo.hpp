/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_REFLECTION_MEMBERINFO
#define ELYSIUM_CORE_REFLECTION_MEMBERINFO

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Reflection
		{
			class ELYSIUM_CORE_API MemberInfo
			{
			public:
				~MemberInfo();

				String GetName();
			protected:
				MemberInfo();
			private:
				void* _Pointer;
				String _Name;
			};
		}
	}
}
#endif
