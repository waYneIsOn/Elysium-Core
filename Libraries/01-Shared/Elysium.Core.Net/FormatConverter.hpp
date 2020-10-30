/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_FORMATCONVERTER
#define ELYSIUM_CORE_NET_FORMATCONVERTER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_ADDRESSFAMILY
#include "AddressFamily.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_PROTOCOLTYPE
#include "ProtocolType.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKETTYPE
#include "SocketType.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_NETWORKINFORMATION_GETADAPTERSADDRESSESFLAGS
#include "GetAdaptersAddressesFlags.hpp"
#endif

namespace Elysium::Core::Net
{
	class FormatConverter
	{
	public:
		static const Elysium::Core::int32_t Convert(Elysium::Core::Net::Sockets::AddressFamily AddressFamily);
		static const Elysium::Core::int32_t Convert(Elysium::Core::Net::Sockets::ProtocolType ProtocolType);
		static const Elysium::Core::int32_t Convert(Elysium::Core::Net::Sockets::SocketType SocketType);

		static const Elysium::Core::int32_t Convert(Elysium::Core::Net::NetworkInformation::GetAdaptersAddressesFlags GetAdaptersAddressesFlags);
	private:
		FormatConverter();
		~FormatConverter();
	};
}
#endif
