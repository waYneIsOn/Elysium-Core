/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

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

		const Elysium::Core::String& GetId() const;

		const Elysium::Core::String& GetName() const;

		const Elysium::Core::String& GetDescription() const;

		const NetworkInterfaceType& GetType() const;

		const OperationalStatus& GetOperationalStatus() const;
	protected:
		NetworkInterface();
	private:
		Elysium::Core::String _Id;
		Elysium::Core::String _Name;
		Elysium::Core::String _Description;
		NetworkInterfaceType _Type;
		OperationalStatus _Status;
		//bool _IsReceiveOnly;
	};
}
#endif
