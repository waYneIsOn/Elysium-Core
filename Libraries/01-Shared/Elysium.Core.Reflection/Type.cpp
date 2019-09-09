#include "Type.hpp"

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

Elysium::Core::Reflection::Type::~Type()
{
}

bool Elysium::Core::Reflection::Type::GetIsArray()
{
	return _IsArray;
}
bool Elysium::Core::Reflection::Type::GetIsEnum()
{
	return _IsEnum;
}
bool Elysium::Core::Reflection::Type::GetIsClass()
{
	return _IsClass;
}

const Elysium::Core::StringView & Elysium::Core::Reflection::Type::GetFullName() const
{
	throw NotImplementedException(L"const Elysium::Core::StringView & Elysium::Core::Reflection::Type::GetFullName() const");
}

Elysium::Core::Reflection::Type::Type()
{
}
