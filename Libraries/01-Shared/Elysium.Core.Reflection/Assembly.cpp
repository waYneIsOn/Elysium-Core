#include "Assembly.hpp"

#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <windows.h>
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

//Elysium::Core::Collections::Generic::List<Elysium::Core::Reflection::Assembly> Elysium::Core::Reflection::Assembly::_RegisteredAssemblies = Elysium::Core::Collections::Generic::List<Elysium::Core::Reflection::Assembly>();

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

Elysium::Core::Reflection::Assembly & Elysium::Core::Reflection::Assembly::GetEntryAssembly()
{
	throw NotImplementedException();
	/*
	TCHAR Location[MAX_PATH + 1];
	GetModuleFileName(nullptr, Location, MAX_PATH);

	Assembly Bla = Assembly();
	return Bla;
	*/
}

Elysium::Core::Reflection::Assembly::Assembly()
{
}
