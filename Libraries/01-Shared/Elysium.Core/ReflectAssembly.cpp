/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_REFLECTION_MACROS
#include "../Elysium.Core.Reflection/Macros.hpp"
#endif

#ifndef ELYSIUM_CORE_REFLECTION_ASSEMBLYNAME
#include "../Elysium.Core.Reflection/AssemblyName.hpp"
#endif

#ifndef ELYSIUM_CORE_REFLECTION_EMIT_ASSEMBLYBUILDER
#include "../Elysium.Core.Reflection/AssemblyBuilder.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

REFLECT
{
	/*
	Elysium::Core::Reflection::AssemblyName CoreAssemblyName = Elysium::Core::Reflection::AssemblyName(L"AssemblyName", L"Location", Elysium::Core::Version(0, 1));

	Elysium::Core::Reflection::Emit::AssemblyBuilder CoreAssemblyBuilder = Elysium::Core::Reflection::Emit::AssemblyBuilder();
	Elysium::Core::Reflection::Emit::ModuleBuilder GlobalModuleCore = CoreAssemblyBuilder.DefineDynamicModule(L"GlobalCoreModule");
	Elysium::Core::Reflection::Emit::TypeBuilder SizeTType = GlobalModuleCore.DefineType<size_t>(L"size_t", Elysium::Core::Reflection::TypeAttributes::Public);
	Elysium::Core::Reflection::Emit::TypeBuilder CharType = GlobalModuleCore.DefineType<size_t>(L"char", Elysium::Core::Reflection::TypeAttributes::Public);
	Elysium::Core::Reflection::Emit::TypeBuilder CharPointerType = GlobalModuleCore.DefineType<size_t>(L"char*", Elysium::Core::Reflection::TypeAttributes::Public);
	Elysium::Core::Reflection::Emit::TypeBuilder WCharType = GlobalModuleCore.DefineType<size_t>(L"wchar", Elysium::Core::Reflection::TypeAttributes::Public);
	Elysium::Core::Reflection::Emit::TypeBuilder WCharPointerType = GlobalModuleCore.DefineType<size_t>(L"wchar*", Elysium::Core::Reflection::TypeAttributes::Public);

	Elysium::Core::Reflection::Emit::TypeBuilder StringType = GlobalModuleCore.DefineType<Elysium::Core::String>(L"String", Elysium::Core::Reflection::TypeAttributes::Public);
	//StringType.DefineField<Elysium::Core::String::_Data>(L"Data", WCharPointerType, Elysium::Core::Reflection::FieldAttributes::Private);
	*/
};
