#include "SystemException.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
#endif

Elysium::Core::SystemException::SystemException()
	: Elysium::Core::Exception(u8"SystemException"),
	_ErrorCode(GetLastError())
{ }
Elysium::Core::SystemException::SystemException(const char8_t* Message)
	: Elysium::Core::Exception(Message),
	_ErrorCode(GetLastError())
{ }
Elysium::Core::SystemException::SystemException(String && Message)
	: Elysium::Core::Exception(Elysium::Core::Template::Functional::Move(Message)),
	_ErrorCode(GetLastError())
{ }
Elysium::Core::SystemException::~SystemException()
{ }

const Elysium::Core::int32_t Elysium::Core::SystemException::GetErrorCode() const
{
	return _ErrorCode;
}
