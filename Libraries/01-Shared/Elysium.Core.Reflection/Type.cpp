#include "Type.hpp"

Elysium::Core::Reflection::Type::Type(const Module& Module, const Elysium::Core::uint64_t Id, const String& Name)
	: _Module(Module), _Id(Id), _Name(Name)
{
	((Elysium::Core::Reflection::Module&)_Module).Add(*this);
}

Elysium::Core::Reflection::Type::~Type()
{
	((Elysium::Core::Reflection::Module&)_Module).Remove(*this);
}

const Elysium::Core::String Elysium::Core::Reflection::Type::GetFullName() const
{	// ToDo: _Module.GetName() + "::" + _Name;
	throw 1;
}

const Elysium::Core::String& Elysium::Core::Reflection::Type::GetName() const
{
	return _Name;
}
