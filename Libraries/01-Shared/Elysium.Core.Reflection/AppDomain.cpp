#include "AppDomain.hpp"

#ifndef ELYSIUM_CORE_REFLECTION_ASSEMBLY
#include "Assembly.hpp"
#endif

constexpr Elysium::Core::Reflection::AppDomain::AppDomain()
	: _RegisteredAssemblies()
{ }

constexpr Elysium::Core::Reflection::AppDomain::~AppDomain()
{ }

const Elysium::Core::Reflection::Container::VectorOfConstAssemblyPointer Elysium::Core::Reflection::AppDomain::GetAssemblies() const
{
	return _RegisteredAssemblies;
}

Elysium::Core::Reflection::AppDomain& Elysium::Core::Reflection::AppDomain::GetCurrentDomain()
{
	static Elysium::Core::Reflection::AppDomain CurrentDomain = Elysium::Core::Reflection::AppDomain();
	return CurrentDomain;
}

constexpr void Elysium::Core::Reflection::AppDomain::Add(const Elysium::Core::Reflection::Assembly& Assembly)
{
	_RegisteredAssemblies.PushBack(&Assembly);
}

constexpr void Elysium::Core::Reflection::AppDomain::Remove(const Elysium::Core::Reflection::Assembly& Assembly)
{
	_RegisteredAssemblies.Erase(&Assembly);
}
