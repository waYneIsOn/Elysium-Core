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

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_KEYSIZES
#include "KeySizes.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Elysium.Core.Template/Vector.hpp"
#endif

namespace Elysium::Core::Security::Cryptography
{
	class ELYSIUM_CORE_SECURITY_API AsymmetricAlgorithm
	{
	protected:
		AsymmetricAlgorithm(const Elysium::Core::uint32_t KeySizeValue, const Elysium::Core::Template::Container::Vector<KeySizes>& LegalKeySizesValue);
	public:
		AsymmetricAlgorithm(const AsymmetricAlgorithm& Source) = delete;

		AsymmetricAlgorithm(AsymmetricAlgorithm&& Right) noexcept = delete;

		~AsymmetricAlgorithm();
	public:
		AsymmetricAlgorithm& operator=(const AsymmetricAlgorithm& Source) = delete;

		AsymmetricAlgorithm& operator=(AsymmetricAlgorithm&& Right) noexcept = delete;
	public:
		const virtual Elysium::Core::Utf8String GetKeyExchangeAlgorithm() const = 0;

		const virtual Elysium::Core::uint32_t GetKeySize() const;

		//const virtual Elysium::Core::Template::Container::Vector<KeySizes>& GetLegalKeySizes() const;

		const virtual Elysium::Core::Utf8String GetSignatureAlgorithm() const = 0;

		//void Clear();
	protected:
		Elysium::Core::uint32_t _KeySizeValue;
		//Elysium::Core::Template::Container::Vector<KeySizes> _LegalKeySizesValue;
	};
}
#endif
