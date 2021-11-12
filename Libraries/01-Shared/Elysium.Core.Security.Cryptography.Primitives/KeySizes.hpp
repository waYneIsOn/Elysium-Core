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

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

namespace Elysium::Core::Security::Cryptography
{
	class ELYSIUM_CORE_SECURITY_API KeySizes final
	{
	public:
		KeySizes(Elysium::Core::uint32_t MinimumSize, Elysium::Core::uint32_t MaximumSize, Elysium::Core::uint32_t SkipSize);

		KeySizes(const KeySizes& Source) = delete;

		KeySizes(KeySizes&& Right) noexcept = delete;

		~KeySizes();
	public:
		KeySizes& operator=(const KeySizes& Source) = delete;

		KeySizes& operator=(KeySizes&& Right) noexcept = delete;
	public:
		const Elysium::Core::uint32_t GetMinimumSize() const;

		const Elysium::Core::uint32_t GetMaximumSize() const;

		const Elysium::Core::uint32_t GetSkipSize() const;
	private:
		const Elysium::Core::uint32_t _MinimumSize;
		const Elysium::Core::uint32_t _MaximumSize;
		const Elysium::Core::uint32_t _SkipSize;
	};
}
#endif
