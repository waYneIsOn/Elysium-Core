#include "AssemblyName.hpp"

constexpr Elysium::Core::Reflection::AssemblyName::AssemblyName(const Utf8String& AssemblyName, const Version& AssemblyVersion)
	: _Name(AssemblyName), _Version(AssemblyVersion)
{ }

constexpr Elysium::Core::Reflection::AssemblyName::AssemblyName(const AssemblyName & Source)
	: _Name(Source._Name), _Version(Source._Version)
{ }

constexpr Elysium::Core::Reflection::AssemblyName::~AssemblyName()
{ }

constexpr Elysium::Core::Reflection::AssemblyName& Elysium::Core::Reflection::AssemblyName::operator=(const AssemblyName& Source)
{
	if (this != &Source)
	{
		_Name = Source._Name;
		_Version = Source._Version;
	}
	return *this;
}

bool Elysium::Core::Reflection::AssemblyName::operator==(const AssemblyName & Other) const
{
	if (this == &Other)
	{
		return true;
	}

	return _Name == Other._Name && _Version == Other._Version;
}

bool Elysium::Core::Reflection::AssemblyName::operator!=(const AssemblyName & Other) const
{
	return _Name != Other._Name || _Version != Other._Version;
}

bool Elysium::Core::Reflection::AssemblyName::operator<(const AssemblyName & Other) const
{
	return _Name == Other._Name && _Version < Other._Version;
}

bool Elysium::Core::Reflection::AssemblyName::operator>(const AssemblyName & Other) const
{
	return _Name == Other._Name && _Version > Other._Version;
}

bool Elysium::Core::Reflection::AssemblyName::operator<=(const AssemblyName & Other) const
{
	if (this == &Other)
	{
		return true;
	}

	return _Name == Other._Name && _Version <= Other._Version;
}

bool Elysium::Core::Reflection::AssemblyName::operator>=(const AssemblyName & Other) const
{
	if (this == &Other)
	{
		return true;
	}

	return _Name == Other._Name && _Version >= Other._Version;
}

const Elysium::Core::Utf8String& Elysium::Core::Reflection::AssemblyName::GetName() const
{
	return _Name;
}

const Elysium::Core::Version & Elysium::Core::Reflection::AssemblyName::GetVersion() const
{
	return _Version;
}

