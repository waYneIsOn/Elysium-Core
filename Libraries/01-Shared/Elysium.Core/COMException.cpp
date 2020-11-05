#include "COMException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
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
