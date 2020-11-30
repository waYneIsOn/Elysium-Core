/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_REFLECTION_MEMBERINFO
#define ELYSIUM_CORE_REFLECTION_MEMBERINFO

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_STRINGVIEW
#include "../Elysium.Core/StringView.hpp"
#endif

namespace Elysium::Core::Reflection
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
#endif
