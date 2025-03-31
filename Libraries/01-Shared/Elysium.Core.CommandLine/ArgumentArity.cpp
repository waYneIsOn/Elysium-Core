#include "ArgumentArity.hpp"

constexpr Elysium::Core::CommandLine::ArgumentArity::ArgumentArity(const Elysium::Core::Template::System::uint32_t MinimumNumberOfValues, const Elysium::Core::Template::System::uint32_t MaximumNumberOfValues)
	: _MinimumNumberOfValues(MinimumNumberOfValues), _MaximumNumberOfValues(MaximumNumberOfValues)
{ }
