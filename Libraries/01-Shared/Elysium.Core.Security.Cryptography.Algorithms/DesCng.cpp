#include "DesCng.hpp"

Elysium::Core::Security::Cryptography::Windows::DesCng::DesCng()
	: SymmetricAlgorithmCng(64, 64, 64, CipherMode::CBC, PaddingMode::PKCS7, BCRYPT_DES_ALGORITHM)
{ }

Elysium::Core::Security::Cryptography::Windows::DesCng::~DesCng()
{ }
