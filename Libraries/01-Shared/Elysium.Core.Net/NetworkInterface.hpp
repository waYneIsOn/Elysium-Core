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

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_NETWORKINFORMATION_NETWORKINTERFACETYPE
#include "NetworkInterfaceType.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_NETWORKINFORMATION_OPERATIONALSTATUS
#include "OperationalStatus.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_NETWORKINFORMATION_NETWORKINTERFACECOMPONENT
#include "NetworkInterfaceComponent.hpp"
#endif

namespace Elysium::Core::Net::NetworkInformation
{
	class ELYSIUM_CORE_NET_API NetworkInterface
	{
		friend class Elysium::Core::Collections::Template::Array<NetworkInterface>;
	public:
		NetworkInterface(const NetworkInterface& Source) = delete;
		NetworkInterface(NetworkInterface&& Right) noexcept = delete;
		virtual ~NetworkInterface();

		NetworkInterface& operator=(const NetworkInterface& Source) = delete;
		NetworkInterface& operator=(NetworkInterface&& Right) noexcept = delete;

		static const Elysium::Core::Collections::Template::Array<NetworkInterface> GetAllNetworkInterfaces();

		//static const Elysium::Core::int32_t GetLoopbackInterfaceIndex();
		//static const Elysium::Core::int32_t GetIPv6LoopbackInterfaceIndex();

		const Elysium::Core::Utf8String& GetId() const;

		const Elysium::Core::Utf8String& GetName() const;

		const Elysium::Core::Utf8String& GetDescription() const;

		const NetworkInterfaceType& GetNetworkInterfaceType() const;

		const OperationalStatus& GetOperationalStatus() const;

		const Elysium::Core::int64_t GetSpeed() const;

		//const bool Supports(const NetworkInterfaceComponent NetworkInterfaceComponent) const;
	protected:
		NetworkInterface();
	private:
		Elysium::Core::Utf8String _Id;
		Elysium::Core::Utf8String _Name;
		Elysium::Core::Utf8String _Description;
		NetworkInterfaceType _Type;
		OperationalStatus _Status;
		Elysium::Core::int64_t _Speed;
		Elysium::Core::int32_t _LoopbackInterfaceIndex;
		Elysium::Core::int32_t _IPv6LoopbackInterfaceIndex;
		bool _IsReceiveOnly;
		bool _SupportsMulticast;
	};
}
#endif
