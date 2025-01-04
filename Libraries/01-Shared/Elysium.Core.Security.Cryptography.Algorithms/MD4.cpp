#include "MD4.hpp"

Elysium::Core::Security::Cryptography::MD4::MD4()
	: Elysium::Core::Security::Cryptography::HashAlgorithm::HashAlgorithm(128)
{ }
Elysium::Core::Security::Cryptography::MD4::~MD4()
{ }

void Elysium::Core::Security::Cryptography::MD4::Initialize()
{

}

void Elysium::Core::Security::Cryptography::MD4::HashCore(Elysium::Core::byte * Array, const Elysium::Core::size Length)
{
}

const Elysium::Core::Container::VectorOfByte Elysium::Core::Security::Cryptography::MD4::HashFinal()
{
	return Elysium::Core::Container::VectorOfByte(0);
}
