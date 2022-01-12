/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SYSTEMEXCEPTION
#define ELYSIUM_CORE_SYSTEMEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_EXCEPTION
#include "Exception.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

namespace Elysium::Core
{
	/// <summary>
	/// 
	/// </summary>
	class ELYSIUM_CORE_API SystemException : public Exception
	{
	public:
		SystemException();

		SystemException(const char8_t* Message);

		SystemException(Elysium::Core::Utf8String&& Message);

		virtual ~SystemException();
	public:
		const Elysium::Core::uint32_t GetErrorCode() const;
	private:
		const Elysium::Core::uint32_t _ErrorCode;
	};
}
#endif
