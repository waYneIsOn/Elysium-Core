#include "Assembly.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

#ifndef _WINDOWS_
#include <windows.h>
#endif

Elysium::Core::Reflection::Assembly::Assembly(const Assembly & Source)
	: _AssemblyName(AssemblyName(Source._AssemblyName)), _Location(String(Source._Location))
{
}
Elysium::Core::Reflection::Assembly::Assembly(Assembly && Right)
	: _AssemblyName(Right._AssemblyName), _Location(Right._Location)
{
	*this = std::move(Right);
}
Elysium::Core::Reflection::Assembly::~Assembly()
{
}

Elysium::Core::Reflection::Assembly & Elysium::Core::Reflection::Assembly::operator=(const Assembly & Source)
{
	if (this != &Source)
	{
	}
	return *this;
}
Elysium::Core::Reflection::Assembly & Elysium::Core::Reflection::Assembly::operator=(Assembly && Right)
{
	if (this != &Right)
	{
	}
	return *this;
}

Elysium::Core::Reflection::Assembly Elysium::Core::Reflection::Assembly::GetEntryAssembly()
{
	TCHAR Location[MAX_PATH + 1];
	GetModuleFileName(nullptr, Location, MAX_PATH);
	return Assembly();
}

Elysium::Core::Reflection::Assembly::Assembly()
{
}
