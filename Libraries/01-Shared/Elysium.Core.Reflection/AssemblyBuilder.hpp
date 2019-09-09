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

#ifndef ELYSIUM_CORE_REFLECTION_EMIT_TYPEBUILDER
#include "TypeBuilder.hpp"
#endif

#ifndef ELYSIUM_CORE_REFLECTION_TYPEATTRIBUTES
#include "TypeAttributes.hpp"
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
					~AssemblyBuilder();

					template<class T>
					TypeBuilder DefineType(const String& Name, const TypeAttributes& Attributes);
				};

				template<class T>
				inline TypeBuilder AssemblyBuilder::DefineType(const String & Name, const TypeAttributes & Attributes)
				{
					TypeBuilder DefinedType = TypeBuilder();
					DefinedType._Assembly = this;
					DefinedType._Name = Name;
					DefinedType._HashCode = typeid(T).hash_code();

					return DefinedType;
				}
			}
		}
	}
}
#endif
