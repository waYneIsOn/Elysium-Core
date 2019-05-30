/*===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_RUNTIME_INTEROPSERVICES_EXTERNALEXCEPTION
#define ELYSIUM_CORE_RUNTIME_INTEROPSERVICES_EXTERNALEXCEPTION

#ifndef ELYSIUM_CORE_EXCEPTION
#include "Exception.hpp"
#endif

#ifndef _INC_COMDEF
#include <comdef.h>
#endif

#ifndef _XSTRING_
#include <xstring>
#endif

#pragma warning(disable : 4251)	// disable warning about str::string

namespace Elysium
{
	namespace Core
	{
		namespace Runtime
		{
			namespace InteropServices
			{
				/// The base exception type for all COM interop exceptions and structured exception handling (SEH) exceptions.
				class EXPORT ExternalException : public Exception
				{
				public:
					ExternalException();
					ExternalException(const char* Message);
					ExternalException(const char* Message, const int ErrorCode);
					~ExternalException();

					int GetErrorCode();
					HRESULT GetHResult();

					virtual const char* what() const throw();
				protected:
					void SetHResult(HRESULT ErrorCode);
				private:
					HRESULT _ErrorCode;
					std::string _ErrorMessage;

					//_com_error _COMError;
					//char* _ErrorMessage = nullptr;
					//Elysium::Core::Collections::IDictionary<char, char> _Data;
				};
			}
		}
	}
}
#endif
