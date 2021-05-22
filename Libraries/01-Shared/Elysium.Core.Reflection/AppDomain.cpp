#include "AppDomain.hpp"

void Elysium::Core::Reflection::AppDomain::Add(const Elysium::Core::Reflection::Assembly& Assembly)
{
	_RegisteredAssemblies.Add(&Assembly);
}

const Elysium::Core::Collections::Template::Array<const Elysium::Core::Reflection::Assembly*> Elysium::Core::Reflection::AppDomain::GetAssemblies()
{
	return Elysium::Core::Collections::Template::Array<const Elysium::Core::Reflection::Assembly*>(_RegisteredAssemblies);
}
