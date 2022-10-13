#include "AppDomain.hpp"

#ifndef ELYSIUM_CORE_REFLECTION_ASSEMBLY
#include "Assembly.hpp"
#endif

Elysium::Core::Reflection::AppDomain Elysium::Core::Reflection::AppDomain::_CurrentDomain = Elysium::Core::Reflection::AppDomain();

Elysium::Core::Reflection::AppDomain::AppDomain()
	: _RegisteredAssemblies()
{ }

Elysium::Core::Reflection::AppDomain::~AppDomain()
{ }

const Elysium::Core::Collections::Template::Array<const Elysium::Core::Reflection::Assembly*> Elysium::Core::Reflection::AppDomain::GetAssemblies() const
{
	return Elysium::Core::Collections::Template::Array<const Elysium::Core::Reflection::Assembly*>(_RegisteredAssemblies);
}

Elysium::Core::Reflection::AppDomain& Elysium::Core::Reflection::AppDomain::GetCurrentDomain()
{
	return _CurrentDomain;
}

void Elysium::Core::Reflection::AppDomain::Add(const Elysium::Core::Reflection::Assembly& Assembly)
{
	_RegisteredAssemblies.PushBack(&Assembly);
}

void Elysium::Core::Reflection::AppDomain::Remove(const Elysium::Core::Reflection::Assembly& Assembly)
{
	_RegisteredAssemblies.Erase(&Assembly);
}
