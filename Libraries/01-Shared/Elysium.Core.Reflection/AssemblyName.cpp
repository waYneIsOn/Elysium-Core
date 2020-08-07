#include "AssemblyName.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::Reflection::AssemblyName::AssemblyName()
{
}
Elysium::Core::Reflection::AssemblyName::AssemblyName(const String & AssemblyName, const String& CodeBase, const Version& AssemblyVersion)
	: _Name(String(AssemblyName)), _CodeBase(String(CodeBase)), _Version(Version(AssemblyVersion))
{
}
Elysium::Core::Reflection::AssemblyName::AssemblyName(const AssemblyName & Source)
{
}
 Elysium::Core::Reflection::AssemblyName::AssemblyName(AssemblyName && Right) noexcept
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
		_Name = String(Source._Name);
		_CodeBase = String(Source._CodeBase);
		_Version = Version(Source._Version);
	}
	return *this;
}
Elysium::Core::Reflection::AssemblyName & Elysium::Core::Reflection::AssemblyName::operator=(AssemblyName && Right) noexcept
{
	if (this != &Right)
	{
		_Name = std::move(Right._Name);
		_CodeBase = std::move(Right._CodeBase);
		_Version = std::move(Right._Version);

		Right._Name = u8"";
		Right._CodeBase = u8"";
		Right._Version = Version();
	}
	return *this;
}

bool Elysium::Core::Reflection::AssemblyName::operator==(const AssemblyName & Other) const
{
	if (this == &Other)
	{
		return true;
	}

	return _CodeBase == Other._CodeBase && _Version == Other._Version;
}
bool Elysium::Core::Reflection::AssemblyName::operator!=(const AssemblyName & Other) const
{
	return _CodeBase != Other._CodeBase || _Version != Other._Version;
}
bool Elysium::Core::Reflection::AssemblyName::operator<(const AssemblyName & Other) const
{
	return _CodeBase == Other._CodeBase && _Version < Other._Version;
}
bool Elysium::Core::Reflection::AssemblyName::operator>(const AssemblyName & Other) const
{
	return _CodeBase == Other._CodeBase && _Version > Other._Version;
}
bool Elysium::Core::Reflection::AssemblyName::operator<=(const AssemblyName & Other) const
{
	if (this == &Other)
	{
		return true;
	}

	return _CodeBase == Other._CodeBase && _Version <= Other._Version;
}
bool Elysium::Core::Reflection::AssemblyName::operator>=(const AssemblyName & Other) const
{
	if (this == &Other)
	{
		return true;
	}

	return _CodeBase == Other._CodeBase && _Version >= Other._Version;
}

const Elysium::Core::String & Elysium::Core::Reflection::AssemblyName::GetCodeBase() const
{
	return _CodeBase;
}
const Elysium::Core::String & Elysium::Core::Reflection::AssemblyName::GetName() const
{
	return _Name;
}
const Elysium::Core::Version & Elysium::Core::Reflection::AssemblyName::GetVersion() const
{
	return _Version;
}
