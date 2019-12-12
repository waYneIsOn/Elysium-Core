#include "HashAlgorithm.hpp"

Elysium::Core::Security::Cryptography::HashAlgorithm::~HashAlgorithm()
{
}

const bool Elysium::Core::Security::Cryptography::HashAlgorithm::GetCanReuseTransform() const
{
	return true;
}

Elysium::Core::Security::Cryptography::HashAlgorithm::HashAlgorithm()
	: _HashValue(Elysium::Core::Collections::Template::Array<Elysium::Core::byte>(2))
{
}
