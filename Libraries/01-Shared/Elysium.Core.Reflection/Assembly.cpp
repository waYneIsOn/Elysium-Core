#include "Assembly.hpp"

#ifndef ELYSIUM_CORE_REFLECTION_APPDOMAIN
#include "AppDomain.hpp"
#endif

Elysium::Core::Reflection::Assembly::Assembly(const Elysium::Core::Reflection::AssemblyName& AssemblyName)
	: _AssemblyName(AssemblyName)
{ }
Elysium::Core::Reflection::Assembly::~Assembly()
{ }

bool Elysium::Core::Reflection::Assembly::operator==(const Assembly & Other) const
{
	return _AssemblyName == Other._AssemblyName;
}
bool Elysium::Core::Reflection::Assembly::operator!=(const Assembly & Other) const
{
	return _AssemblyName != Other._AssemblyName;
}
bool Elysium::Core::Reflection::Assembly::operator<(const Assembly & Other) const
{
	return _AssemblyName < Other._AssemblyName;
}
bool Elysium::Core::Reflection::Assembly::operator>(const Assembly & Other) const
{
	return _AssemblyName > Other._AssemblyName;
}
bool Elysium::Core::Reflection::Assembly::operator<=(const Assembly & Other) const
{
	return _AssemblyName <= Other._AssemblyName;
}
bool Elysium::Core::Reflection::Assembly::operator>=(const Assembly & Other) const
{
	return _AssemblyName >= Other._AssemblyName;
}

const Elysium::Core::String& Elysium::Core::Reflection::Assembly::GetFullName() const
{
	return _AssemblyName.GetName();
}
