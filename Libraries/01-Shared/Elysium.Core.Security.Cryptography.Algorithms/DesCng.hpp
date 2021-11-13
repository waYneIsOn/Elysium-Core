/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_WINDOWS_DESCNG
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_WINDOWS_DESCNG

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_WINDOWS_SYMMETRICALGORITHMCNG
#include "SymmetricAlgorithmCng.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
namespace Elysium::Core::Security::Cryptography::Windows
{
	class ELYSIUM_CORE_SECURITY_API DesCng final : public SymmetricAlgorithmCng
	{
	public:
		DesCng();

		DesCng(const DesCng& Source) = delete;

		DesCng(DesCng&& Right) noexcept = delete;

		virtual ~DesCng();
	public:
		DesCng& operator=(const DesCng& Source) = delete;

		DesCng& operator=(DesCng&& Right) noexcept = delete;
	private:
		inline static KeySizes _LegalBlockSizes[] = { KeySizes(64, 64, 0) };
		inline static KeySizes _LegalKeySizes[] = { KeySizes(64, 64, 0) };
	};
}
#endif
#endif
