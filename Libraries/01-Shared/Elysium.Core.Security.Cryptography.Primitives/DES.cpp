#include "DES.hpp"

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_INTERNAL_WINCNG
#include "WinCNG.hpp"
#endif

Elysium::Core::Security::Cryptography::DES::DES()
	: SymmetricAlgorithm(64, 64, 64, CipherMode::CBC, PaddingMode::PKCS7)
{ }

Elysium::Core::Security::Cryptography::DES::~DES()
{ }

void Elysium::Core::Security::Cryptography::DES::Test()
{
	Internal::WinCNG::Test();
}
