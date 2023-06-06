#include "Type.hpp"

constexpr Elysium::Core::Reflection::Type::Type(const Module& Module, const Elysium::Core::uint64_t Id, const Elysium::Core::Utf8String& Name)
	: _Module(Module), _Id(Id), _Name(Name)
{
	((Elysium::Core::Reflection::Module&)_Module).Add(*this);
}

constexpr Elysium::Core::Reflection::Type::~Type()
{
	((Elysium::Core::Reflection::Module&)_Module).Remove(*this);
}

constexpr const Elysium::Core::Utf8String Elysium::Core::Reflection::Type::GetFullName() const
{	// ToDo: _Module.GetName() + "::" + _Name;
	return _Name;
}

constexpr const Elysium::Core::Utf8String& Elysium::Core::Reflection::Type::GetName() const
{
	return _Name;
}
