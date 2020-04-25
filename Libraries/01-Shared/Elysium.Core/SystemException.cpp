#include "SystemException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
#endif

Elysium::Core::SystemException::SystemException()
	: Elysium::Core::Exception(u"SystemException"),
	_HResult(GetLastError())
{ }
Elysium::Core::SystemException::SystemException(const char16_t * Message)
	: Elysium::Core::Exception(Message),
	_HResult(GetLastError())
{ }
Elysium::Core::SystemException::SystemException(String && Message)
	: Elysium::Core::Exception(std::move(Message)),
	_HResult(GetLastError())
{ }
Elysium::Core::SystemException::~SystemException()
{ }
