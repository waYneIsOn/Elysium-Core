#include "AuthenticationException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::Security::Authentication::AuthenticationException::AuthenticationException()
	: Elysium::Core::SystemException(u8"AuthenticationException")
{ }
Elysium::Core::Security::Authentication::AuthenticationException::AuthenticationException(const char8_t * Message)
	: Elysium::Core::SystemException(Message)
{ }
Elysium::Core::Security::Authentication::AuthenticationException::AuthenticationException(String && Message)
	: Elysium::Core::SystemException(std::move(Message))
{ }
Elysium::Core::Security::Authentication::AuthenticationException::~AuthenticationException()
{ }
