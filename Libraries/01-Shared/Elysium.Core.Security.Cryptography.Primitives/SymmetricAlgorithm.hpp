/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_SYMMETRICALGORITHM
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_SYMMETRICALGORITHM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_KEYSIZES
#include "KeySizes.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Security::Cryptography
{
	class ELYSIUM_CORE_SECURITY_API SymmetricAlgorithm
	{
	public:
		SymmetricAlgorithm(const SymmetricAlgorithm& Source) = delete;
		SymmetricAlgorithm(SymmetricAlgorithm&& Right) noexcept = delete;
		~SymmetricAlgorithm();

		SymmetricAlgorithm& operator=(const SymmetricAlgorithm& Source) = delete;
		SymmetricAlgorithm& operator=(SymmetricAlgorithm&& Right) noexcept = delete;

		const virtual Elysium::Core::String GetKeyExchangeAlgorithm() const = 0;
		const virtual Elysium::Core::uint32_t GetKeySize() const;
		const virtual Collections::Template::Array<KeySizes>& GetLegalKeySizes() const;
		const virtual Elysium::Core::String GetSignatureAlgorithm() const = 0;
	protected:
		SymmetricAlgorithm(const Elysium::Core::uint32_t KeySizeValue, const Collections::Template::Array<KeySizes>& LegalKeySizesValue);

		Elysium::Core::uint32_t _KeySizeValue;
		Collections::Template::Array<KeySizes> _LegalKeySizesValue;
	};
}
#endif
