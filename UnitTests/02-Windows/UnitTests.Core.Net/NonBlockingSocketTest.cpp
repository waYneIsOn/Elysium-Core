#include "CppUnitTest.h"

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKET
#include "../../../Libraries/01-Shared/Elysium.Core.Net/Socket.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKETEXCEPTION
#include "../../../Libraries/01-Shared/Elysium.Core.Net/SocketException.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_DNSENDPOINT
#include "../../../Libraries/01-Shared/Elysium.Core.Net/DnsEndPoint.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_IPENDPOINT
#include "../../../Libraries/01-Shared/Elysium.Core.Net/IPEndPoint.hpp"
#endif

using namespace Elysium::Core;
using namespace Elysium::Core::Net;
using namespace Elysium::Core::Net::Sockets;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Net::Sockets
{
	TEST_CLASS(NonBlockingSocketTest)
	{
	public:
		TEST_METHOD(ConnectUsingHost)
		{
			Socket ClientSocket = Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			ClientSocket.SetBlocking(false);

			try
			{
				ClientSocket.Connect(Elysium::Core::String("www.tutorialspoint.com"), 80);
				Assert::Fail();
			}
			catch (const SocketException& ex)
			{
				SocketError InitialError = ex.GetSocketError();
				if (InitialError != SocketError::WouldBlock)
				{
					Assert::Fail();
				}

				SocketError Error = SocketError::IsConnected;
				do
				{
					try
					{
						ClientSocket.Connect(Elysium::Core::String("www.tutorialspoint.com"), 80);
						Assert::Fail();
					}
					catch (const SocketException& ex)
					{
						Error = ex.GetSocketError();
						if (Error == SocketError::NotConnected)
						{
							Assert::Fail();
						}
					}
				} while (Error != SocketError::IsConnected);
			}

			ClientSocket.Shutdown(SocketShutdown::Both);
			ClientSocket.Disconnect(false);
		}

		TEST_METHOD(ReceiveNothing)
		{
			Socket ClientSocket = Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			ClientSocket.Connect(Elysium::Core::String("www.tutorialspoint.com"), 80);

			ClientSocket.SetBlocking(false);
			Assert::IsFalse(ClientSocket.GetBlocking());

			try
			{
				byte Buffer[32];
				const size_t BytesReceived = ClientSocket.Receive(&Buffer[0], 32);

				Assert::Fail();
			}
			catch(const SocketException& ex)
			{ }

			ClientSocket.Shutdown(SocketShutdown::Both);
			ClientSocket.Disconnect(false);
		}
	};
}