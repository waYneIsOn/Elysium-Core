/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASYMMETRICALGORITHM
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASYMMETRICALGORITHM

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
	class ELYSIUM_CORE_SECURITY_API AsymmetricAlgorithm
	{
	public:
		AsymmetricAlgorithm(const AsymmetricAlgorithm& Source) = delete;
		AsymmetricAlgorithm(AsymmetricAlgorithm&& Right) noexcept = delete;
		~AsymmetricAlgorithm();

		AsymmetricAlgorithm& operator=(const AsymmetricAlgorithm& Source) = delete;
		AsymmetricAlgorithm& operator=(AsymmetricAlgorithm&& Right) noexcept = delete;

		const virtual Elysium::Core::String GetKeyExchangeAlgorithm() const = 0;
		const virtual Elysium::Core::uint32_t GetKeySize() const;
		const virtual Collections::Template::Array<KeySizes>& GetLegalKeySizes() const;
		const virtual Elysium::Core::String GetSignatureAlgorithm () const = 0;

		//void Clear();
	protected:
		AsymmetricAlgorithm(const Elysium::Core::uint32_t KeySizeValue, const Collections::Template::Array<KeySizes>& LegalKeySizesValue);

		Elysium::Core::uint32_t _KeySizeValue;
		Collections::Template::Array<KeySizes> _LegalKeySizesValue;
	};
}
#endif
