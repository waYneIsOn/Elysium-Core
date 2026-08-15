/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_SECURITY_AUTHENTICATION_INVALIDCREDENTIALEXCEPTION
#define ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_SECURITY_AUTHENTICATION_INVALIDCREDENTIALEXCEPTION

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

namespace Elysium::Core::Template::Exceptions::Security::Authentication
{
	class InvalidCredentialException
		: public SystemException
	{
	public:
		inline constexpr InvalidCredentialException(const char8_t* Message = nullptr)
			: Elysium::Core::Template::Exceptions::SystemException(GetLastError(), Message)
		{}

		inline constexpr InvalidCredentialException(const System::uint32_t ErrorCode, const char8_t* Message)
			: Elysium::Core::Template::Exceptions::SystemException(ErrorCode, Message)
		{}

		inline constexpr InvalidCredentialException(const Elysium::Core::Template::System::uint32_t ErrorCode)
			: Elysium::Core::Template::Exceptions::SystemException(ErrorCode)
		{}

		virtual ~InvalidCredentialException() = default;
	public:
		constexpr InvalidCredentialException& operator=(const InvalidCredentialException& Source) = delete;

		//constexpr InvalidCredentialException& operator=(InvalidCredentialException&& Right) noexcept;
	};
}
#endif
