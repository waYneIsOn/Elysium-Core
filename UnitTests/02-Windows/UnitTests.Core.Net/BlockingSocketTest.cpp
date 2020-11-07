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
using namespace Elysium::Core::Collections::Template;
using namespace Elysium::Core::Net;
using namespace Elysium::Core::Net::Sockets;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Net::Sockets
{
	TEST_CLASS(BlockingSocketTest)
	{
	public:
		TEST_METHOD(Properties)
		{
			Socket ClientSocket = Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			ClientSocket.Connect(Elysium::Core::String("www.tutorialspoint.com"), 80);
			Assert::IsTrue(ClientSocket.GetBlocking());
		}

		TEST_METHOD(PollAndSelectRead)
		{
			Socket HttpClientSocket = Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			HttpClientSocket.Connect(Elysium::Core::String("www.tutorialspoint.com"), 80);
			Assert::IsFalse(HttpClientSocket.Poll(1000000, SelectMode::SelectRead));

			Socket FtpClientSocket = Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			FtpClientSocket.Connect(Elysium::Core::String("demo.wftpserver.com"), 21);
			Assert::IsTrue(FtpClientSocket.Poll(1000000, SelectMode::SelectRead));

			List<const Socket*> CheckRead = List<const Socket*>(2);
			CheckRead[0] = &HttpClientSocket;
			CheckRead[1] = &FtpClientSocket;
			Socket::Select(&CheckRead, nullptr, nullptr, 1000000);
			Assert::AreEqual((size_t)1, CheckRead.GetCount());
			Assert::AreEqual((const void*)&FtpClientSocket, (const void*)CheckRead[0]);
		}

		TEST_METHOD(ParseIpAddresses)
		{
			// int64
			Elysium::Core::Net::IPAddress Int64_1 = Elysium::Core::Net::IPAddress::Parse(Elysium::Core::String(u8"2130706433"));

			// IPv4
			Elysium::Core::Net::IPAddress IPv4_1 = Elysium::Core::Net::IPAddress::Parse(Elysium::Core::String(u8"127.0.0.1"));
			Elysium::Core::Net::IPAddress IPv4_2 = Elysium::Core::Net::IPAddress::Parse(Elysium::Core::String(u8"127.0.0.1:80"));

			// IPv6
			Elysium::Core::Net::IPAddress IPv6_1 = Elysium::Core::Net::IPAddress::Parse(Elysium::Core::String(u8"0:0:0:0:0:0:0:1"));

			// invalid input
			Elysium::Core::Net::IPAddress IP1 = Elysium::Core::Net::IPAddress::Parse(Elysium::Core::String(u8"277.0.0.1"));
		}

		TEST_METHOD(ConnectUsingHost)
		{
			Socket ClientSocket = Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			ClientSocket.Connect(Elysium::Core::String("www.tutorialspoint.com"), 80);
			ClientSocket.Disconnect(false);
		}

		TEST_METHOD(ConnectUsingDnsEndPoint)
		{
			Elysium::Core::Net::DnsEndPoint RemoteEndPoint = Elysium::Core::Net::DnsEndPoint(Elysium::Core::String(u8"www.tutorialspoint.com"), 80,
				Elysium::Core::Net::Sockets::AddressFamily::InterNetwork);

			Socket ClientSocket = Socket(RemoteEndPoint.GetAddressFamily(), SocketType::Stream, ProtocolType::Tcp);
			ClientSocket.Connect(RemoteEndPoint);
			ClientSocket.Disconnect(false);
		}

		TEST_METHOD(ConnectUsingIpEndPoint)
		{
			Elysium::Core::Net::IPEndPoint RemoteEndPoint = Elysium::Core::Net::IPEndPoint(Elysium::Core::Net::IPAddress::Parse(Elysium::Core::String("93.184.220.42")),
				443);

			Socket ClientSocket = Socket(RemoteEndPoint.GetAddressFamily(), SocketType::Stream, ProtocolType::Tcp);
			ClientSocket.Connect(RemoteEndPoint);
			ClientSocket.Disconnect(false);
		}

		TEST_METHOD(Reconnect)
		{
			Socket ClientSocket = Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			ClientSocket.Connect(Elysium::Core::String("www.tutorialspoint.com"), 80);
			ClientSocket.Shutdown(Elysium::Core::Net::Sockets::SocketShutdown::Both);
			ClientSocket.Disconnect(true);

			try
			{
				ClientSocket.Connect(Elysium::Core::String("www.tutorialspoint.com"), 80);
				ClientSocket.Shutdown(Elysium::Core::Net::Sockets::SocketShutdown::Both);
				ClientSocket.Disconnect(true);

				Assert::Fail();
			}
			catch (SocketException& ex)
			{
				int sadf = 456;
			}
		}

		TEST_METHOD(RunIntoTimeout)
		{
			Socket ClientSocket = Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			ClientSocket.Connect(Elysium::Core::String("www.tutorialspoint.com"), 80);
			ClientSocket.SetReceiveTimeout(1000);

			try
			{
				byte Buffer[32];
				const size_t BytesReceived = ClientSocket.Receive(&Buffer[0], 32);

				Assert::Fail();
			}
			catch (const SocketException& ex)
			{ }
		}
	};
}