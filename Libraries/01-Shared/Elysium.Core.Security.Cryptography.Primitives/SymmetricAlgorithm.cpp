#include "SymmetricAlgorithm.hpp"

Elysium::Core::Security::Cryptography::SymmetricAlgorithm::~SymmetricAlgorithm()
{ }

const Elysium::Core::uint32_t Elysium::Core::Security::Cryptography::SymmetricAlgorithm::GetKeySize() const
{
	return _KeySizeValue;
}
const Elysium::Core::Collections::Template::Array<Elysium::Core::Security::Cryptography::KeySizes>& Elysium::Core::Security::Cryptography::SymmetricAlgorithm::GetLegalKeySizes() const
{
	return _LegalKeySizesValue;
}

Elysium::Core::Security::Cryptography::SymmetricAlgorithm::SymmetricAlgorithm(const Elysium::Core::uint32_t KeySizeValue, const Collections::Template::Array<KeySizes>& LegalKeySizesValue)
	: _KeySizeValue(KeySizeValue), _LegalKeySizesValue(LegalKeySizesValue)
{ }
