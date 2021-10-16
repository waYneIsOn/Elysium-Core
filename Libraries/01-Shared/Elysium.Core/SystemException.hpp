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

		SystemException(Elysium::Core::String&& Message);

		virtual ~SystemException();

		const Elysium::Core::int32_t GetErrorCode() const;
	private:
		const Elysium::Core::int32_t _ErrorCode;
	};
}
#endif
