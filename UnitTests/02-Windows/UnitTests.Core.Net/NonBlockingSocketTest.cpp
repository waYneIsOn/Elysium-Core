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
			Socket ClientSocket = Socket(Elysium::Core::Template::Net::Sockets::AddressFamily::InterNetwork, Elysium::Core::Template::Net::Sockets::SocketType::Stream, Elysium::Core::Template::Net::Sockets::ProtocolType::Tcp);
			ClientSocket.SetBlocking(false);

			try
			{
				ClientSocket.Connect(Elysium::Core::Utf8String(u8"www.tutorialspoint.com"), 80);
				Assert::Fail();
			}
			catch (const SocketException& ex)
			{
				Elysium::Core::Template::Net::Sockets::SocketError InitialError = ex.GetSocketErrorCode();
				if (InitialError != Elysium::Core::Template::Net::Sockets::SocketError::WouldBlock)
				{
					Assert::Fail();
				}

				Elysium::Core::Template::Net::Sockets::SocketError Error = Elysium::Core::Template::Net::Sockets::SocketError::IsConnected;
				do
				{
					try
					{
						ClientSocket.Connect(Elysium::Core::Utf8String(u8"www.tutorialspoint.com"), 80);
						Assert::Fail();
					}
					catch (const SocketException& ex)
					{
						Error = ex.GetSocketErrorCode();
						if (Error == Elysium::Core::Template::Net::Sockets::SocketError::NotConnected)
						{
							Assert::Fail();
						}
					}
				} while (Error != Elysium::Core::Template::Net::Sockets::SocketError::IsConnected);
			}

			ClientSocket.Shutdown(Elysium::Core::Template::Net::Sockets::SocketShutdown::Both);
			ClientSocket.Disconnect(false);
		}

		TEST_METHOD(ReceiveNothing)
		{
			Socket ClientSocket = Socket(Elysium::Core::Template::Net::Sockets::AddressFamily::InterNetwork, Elysium::Core::Template::Net::Sockets::SocketType::Stream,
				Elysium::Core::Template::Net::Sockets::ProtocolType::Tcp);
			ClientSocket.Connect(Elysium::Core::Utf8String(u8"www.tutorialspoint.com"), 80);

			ClientSocket.SetBlocking(false);
			Assert::IsFalse(ClientSocket.GetBlocking());

			try
			{
				byte Buffer[32];
				const Elysium::Core::size BytesReceived = ClientSocket.Receive(&Buffer[0], 32);

				Assert::Fail();
			}
			catch(const SocketException& ex)
			{ }

			ClientSocket.Shutdown(Elysium::Core::Template::Net::Sockets::SocketShutdown::Both);
			ClientSocket.Disconnect(false);
		}
	};
}