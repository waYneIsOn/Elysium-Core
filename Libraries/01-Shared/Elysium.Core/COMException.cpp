#include "COMException.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
Elysium::Core::Runtime::InteropServices::COMException::COMException()
	: ExternalException()
{ }
Elysium::Core::Runtime::InteropServices::COMException::COMException(const Elysium::Core::int32_t ErrorCode)
	: ExternalException(ErrorCode)
{ }
Elysium::Core::Runtime::InteropServices::COMException::~COMException()
{ }
#endif
