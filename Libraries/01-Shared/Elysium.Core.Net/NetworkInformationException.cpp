#include "NetworkInformationException.hpp"

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

Elysium::Core::Net::NetworkInformation::NetworkInformationException::NetworkInformationException(const Elysium::Core::int32_t ErrorCode)
	: Elysium::Core::Runtime::InteropServices::ExternalException(ErrorCode)
{ }
Elysium::Core::Net::NetworkInformation::NetworkInformationException::~NetworkInformationException()
{ }
