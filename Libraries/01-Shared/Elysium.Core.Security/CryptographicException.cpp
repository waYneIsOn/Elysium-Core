#include "CryptographicException.hpp"

Elysium::Core::Security::Cryptography::CryptographicException::CryptographicException()
	: Elysium::Core::Exception(u"CryptographicException")
{ }
Elysium::Core::Security::Cryptography::CryptographicException::CryptographicException(String && Message)
	: Elysium::Core::Exception(std::move(Message))
{ }
Elysium::Core::Security::Cryptography::CryptographicException::~CryptographicException()
{ }
