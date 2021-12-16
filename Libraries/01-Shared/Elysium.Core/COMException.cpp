#include "COMException.hpp"

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Runtime::InteropServices::COMException::COMException()
	: ExternalException()
{ }

Elysium::Core::Runtime::InteropServices::COMException::COMException(const Elysium::Core::int32_t ErrorCode)
	: ExternalException(ErrorCode)
{ }

Elysium::Core::Runtime::InteropServices::COMException::~COMException()
{ }
#endif
