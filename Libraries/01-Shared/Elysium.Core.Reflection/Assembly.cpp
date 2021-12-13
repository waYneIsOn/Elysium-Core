#include "Assembly.hpp"

#ifndef ELYSIUM_CORE_REFLECTION_APPDOMAIN
#include "AppDomain.hpp"
#endif

#ifndef ELYSIUM_CORE_REFLECTION_MODULE
#include "Module.hpp"
#endif

Elysium::Core::Reflection::Assembly::Assembly(const Elysium::Core::Reflection::AssemblyName& AssemblyName)
	: _AssemblyName(AssemblyName), _Modules()
{
	AppDomain::GetCurrentDomain().Add(*this);
}

Elysium::Core::Reflection::Assembly::~Assembly()
{
	AppDomain::GetCurrentDomain().Remove(*this);
}

bool Elysium::Core::Reflection::Assembly::operator==(const Assembly& Other) const
{
	return _AssemblyName == Other._AssemblyName;
}

bool Elysium::Core::Reflection::Assembly::operator!=(const Assembly& Other) const
{
	return _AssemblyName != Other._AssemblyName;
}

bool Elysium::Core::Reflection::Assembly::operator<(const Assembly& Other) const
{
	return _AssemblyName < Other._AssemblyName;
}

bool Elysium::Core::Reflection::Assembly::operator>(const Assembly& Other) const
{
	return _AssemblyName > Other._AssemblyName;
}

bool Elysium::Core::Reflection::Assembly::operator<=(const Assembly& Other) const
{
	return _AssemblyName <= Other._AssemblyName;
}

bool Elysium::Core::Reflection::Assembly::operator>=(const Assembly& Other) const
{
	return _AssemblyName >= Other._AssemblyName;
}

const Elysium::Core::String& Elysium::Core::Reflection::Assembly::GetFullName() const
{
	return _AssemblyName.GetName();
}

const Elysium::Core::Collections::Template::Array<const Elysium::Core::Reflection::Module*> Elysium::Core::Reflection::Assembly::GetModules() const
{
	return Elysium::Core::Collections::Template::Array<const Elysium::Core::Reflection::Module*>(_Modules);
}

void Elysium::Core::Reflection::Assembly::Add(Elysium::Core::Reflection::Module& Module)
{
	_Modules.Add(&Module);
}

void Elysium::Core::Reflection::Assembly::Remove(Elysium::Core::Reflection::Module& Module)
{
	_Modules.Remove(&Module);
}
