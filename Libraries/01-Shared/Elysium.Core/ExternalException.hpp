/*===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_RUNTIME_INTEROPSERVICES_EXTERNALEXCEPTION
#define ELYSIUM_CORE_RUNTIME_INTEROPSERVICES_EXTERNALEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "System.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef ELYSIUM_CORE_EXCEPTION
#include "Exception.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

#ifndef _INC_COMDEF
#include <comdef.h>
#endif

namespace Elysium::Core::Runtime::InteropServices
{
	/// <summary>
	/// The base exception type for all COM interop exceptions and structured exception handling (SEH) exceptions.
	/// </summary>
	class ELYSIUM_CORE_API ExternalException : public Exception
	{
	public:
		ExternalException();

		ExternalException(const Elysium::Core::int32_t ErrorCode);

		//ExternalException(const ExternalException& Source) = delete;
		//ExternalException(ExternalException&& Right) noexcept = delete;

		virtual ~ExternalException();

		//ExternalException& operator=(const ExternalException& Source) = delete;
		//ExternalException& operator=(ExternalException&& Right) noexcept = delete;

		const Elysium::Core::int32_t GetErrorCode() const;

		const HRESULT GetHResult() const;
	protected:
		const Elysium::Core::int32_t _ErrorCode;
	private:
		Elysium::Core::Utf8String GetErrorMessage(const Elysium::Core::int32_t ErrorCode);
	};
}
#endif
#endif
