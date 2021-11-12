/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_SYMMETRICGORITHM
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_SYMMETRICGORITHM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_CIPHERMODE
#include "CipherMode.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_KEYSIZES
#include "KeySizes.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_PADDINGMODE
#include "PaddingMode.hpp"
#endif

namespace Elysium::Core::Security::Cryptography
{
	class ELYSIUM_CORE_SECURITY_API SymmetricAlgorithm
	{
	protected:
		SymmetricAlgorithm(const Elysium::Core::uint32_t BlockSize, const Elysium::Core::uint32_t KeySize, const Elysium::Core::uint32_t FeedbackSize,
			const CipherMode CipherMode, const PaddingMode PaddingMode);
	public:
		SymmetricAlgorithm(const SymmetricAlgorithm& Source) = delete;

		SymmetricAlgorithm(SymmetricAlgorithm&& Right) noexcept = delete;

		virtual ~SymmetricAlgorithm();
	public:
		SymmetricAlgorithm& operator=(const SymmetricAlgorithm& Source) = delete;

		SymmetricAlgorithm& operator=(SymmetricAlgorithm&& Right) noexcept = delete;
	public:
		const virtual Elysium::Core::uint32_t GetBlockSize() const;

		const virtual Elysium::Core::uint32_t GetKeySize() const;

		const virtual Elysium::Core::uint32_t GetFeedbackSize() const;

		//const virtual Elysium::Core::String GetKeyExchangeAlgorithm() const = 0;

		//const virtual Collections::Template::Array<KeySizes>& GetLegalKeySizes() const;

		//const virtual Elysium::Core::String GetSignatureAlgorithm() const = 0;
	public:

	private:
		Elysium::Core::uint32_t _BlockSize;
		Elysium::Core::uint32_t _KeySize;
		Elysium::Core::uint32_t _FeedbackSize;
		CipherMode _CipherMode;
		PaddingMode _PadingMode;
		//Collections::Template::Array<KeySizes> _LegalKeySizesValue;
	};
}
#endif
