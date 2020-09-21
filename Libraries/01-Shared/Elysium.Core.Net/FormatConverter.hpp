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

namespace Elysium::Core::Net
{
	class FormatConverter
	{
	public:
		static Elysium::Core::int32_t Convert(Elysium::Core::Net::Sockets::AddressFamily AddressFamily);
		static Elysium::Core::int32_t Convert(Elysium::Core::Net::Sockets::ProtocolType ProtocolType);
		static Elysium::Core::int32_t Convert(Elysium::Core::Net::Sockets::SocketType SocketType);
	private:
		FormatConverter();
		~FormatConverter();
	};
}
#endif
