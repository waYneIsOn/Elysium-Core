#include "SystemException.hpp"

#ifndef _WINDOWS_
#include <Windows.h>
#endif

Elysium::Core::SystemException::SystemException()
	: Elysium::Core::Exception(u"SystemException"),
	_HResult(GetLastError())
{ }
Elysium::Core::SystemException::SystemException(String && Message)
	: Elysium::Core::Exception(std::move(Message)),
	_HResult(GetLastError())
{ }
Elysium::Core::SystemException::~SystemException()
{ }
