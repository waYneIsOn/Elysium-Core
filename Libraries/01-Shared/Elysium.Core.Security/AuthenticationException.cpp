#include "AuthenticationException.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Security::Authentication::AuthenticationException::AuthenticationException()
	: Elysium::Core::SystemException(u8"AuthenticationException")
{ }

Elysium::Core::Security::Authentication::AuthenticationException::AuthenticationException(const char8_t * Message)
	: Elysium::Core::SystemException(Message)
{ }

Elysium::Core::Security::Authentication::AuthenticationException::AuthenticationException(Utf8String&& Message)
	: Elysium::Core::SystemException(Elysium::Core::Template::Functional::Move(Message))
{ }

Elysium::Core::Security::Authentication::AuthenticationException::~AuthenticationException()
{ }
