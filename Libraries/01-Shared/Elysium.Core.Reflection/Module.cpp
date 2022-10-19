#include "Module.hpp"

#ifndef ELYSIUM_CORE_REFLECTION_ASSEMBLY
#include "Assembly.hpp"
#endif

#ifndef ELYSIUM_CORE_REFLECTION_TYPE
#include "Type.hpp"
#endif

Elysium::Core::Reflection::Module::Module(const Assembly& Assembly, const Utf8String& Name)
	: _Assembly(Assembly), _Name(Name), _Types()
{
	((Elysium::Core::Reflection::Assembly&)_Assembly).Add(*this);
}

Elysium::Core::Reflection::Module::~Module()
{
	((Elysium::Core::Reflection::Assembly&)_Assembly).Remove(*this);
}

const bool Elysium::Core::Reflection::Module::operator==(const Module& Other) const
{
	return _Assembly == Other._Assembly && _Name == Other._Name;
}

const Elysium::Core::Reflection::Assembly& Elysium::Core::Reflection::Module::GetAssembly() const
{
	return _Assembly;
}

const Elysium::Core::Utf8String& Elysium::Core::Reflection::Module::GetName() const
{
	return _Name;
}

const Elysium::Core::Template::Container::Vector<const Elysium::Core::Reflection::Type*> Elysium::Core::Reflection::Module::GetTypes() const
{
	return _Types;
}

const Elysium::Core::size Elysium::Core::Reflection::Module::GetHashCode() const
{
	return _Name.GetHashCode();
}

void Elysium::Core::Reflection::Module::Add(const Elysium::Core::Reflection::Type& Type)
{
	_Types.PushBack(&Type);
}

void Elysium::Core::Reflection::Module::Remove(const Elysium::Core::Reflection::Type& Type)
{
	_Types.Erase(&Type);
}
