/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_SECURITY_CRYPTOGRAPHY_CRYPTOGRAPHICEXCEPTION
#define ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_SECURITY_CRYPTOGRAPHY_CRYPTOGRAPHICEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_SYSTEMEXCEPTION
#include "../../SystemException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../../../Functional/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Exceptions::Security::Cryptography
{
	class CryptographicException
		: public SystemException
	{
	public:
		inline constexpr CryptographicException(const char8_t* Message = nullptr)
			: Elysium::Core::Template::Exceptions::SystemException(GetLastError(), Message)
		{}

		inline constexpr CryptographicException(const System::uint32_t ErrorCode, const char8_t* Message)
			: Elysium::Core::Template::Exceptions::SystemException(ErrorCode, Message)
		{}

		inline constexpr CryptographicException(const Elysium::Core::Template::System::uint32_t ErrorCode)
			: Elysium::Core::Template::Exceptions::SystemException(ErrorCode)
		{}

		virtual ~CryptographicException() = default;
	public:
		constexpr CryptographicException& operator=(const CryptographicException& Source) = delete;

		//constexpr CryptographicException& operator=(CryptographicException&& Right) noexcept;
	};
}
#endif
