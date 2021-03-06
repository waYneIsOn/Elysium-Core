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

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "../Elysium.Core/Byte.hpp"
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

		RandomNumberGenerator& operator=(const RandomNumberGenerator& Source) = delete;
		RandomNumberGenerator& operator=(RandomNumberGenerator&& Right) noexcept = delete;

		void GetBytes(Elysium::Core::Collections::Template::Array<Elysium::Core::byte>& Data);
	private:
	};
}
#endif
