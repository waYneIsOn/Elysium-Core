/*===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_RUNTIME_INTEROPSERVICES_EXTERNALEXCEPTION
#define ELYSIUM_CORE_RUNTIME_INTEROPSERVICES_EXTERNALEXCEPTION

#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)

#ifndef ELYSIUM_CORE_EXCEPTION
#include "Exception.hpp"
#endif

#ifndef _INC_COMDEF
#include <comdef.h>
#endif

#pragma warning(disable : 4251)	// disable warning about str::string

namespace Elysium::Core::Runtime::InteropServices
{
	/// The base exception type for all COM interop exceptions and structured exception handling (SEH) exceptions.
	class ELYSIUM_CORE_API ExternalException : public Exception
	{
	public:
		ExternalException();
		ExternalException(const String& Message);
		ExternalException(const String& Message, const int ErrorCode);
		virtual ~ExternalException();

		int GetErrorCode();
		HRESULT GetHResult();
	protected:
		void SetHResult(HRESULT ErrorCode);
	private:
		HRESULT _ErrorCode;

		//_com_error _COMError;
		//char* _ErrorMessage = nullptr;
		//Elysium::Core::Collections::IDictionary<char, char> _Data;
	};
}
#endif
#endif
