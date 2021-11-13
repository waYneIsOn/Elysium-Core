/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_DES
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_DES

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_KEYSIZES
#include "KeySizes.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_SYMMETRICALGORITHM
#include "SymmetricAlgorithm.hpp"
#endif

namespace Elysium::Core::Security::Cryptography
{
	class ELYSIUM_CORE_SECURITY_API Des final : public SymmetricAlgorithm
	{
	public:
		Des();

		Des(const Des& Source) = delete;

		Des(Des&& Right) noexcept = delete;

		virtual ~Des();
	public:
		Des& operator=(const Des& Source) = delete;

		Des& operator=(Des&& Right) noexcept = delete;
	private:
		inline static KeySizes _LegalBlockSizes[] = { KeySizes(64, 64, 0) };
		inline static KeySizes _LegalKeySizes[] = { KeySizes(64, 64, 0) };
	};
}
#endif
