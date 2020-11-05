#include "CppUnitTest.h"

#ifndef ELYSIUM_CORE_NET_NETWORKINFORMATION_NETWORKINTERFACE
#include "../../../Libraries/01-Shared/Elysium.Core.Net/NetworkInterface.hpp"
#endif

using namespace Elysium::Core;
using namespace Elysium::Core::Collections::Template;
using namespace Elysium::Core::Net;
using namespace Elysium::Core::Net::NetworkInformation;

namespace UnitTests::Core::Net::NetworkInformation
{
	TEST_CLASS(NetworkInterfaceTest)
	{
	public:
		TEST_METHOD(TestGetAllNetworkInterfaces)
		{
			const Array<NetworkInterface> NetworkInterfaces = NetworkInterface::GetAllNetworkInterfaces();
			for (size_t i = 0; i < NetworkInterfaces.GetLength(); i++)
			{
				const NetworkInterface& NetworkInterface = NetworkInterfaces[i];

				const String& Id = NetworkInterface.GetId();
				const String& Name = NetworkInterface.GetName();
				const String& Description = NetworkInterface.GetDescription();
				const NetworkInterfaceType& Type = NetworkInterface.GetNetworkInterfaceType();
				const OperationalStatus& Status = NetworkInterface.GetOperationalStatus();
				const Elysium::Core::int64_t Speed = NetworkInterface.GetSpeed();
			}
		}
	};
}
