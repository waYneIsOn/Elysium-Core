#include "CppUnitTest.h"

#ifndef ELYSIUM_CORE_NET_NETWORKINFORMATION_NETWORKINTERFACE
#include "../../../Libraries/01-Shared/Elysium.Core.Net/NetworkInterface.hpp"
#endif

using namespace Elysium::Core;
using namespace Elysium::Core::Net;
using namespace Elysium::Core::Net::NetworkInformation;

namespace UnitTests::Core::Net::NetworkInformation
{
	TEST_CLASS(NetworkInterfaceTest)
	{
	public:
		TEST_METHOD(TestGetAllNetworkInterfaces)
		{
			const Elysium::Core::Template::Container::Vector<NetworkInterface> NetworkInterfaces = NetworkInterface::GetAllNetworkInterfaces();
			for (Elysium::Core::size i = 0; i < NetworkInterfaces.GetLength(); i++)
			{
				const NetworkInterface& NetworkInterface = NetworkInterfaces[i];

				const Elysium::Core::Utf8String& Id = NetworkInterface.GetId();
				const Elysium::Core::Utf8String& Name = NetworkInterface.GetName();
				const Elysium::Core::Utf8String& Description = NetworkInterface.GetDescription();
				const NetworkInterfaceType& Type = NetworkInterface.GetNetworkInterfaceType();
				const OperationalStatus& Status = NetworkInterface.GetOperationalStatus();
				const Elysium::Core::int64_t Speed = NetworkInterface.GetSpeed();
			}
		}
	};
}
