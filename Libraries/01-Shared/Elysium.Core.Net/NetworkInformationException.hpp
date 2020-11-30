/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_NETWORKINFORMATION_NETWORKINFORMATIONEXCEPTION
#define ELYSIUM_CORE_NET_NETWORKINFORMATION_NETWORKINFORMATIONEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_NET_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_RUNTIME_INTEROPSERVICES_EXTERNALEXCEPTION
#include "../Elysium.Core/ExternalException.hpp"
#endif

namespace Elysium::Core::Net::NetworkInformation
{
	class ELYSIUM_CORE_NET_API NetworkInformationException : public Elysium::Core::Runtime::InteropServices::ExternalException
	{
	public:
		NetworkInformationException(const Elysium::Core::int32_t ErrorCode);
		NetworkInformationException(const NetworkInformationException& Source) = delete;
		NetworkInformationException(NetworkInformationException&& Right) noexcept = delete;
		virtual ~NetworkInformationException();

		NetworkInformationException& operator=(const NetworkInformationException& Source) = delete;
		NetworkInformationException& operator=(NetworkInformationException&& Right) noexcept = delete;
	};
}
#endif
