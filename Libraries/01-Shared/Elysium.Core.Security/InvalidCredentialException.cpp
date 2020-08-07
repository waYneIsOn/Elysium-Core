#include "InvalidCredentialException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::Security::Authentication::InvalidCredentialException::InvalidCredentialException()
	: Elysium::Core::Security::Authentication::AuthenticationException(u8"InvalidCredentialException")
{ }
Elysium::Core::Security::Authentication::InvalidCredentialException::InvalidCredentialException(const char * Message)
	: Elysium::Core::Security::Authentication::AuthenticationException(Message)
{ }
Elysium::Core::Security::Authentication::InvalidCredentialException::InvalidCredentialException(String && Message)
	: Elysium::Core::Security::Authentication::AuthenticationException(std::move(Message))
{ }
Elysium::Core::Security::Authentication::InvalidCredentialException::~InvalidCredentialException()
{ }
