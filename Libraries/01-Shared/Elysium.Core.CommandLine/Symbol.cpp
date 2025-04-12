#include "Symbol.hpp"

constexpr Elysium::Core::CommandLine::Symbol::Symbol(const char8_t* Name, const char8_t* Description)
	: _Name(Name), _Description(Description)
{ }

Elysium::Core::CommandLine::Symbol::~Symbol() noexcept
{ }

const Elysium::Core::Utf8String& Elysium::Core::CommandLine::Symbol::GetName() const noexcept
{
	return _Name;
}

const Elysium::Core::Utf8String& Elysium::Core::CommandLine::Symbol::GetDescription() const noexcept
{
	return _Description;
}