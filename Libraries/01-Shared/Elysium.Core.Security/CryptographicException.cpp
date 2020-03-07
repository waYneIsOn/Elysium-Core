#include "CryptographicException.hpp"

Elysium::Core::Security::Cryptography::CryptographicException::CryptographicException()
	: Elysium::Core::SystemException(u"CryptographicException")
{ }
Elysium::Core::Security::Cryptography::CryptographicException::CryptographicException(String && Message)
	: Elysium::Core::SystemException(std::move(Message))
{ }
Elysium::Core::Security::Cryptography::CryptographicException::~CryptographicException()
{ }
