#include "AssemblyBuilder.hpp"

Elysium::Core::Reflection::Emit::AssemblyBuilder::AssemblyBuilder()
	: Elysium::Core::Reflection::Assembly::Assembly()
{
	//_RegisteredAssemblies.Add(this);
}
Elysium::Core::Reflection::Emit::AssemblyBuilder::~AssemblyBuilder()
{
}

Elysium::Core::Reflection::Emit::ModuleBuilder Elysium::Core::Reflection::Emit::AssemblyBuilder::DefineDynamicModule(const String & Name)
{
	Elysium::Core::Reflection::Emit::ModuleBuilder ModuleBuilder = Elysium::Core::Reflection::Emit::ModuleBuilder();
	ModuleBuilder._Name = Name;

	return ModuleBuilder;
}
Elysium::Core::Reflection::Emit::ModuleBuilder Elysium::Core::Reflection::Emit::AssemblyBuilder::DefineDynamicModule(const String & Name, const String & FileName, bool EmitSymbolInfo)
{
	Elysium::Core::Reflection::Emit::ModuleBuilder ModuleBuilder = Elysium::Core::Reflection::Emit::ModuleBuilder();
	ModuleBuilder._Name = Name;

	return ModuleBuilder;
}
