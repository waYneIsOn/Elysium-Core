/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_REFLECTION_EMIT_FIELDBUILDER
#define ELYSIUM_CORE_REFLECTION_EMIT_FIELDBUILDER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_REFLECTION_FIELDINFO
#include "FieldInfo.hpp"
#endif

namespace Elysium::Core::Reflection::Emit
{
	class ELYSIUM_CORE_API FieldBuilder final : public FieldInfo
	{
		friend class TypeBuilder;
	public:
		~FieldBuilder();
	protected:
		FieldBuilder();
	};
}
#endif
