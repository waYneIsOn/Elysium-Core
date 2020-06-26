#include "AsymmetricAlgorithm.hpp"

Elysium::Core::Security::Cryptography::AsymmetricAlgorithm::~AsymmetricAlgorithm()
{ }

const Elysium::Core::uint32_t Elysium::Core::Security::Cryptography::AsymmetricAlgorithm::GetKeySize() const
{
	return _KeySizeValue;
}
const Elysium::Core::Collections::Template::Array<Elysium::Core::Security::Cryptography::KeySizes>& Elysium::Core::Security::Cryptography::AsymmetricAlgorithm::GetLegalKeySizes() const
{
	return _LegalKeySizesValue;
}

Elysium::Core::Security::Cryptography::AsymmetricAlgorithm::AsymmetricAlgorithm(const Elysium::Core::uint32_t KeySizeValue, const Collections::Template::Array<KeySizes> & LegalKeySizesValue)
	: _KeySizeValue(KeySizeValue), _LegalKeySizesValue(LegalKeySizesValue)
{ }
