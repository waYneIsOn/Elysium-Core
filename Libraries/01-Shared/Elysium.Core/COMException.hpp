/*===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_RUNTIME_INTEROPSERVICES_COMEXCEPTION
#define ELYSIUM_CORE_RUNTIME_INTEROPSERVICES_COMEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
#ifndef ELYSIUM_CORE_RUNTIME_INTEROPSERVICES_EXTERNALEXCEPTION
#include "ExternalException.hpp"
#endif

namespace Elysium::Core::Runtime::InteropServices
{
	/// The exception that is thrown when an unrecognized HRESULT is returned from a COM method call.
	class ELYSIUM_CORE_API COMException : public ExternalException
	{
	public:
		COMException();
		COMException(const Elysium::Core::int32_t ErrorCode);
		virtual ~COMException();
	};
}
#endif
#endif
