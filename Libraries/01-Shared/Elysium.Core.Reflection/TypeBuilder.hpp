/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_REFLECTION_EMIT_TYPEBUILDER
#define ELYSIUM_CORE_REFLECTION_EMIT_TYPEBUILDER

#ifndef ELYSIUM_CORE_REFLECTION_TYPE
#include "Type.hpp"
#endif

#ifndef ELYSIUM_CORE_REFLECTION_EMIT_FIELDBUILDER
#include "FieldBuilder.hpp"
#endif

#ifndef ELYSIUM_CORE_REFLECTION_FIELDATTRIBUTES
#include "FieldAttributes.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Reflection
		{
			namespace Emit
			{
				class ELYSIUM_CORE_API TypeBuilder final : public Type
				{
					friend class AssemblyBuilder;
				public:
					~TypeBuilder();

					template<class T>
					FieldBuilder DefineField(const String& FieldName, const Type& Type, const FieldAttributes& Attributes);
				private:
					TypeBuilder();

					Assembly* _Assembly;
					size_t _HashCode;
				};

				template<class T>
				inline FieldBuilder Elysium::Core::Reflection::Emit::TypeBuilder::DefineField(const String & FieldName, const Type & Type, const FieldAttributes & Attributes)
				{
					FieldBuilder DefinedField = FieldBuilder();
					DefinedField._Name = FieldName;
					DefinedField._Address = T;

					return FieldBuilder();
				}
			}
		}
	}
}
#endif
