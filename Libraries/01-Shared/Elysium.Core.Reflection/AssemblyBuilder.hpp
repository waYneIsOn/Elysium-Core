/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_REFLECTION_EMIT_ASSEMBLYBUILDER
#define ELYSIUM_CORE_REFLECTION_EMIT_ASSEMBLYBUILDER

#ifndef ELYSIUM_CORE_REFLECTION_ASSEMBLY
#include "Assembly.hpp"
#endif

#ifndef ELYSIUM_CORE_REFLECTION_EMIT_MODULEBUILDER
#include "ModuleBuilder.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Reflection
		{
			namespace Emit
			{
				class ELYSIUM_CORE_API AssemblyBuilder final : public Assembly
				{
				public:
					AssemblyBuilder();
					virtual ~AssemblyBuilder();

					ModuleBuilder DefineDynamicModule(const String& Name);
					ModuleBuilder DefineDynamicModule(const String& Name, const String& FileName, bool EmitSymbolInfo);
				};
			}
		}
	}
}
#endif