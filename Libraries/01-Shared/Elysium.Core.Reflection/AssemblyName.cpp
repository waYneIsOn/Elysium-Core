#include "AssemblyName.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::Reflection::AssemblyName::AssemblyName()
{
}
Elysium::Core::Reflection::AssemblyName::AssemblyName(const String & AssemblyName)
	: _AssemblyName(String(AssemblyName))
{
}
Elysium::Core::Reflection::AssemblyName::AssemblyName(const AssemblyName & Source)
{
}
Elysium::Core::Reflection::AssemblyName::AssemblyName(AssemblyName && Right)
{
	*this = std::move(Right);
}
Elysium::Core::Reflection::AssemblyName::~AssemblyName()
{
}

Elysium::Core::Reflection::AssemblyName & Elysium::Core::Reflection::AssemblyName::operator=(const AssemblyName & Source)
{
	if (this != &Source)
	{
	}
	return *this;
}
Elysium::Core::Reflection::AssemblyName & Elysium::Core::Reflection::AssemblyName::operator=(AssemblyName && Right)
{
	if (this != &Right)
	{
	}
	return *this;
}
