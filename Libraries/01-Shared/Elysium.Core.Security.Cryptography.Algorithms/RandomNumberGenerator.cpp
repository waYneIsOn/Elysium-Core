#include "RandomNumberGenerator.hpp"

#ifndef _INC_STDLIB
#include <stdlib.h>
#endif

Elysium::Core::Security::Cryptography::RandomNumberGenerator::RandomNumberGenerator()
{ }
Elysium::Core::Security::Cryptography::RandomNumberGenerator::~RandomNumberGenerator()
{ }

void Elysium::Core::Security::Cryptography::RandomNumberGenerator::GetBytes(Elysium::Core::Collections::Template::Array<Elysium::Core::byte>& Data)
{
	for (Elysium::Core::size i = 0; i < Data.GetLength(); i++)
	{
		Data[i] = rand() % 256;
	}
}
