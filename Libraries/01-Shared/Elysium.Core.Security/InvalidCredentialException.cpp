#include "InvalidCredentialException.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Security::Authentication::InvalidCredentialException::InvalidCredentialException()
	: Elysium::Core::Security::Authentication::AuthenticationException(u8"InvalidCredentialException")
{ }
Elysium::Core::Security::Authentication::InvalidCredentialException::InvalidCredentialException(const char8_t* Message)
	: Elysium::Core::Security::Authentication::AuthenticationException(Message)
{ }
Elysium::Core::Security::Authentication::InvalidCredentialException::InvalidCredentialException(String && Message)
	: Elysium::Core::Security::Authentication::AuthenticationException(Elysium::Core::Template::Functional::Move(Message))
{ }
Elysium::Core::Security::Authentication::InvalidCredentialException::~InvalidCredentialException()
{ }
