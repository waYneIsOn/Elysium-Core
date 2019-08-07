#include "Type.hpp"

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

Elysium::Core::String Elysium::Core::Reflection::Type::GetNamespace()
{
	return _Namespace;
}

Elysium::Core::Reflection::Type::Type()
{
}
