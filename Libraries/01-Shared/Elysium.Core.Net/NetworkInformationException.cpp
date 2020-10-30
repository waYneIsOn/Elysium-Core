#include "NetworkInformationException.hpp"

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

Elysium::Core::Net::NetworkInformation::NetworkInformationException::NetworkInformationException(const int ErrorCode)
	: Elysium::Core::Runtime::InteropServices::ExternalException(Elysium::Core::String(u8""), ErrorCode)
{ }
Elysium::Core::Net::NetworkInformation::NetworkInformationException::~NetworkInformationException()
{ }
