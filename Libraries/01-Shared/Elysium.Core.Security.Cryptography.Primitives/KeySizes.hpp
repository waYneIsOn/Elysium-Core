/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_KEYSIZES
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_KEYSIZES

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Security::Cryptography
{
	class ELYSIUM_CORE_SECURITY_API KeySizes final
	{
		friend class Collections::Template::Array<KeySizes>;
	public:
		KeySizes(Elysium::Core::uint32_t MinimumSize, Elysium::Core::uint32_t MaximumSize, Elysium::Core::uint32_t SkipSize);
		KeySizes(const KeySizes& Source);
		KeySizes(KeySizes&& Right) noexcept;
		~KeySizes();

		KeySizes& operator=(const KeySizes& Source);
		KeySizes& operator=(KeySizes&& Right) noexcept;

		const Elysium::Core::uint32_t GetMinimumSize() const;
		const Elysium::Core::uint32_t GetMaximumSize() const;
		const Elysium::Core::uint32_t GetSkipSize() const;
	private:
		KeySizes();

		Elysium::Core::uint32_t _MinimumSize;
		Elysium::Core::uint32_t _MaximumSize;
		Elysium::Core::uint32_t _SkipSize;
	};
}
#endif
