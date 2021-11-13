#include "StackTrace.hpp"

Elysium::Core::Diagnostics::StackTrace::StackTrace()
	: _FrameCount(0)
{ }

Elysium::Core::Diagnostics::StackTrace::~StackTrace()
{ }

const Elysium::Core::size Elysium::Core::Diagnostics::StackTrace::GetFrameCount() const
{
	return _FrameCount;
}
