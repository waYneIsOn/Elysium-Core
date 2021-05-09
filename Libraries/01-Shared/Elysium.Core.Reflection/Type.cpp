#include "Type.hpp"

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

Elysium::Core::Reflection::Type::~Type()
{ }

const bool Elysium::Core::Reflection::Type::GetIsArray() const
{
	return _IsArray;
}
const bool Elysium::Core::Reflection::Type::GetIsEnum() const
{
	return _IsEnum;
}
const bool Elysium::Core::Reflection::Type::GetIsClass() const
{
	return _IsClass;
}

const Elysium::Core::StringView & Elysium::Core::Reflection::Type::GetFullName() const
{
	throw NotImplementedException(u8"const Elysium::Core::StringView & Elysium::Core::Reflection::Type::GetFullName() const");
}

bool Elysium::Core::Reflection::Type::operator==(const Type & Other) const
{
	return _HashCode == Other._HashCode;
}
bool Elysium::Core::Reflection::Type::operator!=(const Type & Other) const
{
	return _HashCode != Other._HashCode;
}
bool Elysium::Core::Reflection::Type::operator<(const Type & Other) const
{
	return _HashCode < Other._HashCode;
}
bool Elysium::Core::Reflection::Type::operator>(const Type & Other) const
{
	return _HashCode > Other._HashCode;
}
bool Elysium::Core::Reflection::Type::operator<=(const Type & Other) const
{
	return _HashCode <= Other._HashCode;
}
bool Elysium::Core::Reflection::Type::operator>=(const Type & Other) const
{
	return _HashCode >= Other._HashCode;
}

Elysium::Core::Reflection::Type::Type()
	: _HashCode(0), _IsArray(false), _IsEnum(false), _IsClass(false)
{ }
