/*===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_RUNTIME_INTEROPSERVICES_COMEXCEPTION
#define ELYSIUM_CORE_RUNTIME_INTEROPSERVICES_COMEXCEPTION

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
		COMException(const String& Message);
		COMException(const String& Message, const int ErrorCode);
		~COMException();
	};
}
#endif
#endif
