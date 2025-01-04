#include "RandomNumberGenerator.hpp"

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef _INC_STDLIB
#include <stdlib.h>
#endif

Elysium::Core::Security::Cryptography::RandomNumberGenerator::RandomNumberGenerator()
{ }

Elysium::Core::Security::Cryptography::RandomNumberGenerator::~RandomNumberGenerator()
{ }

void Elysium::Core::Security::Cryptography::RandomNumberGenerator::GetBytes(Elysium::Core::Container::VectorOfByte& Data)
{	// adapted from https://stackoverflow.com/questions/2999075/generate-a-random-number-within-range/2999130#2999130
	static Elysium::Core::byte UpperLimit = 255;
	Elysium::Core::byte Divisor = RAND_MAX / (UpperLimit + 1);
	Elysium::Core::byte Result;

	for (Elysium::Core::size i = 0; i < Data.GetLength(); i++)
	{
		do
		{
			Result = rand() / Divisor;
		} while (Result > UpperLimit);

		Data[i] = Result;
	}
}
