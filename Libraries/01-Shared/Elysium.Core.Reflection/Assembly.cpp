#include "Assembly.hpp"

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
/*
const Elysium::Core::Reflection::Assembly & Elysium::Core::Reflection::Assembly::GetEntryAssembly()
{
	throw 1;
	TCHAR Location[MAX_PATH + 1];
	GetModuleFileName(nullptr, Location, MAX_PATH);

	Assembly Bla = Assembly();
	return Bla;
}
*/
