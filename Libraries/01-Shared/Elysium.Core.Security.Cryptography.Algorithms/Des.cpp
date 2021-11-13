#include "Des.hpp"

Elysium::Core::Security::Cryptography::Des::Des()
	: SymmetricAlgorithm(64, 64, 64, CipherMode::CBC, PaddingMode::PKCS7)
{ }

Elysium::Core::Security::Cryptography::Des::~Des()
{ }
