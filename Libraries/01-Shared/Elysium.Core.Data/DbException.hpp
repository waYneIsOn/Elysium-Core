/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_COMMON_DBEXCEPTION
#define ELYSIUM_CORE_DATA_COMMON_DBEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_DATA_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_RUNTIME_INTEROPSERVICES_EXTERNALEXCEPTION
#include "../Elysium.Core/ExternalException.hpp"
#endif


namespace Elysium::Core::Data::Common
{
	class ELYSIUM_CORE_DATA_API DbException : public Elysium::Core::Runtime::InteropServices::ExternalException
	{
	public:
		DbException();
		DbException(const Elysium::Core::int32_t ErrorCode);
		virtual ~DbException();
	};
}
#endif
