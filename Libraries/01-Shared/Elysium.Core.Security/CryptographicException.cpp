#include "CryptographicException.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Security::Cryptography::CryptographicException::CryptographicException()
	: Elysium::Core::SystemException(u8"CryptographicException")
{ }

Elysium::Core::Security::Cryptography::CryptographicException::CryptographicException(const char8_t* Message)
	: Elysium::Core::SystemException(Message)
{ }

Elysium::Core::Security::Cryptography::CryptographicException::CryptographicException(Elysium::Core::Utf8String&& Message)
	: Elysium::Core::SystemException(Elysium::Core::Template::Functional::Move(Message))
{ }

Elysium::Core::Security::Cryptography::CryptographicException::~CryptographicException()
{ }
