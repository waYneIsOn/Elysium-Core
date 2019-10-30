#include "Module.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::Reflection::Module::Module(const Module & Source)
	: _Name(Elysium::Core::String(Source._Name))
{
}
Elysium::Core::Reflection::Module::Module(Module && Right) noexcept
	: _Name()
{
	*this = std::move(Right);
}
Elysium::Core::Reflection::Module::~Module()
{
}

Elysium::Core::Reflection::Module & Elysium::Core::Reflection::Module::operator=(const Module & Source)
{
	if (this != &Source)
	{
		_Name = Elysium::Core::String(Source._Name);
	}
	return *this;
}
Elysium::Core::Reflection::Module & Elysium::Core::Reflection::Module::operator=(Module && Right) noexcept
{
	if (this != &Right)
	{
		_Name = std::move(Right._Name);
	}
	return *this;
}

bool Elysium::Core::Reflection::Module::operator==(const Module & Other) const
{
	if (this == &Other)
	{
		return true;
	}

	return _Name == Other._Name;
}
bool Elysium::Core::Reflection::Module::operator!=(const Module & Other) const
{
	return _Name != Other._Name;
}
bool Elysium::Core::Reflection::Module::operator<(const Module & Other) const
{
	return _Name < Other._Name;
}
bool Elysium::Core::Reflection::Module::operator>(const Module & Other) const
{
	return _Name > Other._Name;
}
bool Elysium::Core::Reflection::Module::operator<=(const Module & Other) const
{
	if (this == &Other)
	{
		return true;
	}

	return _Name <= Other._Name;
}
bool Elysium::Core::Reflection::Module::operator>=(const Module & Other) const
{
	if (this == &Other)
	{
		return true;
	}

	return _Name >= Other._Name;
}

const Elysium::Core::String & Elysium::Core::Reflection::Module::GetName() const
{
	return _Name;
}

Elysium::Core::Reflection::Module::Module()
	: _Name()
{
}
