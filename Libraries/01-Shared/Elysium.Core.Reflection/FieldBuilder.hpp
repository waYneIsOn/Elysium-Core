/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_REFLECTION_EMIT_FIELDBUILDER
#define ELYSIUM_CORE_REFLECTION_EMIT_FIELDBUILDER

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
