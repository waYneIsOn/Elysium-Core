#include "AsymmetricAlgorithm.hpp"

Elysium::Core::Security::Cryptography::AsymmetricAlgorithm::AsymmetricAlgorithm(const Elysium::Core::uint32_t KeySizeValue, const Collections::Template::Array<KeySizes>& LegalKeySizesValue)
	: _KeySizeValue(KeySizeValue)
{ }

Elysium::Core::Security::Cryptography::AsymmetricAlgorithm::~AsymmetricAlgorithm()
{ }

const Elysium::Core::uint32_t Elysium::Core::Security::Cryptography::AsymmetricAlgorithm::GetKeySize() const
{
	return _KeySizeValue;
}

