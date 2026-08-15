/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_OIDCOLLECTION
#define ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_OIDCOLLECTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_OID
#include "Oid.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Security::Cryptography::Encoding
{
	class OidCollection
	{
	public:
		constexpr OidCollection() = default;

		constexpr OidCollection(const OidCollection& Source) = delete;

		constexpr OidCollection(OidCollection&& Right) noexcept = delete;

		inline constexpr ~OidCollection()
		{
			if (nullptr != _Data)
			{
				delete[] _Data;
				_Data = nullptr;
			}
		}
	public:
		constexpr OidCollection& operator=(const OidCollection& Source) = delete;

		constexpr OidCollection& operator=(OidCollection&& Right) noexcept = delete;
	private:
		Elysium::Core::Template::System::size _Capacity;
		Elysium::Core::Template::System::size _Count;
		Oid* _Data;
	};
}
#endif
