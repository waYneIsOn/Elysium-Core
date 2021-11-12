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

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_SYMMETRICGORITHM
#include "SymmetricAlgorithm.hpp"
#endif

namespace Elysium::Core::Security::Cryptography
{
	class ELYSIUM_CORE_SECURITY_API DES final : public SymmetricAlgorithm
	{
	public:
		DES();

		DES(const DES& Source) = delete;

		DES(DES&& Right) noexcept = delete;

		virtual ~DES();
	public:
		DES& operator=(const DES& Source) = delete;

		DES& operator=(DES&& Right) noexcept = delete;
	public:
		void Test();
	private:
		inline static KeySizes _LegalBlockSizes[] = { KeySizes(64, 64, 0) };
		inline static KeySizes _LegalKeySizes[] = { KeySizes(64, 64, 0) };
	};
}
#endif
