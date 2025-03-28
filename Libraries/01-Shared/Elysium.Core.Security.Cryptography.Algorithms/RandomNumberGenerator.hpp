/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_RANDOMNUMBERGENERATOR
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_RANDOMNUMBERGENERATOR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_CONTAINER_VECTOROFBYTE
#include "../Elysium.Core/VectorOfByte.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

namespace Elysium::Core::Security::Cryptography
{
	class ELYSIUM_CORE_SECURITY_API RandomNumberGenerator final
	{
	public:
		RandomNumberGenerator();

		RandomNumberGenerator(const RandomNumberGenerator& Source) = delete;

		RandomNumberGenerator(RandomNumberGenerator&& Right) noexcept = delete;

		~RandomNumberGenerator();
	public:
		RandomNumberGenerator& operator=(const RandomNumberGenerator& Source) = delete;

		RandomNumberGenerator& operator=(RandomNumberGenerator&& Right) noexcept = delete;
	public:
		void GetBytes(Elysium::Core::Container::VectorOfByte& Data);
	private:
	};
}
#endif
