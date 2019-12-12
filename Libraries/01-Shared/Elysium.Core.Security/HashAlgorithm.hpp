/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_HASHALGORITHM
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_HASHALGORITHM

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "../Elysium.Core/Byte.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Security
		{
			namespace Cryptography
			{
				class ELYSIUM_CORE_API HashAlgorithm
				{
				public:
					HashAlgorithm(const HashAlgorithm& Source) = delete;
					HashAlgorithm(HashAlgorithm&& Right) noexcept = delete;
					~HashAlgorithm();

					HashAlgorithm& operator=(const HashAlgorithm& Source) = delete;
					HashAlgorithm& operator=(HashAlgorithm&& Right) noexcept = delete;

					virtual const bool GetCanReuseTransform() const;
				protected:
					HashAlgorithm();

					int32_t _HashSizeValue;
					Elysium::Core::Collections::Template::Array<Elysium::Core::byte> _HashValue;
					int32_t _State;
				};
			}
		}
	}
}
#endif
