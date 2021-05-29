#include "Module.hpp"

#ifndef ELYSIUM_CORE_REFLECTION_ASSEMBLY
#include "Assembly.hpp"
#endif

Elysium::Core::Reflection::Module::Module(const Assembly& Assembly, const String& Name)
	: _Assembly(Assembly), _Name(Name)
{
	((Elysium::Core::Reflection::Assembly&)_Assembly).Add(*this);
}
Elysium::Core::Reflection::Module::~Module()
{
	((Elysium::Core::Reflection::Assembly&)_Assembly).Remove(*this);
}

const Elysium::Core::Reflection::Assembly& Elysium::Core::Reflection::Module::GetAssembly() const
{
	return _Assembly;
}

const Elysium::Core::String& Elysium::Core::Reflection::Module::GetName() const
{
	return _Name;
}

const Elysium::Core::Collections::Template::Array<const Elysium::Core::Reflection::Type*> Elysium::Core::Reflection::Module::GetTypes() const
{
	return Elysium::Core::Collections::Template::Array<const Elysium::Core::Reflection::Type*>(_Types);
}

void Elysium::Core::Reflection::Module::Add(const Elysium::Core::Reflection::Type& Type)
{
	_Types.Add(&Type);
}

void Elysium::Core::Reflection::Module::Remove(const Elysium::Core::Reflection::Type& Type)
{
	_Types.Remove(&Type);
}
