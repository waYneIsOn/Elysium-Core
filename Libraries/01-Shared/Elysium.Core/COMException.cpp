#include "COMException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
Elysium::Core::Runtime::InteropServices::COMException::COMException()
	: ExternalException(u8"COMException")
{ }
Elysium::Core::Runtime::InteropServices::COMException::COMException(String && Message)
	: ExternalException(std::move(Message))
{ }
Elysium::Core::Runtime::InteropServices::COMException::COMException(String && Message, const int ErrorCode)
	: ExternalException(std::move(Message), ErrorCode)
{ }
Elysium::Core::Runtime::InteropServices::COMException::~COMException()
{ }
#endif
