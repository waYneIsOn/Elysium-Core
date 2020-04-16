/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_REFLECTION_EMIT_MODULEBUILDER
#define ELYSIUM_CORE_REFLECTION_EMIT_MODULEBUILDER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_REFLECTION_MODULE
#include "Module.hpp"
#endif

#ifndef ELYSIUM_CORE_REFLECTION_EMIT_TYPEBUILDER
#include "TypeBuilder.hpp"
#endif

#ifndef ELYSIUM_CORE_REFLECTION_TYPEATTRIBUTES
#include "TypeAttributes.hpp"
#endif

#ifndef _TYPEINFO_
#include <typeinfo>
#endif

namespace Elysium::Core::Reflection::Emit
{
	class ELYSIUM_CORE_API ModuleBuilder final : public Module
	{
		friend class AssemblyBuilder;
	public:
		virtual ~ModuleBuilder();

		template<class T>
		TypeBuilder DefineType(const String& Name, const TypeAttributes& Attributes);
	private:
		ModuleBuilder();
	};

	template<class T>
	inline TypeBuilder ModuleBuilder::DefineType(const String & Name, const TypeAttributes & Attributes)
	{
		TypeBuilder DefinedType = TypeBuilder();
		//DefinedType._Assembly = this;
		DefinedType._Name = Name;
		DefinedType._HashCode = typeid(T).hash_code();

		return DefinedType;
	}
}
#endif
