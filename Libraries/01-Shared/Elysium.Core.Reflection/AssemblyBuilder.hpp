/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_REFLECTION_EMIT_ASSEMBLYBUILDER
#define ELYSIUM_CORE_REFLECTION_EMIT_ASSEMBLYBUILDER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_REFLECTION_ASSEMBLY
#include "Assembly.hpp"
#endif

#ifndef ELYSIUM_CORE_REFLECTION_EMIT_MODULEBUILDER
#include "ModuleBuilder.hpp"
#endif

namespace Elysium::Core::Reflection::Emit
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
#endif
