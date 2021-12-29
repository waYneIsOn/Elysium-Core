#include "SystemException.hpp"

#ifndef ELYSIUM_CORE_SYSTEMSPECIFIC
#include "../Elysium.Core/SystemSpecific.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::SystemException::SystemException()
	: Elysium::Core::Exception(u8"SystemException"),
	_ErrorCode(SystemSpecific::GetLastErrorCode())
{ }

Elysium::Core::SystemException::SystemException(const char8_t* Message)
	: Elysium::Core::Exception(Message),
	_ErrorCode(SystemSpecific::GetLastErrorCode())
{ }

Elysium::Core::SystemException::SystemException(Utf8String&& Message)
	: Elysium::Core::Exception(Elysium::Core::Template::Functional::Move(Message)),
	_ErrorCode(SystemSpecific::GetLastErrorCode())
{ }

Elysium::Core::SystemException::~SystemException()
{ }

const Elysium::Core::uint32_t Elysium::Core::SystemException::GetErrorCode() const
{
	return _ErrorCode;
}
