/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_NETWORKINFORMATION_NETWORKINTERFACE
#define ELYSIUM_CORE_NET_NETWORKINFORMATION_NETWORKINTERFACE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_NET_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_NETWORKINFORMATION_NETWORKINTERFACETYPE
#include "../Elysium.Core.Template/Net/NetworkInformation/NetworkInterfaceType.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_NETWORKINFORMATION_OPERATIONALSTATUS
#include "../Elysium.Core.Template/Net/NetworkInformation/OperationalStatus.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_NETWORKINFORMATION_NETWORKINTERFACECOMPONENT
#include "../Elysium.Core.Template/Net/NetworkInformation/NetworkInterfaceComponent.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Elysium.Core.Template/Container/Vector.hpp"
#endif

namespace Elysium::Core::Net::NetworkInformation
{
	class ELYSIUM_CORE_NET_API NetworkInterface
	{
		friend class Elysium::Core::Template::Container::Vector<NetworkInterface>;
	protected:
		NetworkInterface();

		NetworkInterface(const char8_t* Id);
	public:
		NetworkInterface(const NetworkInterface& Source);

		NetworkInterface(NetworkInterface&& Right) noexcept;

		virtual ~NetworkInterface();
	public:
		NetworkInterface& operator=(const NetworkInterface& Source);

		NetworkInterface& operator=(NetworkInterface&& Right) noexcept;
	public:
		static const Elysium::Core::Template::Container::Vector<NetworkInterface> GetAllNetworkInterfaces();

		//static const Elysium::Core::int32_t GetLoopbackInterfaceIndex();
		//static const Elysium::Core::int32_t GetIPv6LoopbackInterfaceIndex();
	public:
		const Elysium::Core::Utf8String& GetId() const;

		const Elysium::Core::Utf8String& GetName() const;

		const Elysium::Core::Utf8String& GetDescription() const;

		const Elysium::Core::Template::Net::NetworkInformation::NetworkInterfaceType& GetNetworkInterfaceType() const;

		const Elysium::Core::Template::Net::NetworkInformation::OperationalStatus& GetOperationalStatus() const;

		const Elysium::Core::int64_t GetSpeed() const;

		//const bool Supports(const NetworkInterfaceComponent NetworkInterfaceComponent) const;
	private:
		Elysium::Core::Utf8String _Id;
		Elysium::Core::Utf8String _Name;
		Elysium::Core::Utf8String _Description;
		Elysium::Core::Template::Net::NetworkInformation::NetworkInterfaceType _Type;
		Elysium::Core::Template::Net::NetworkInformation::OperationalStatus _Status;
		Elysium::Core::int64_t _Speed;
		Elysium::Core::int32_t _LoopbackInterfaceIndex;
		Elysium::Core::int32_t _IPv6LoopbackInterfaceIndex;
		bool _IsReceiveOnly;
		bool _SupportsMulticast;
	};
}
#endif
