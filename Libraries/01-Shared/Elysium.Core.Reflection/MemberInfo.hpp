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

#ifndef ELYSIUM_CORE_STRINGVIEW
#include "../Elysium.Core/StringView.hpp"
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
				virtual ~MemberInfo();

				const StringView GetName() const;
			protected:
				MemberInfo(); 

				String _Name;
			};
		}
	}
}
#endif
