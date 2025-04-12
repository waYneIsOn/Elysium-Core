#include "ArgumentArity.hpp"

constexpr Elysium::Core::CommandLine::ArgumentArity::ArgumentArity(const Elysium::Core::Template::System::uint32_t MinimumNumberOfValues, const Elysium::Core::Template::System::uint32_t MaximumNumberOfValues)
	: _MinimumNumberOfValues(MinimumNumberOfValues), _MaximumNumberOfValues(MaximumNumberOfValues)
{ }

Elysium::Core::Template::System::uint32_t Elysium::Core::CommandLine::ArgumentArity::GetMinimumNumberOfValues()
{
	return _MinimumNumberOfValues;
}

Elysium::Core::Template::System::uint32_t Elysium::Core::CommandLine::ArgumentArity::GetMaximumNumberOfValues()
{
	return _MaximumNumberOfValues;
}

void Elysium::Core::CommandLine::ArgumentArity::SetMinimumNumberOfValues(const Elysium::Core::Template::System::uint32_t Value)
{
	_MinimumNumberOfValues = Value;
}

void Elysium::Core::CommandLine::ArgumentArity::SetMaximumNumberOfValues(const Elysium::Core::Template::System::uint32_t Value)
{
	_MaximumNumberOfValues = Value;
}