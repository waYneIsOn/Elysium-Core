/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_OIDNODE
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_OIDNODE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/Stringg.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

namespace Elysium::Core::Security::Cryptography
{
	/// <summary>
	/// 
	/// </summary>
	class ELYSIUM_CORE_SECURITY_API OidNode final
	{
	public:
		OidNode(const Elysium::Core::uint32_t Value, const Elysium::Core::Utf8String Name);

		OidNode(const OidNode& Source) = delete;

		OidNode(OidNode&& Right) noexcept = delete;

		~OidNode();
	public:
		OidNode& operator=(const OidNode& Source) = delete;

		OidNode& operator=(OidNode&& Right) noexcept = delete;
	private:
		const Elysium::Core::uint32_t _Value;
		const Elysium::Core::Utf8String _Name;
		//OidNode* _Parent;
		//OidNode* _Children;
	};
}
#endif
