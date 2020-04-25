#include "CryptographicException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::Security::Cryptography::CryptographicException::CryptographicException()
	: Elysium::Core::SystemException(u"CryptographicException")
{ }
Elysium::Core::Security::Cryptography::CryptographicException::CryptographicException(const char16_t * Message)
	: Elysium::Core::SystemException(Message)
{ }
Elysium::Core::Security::Cryptography::CryptographicException::CryptographicException(String && Message)
	: Elysium::Core::SystemException(std::move(Message))
{ }
Elysium::Core::Security::Cryptography::CryptographicException::~CryptographicException()
{ }
