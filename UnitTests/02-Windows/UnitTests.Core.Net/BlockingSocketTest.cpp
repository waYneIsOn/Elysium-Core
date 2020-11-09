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

#ifndef ELYSIUM_CORE_THREADING_THREADPOOL
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/ThreadPool.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_MANUALRESETEVENT
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/ManualResetEvent.hpp"
#endif

using namespace Elysium::Core;
using namespace Elysium::Core::Collections::Template;
using namespace Elysium::Core::Net;
using namespace Elysium::Core::Net::Sockets;
using namespace Elysium::Core::Threading;
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

			ClientSocket.Shutdown(SocketShutdown::Both);
			ClientSocket.Disconnect(false);
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

			HttpClientSocket.Shutdown(SocketShutdown::Both);
			HttpClientSocket.Disconnect(false);

			FtpClientSocket.Shutdown(SocketShutdown::Both);
			FtpClientSocket.Disconnect(false);
		}

		TEST_METHOD(ParseIpAddresses)
		{
			// int64
			Elysium::Core::Net::IPAddress Int64_1 = Elysium::Core::Net::IPAddress::Parse(Elysium::Core::String(u8"2130706433"));

			// IPv4
			Elysium::Core::Net::IPAddress IPv4_1 = Elysium::Core::Net::IPAddress::Parse(Elysium::Core::String(u8"127.0.0.1"));
			Elysium::Core::Net::IPAddress IPv4_2 = Elysium::Core::Net::IPAddress::Parse(Elysium::Core::String(u8"127.0.0.1:80"));

			//Assert::AreEqual("127.0.0.1", &IPv4_1.ToString()[0]);

			// IPv6
			Elysium::Core::Net::IPAddress IPv6_1 = Elysium::Core::Net::IPAddress::Parse(Elysium::Core::String(u8"0:0:0:0:0:0:0:1"));

			// invalid input
			Elysium::Core::Net::IPAddress IP1 = Elysium::Core::Net::IPAddress::Parse(Elysium::Core::String(u8"277.0.0.1"));
		}

		TEST_METHOD(ConnectUsingHost)
		{
			Socket ClientSocket = Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			ClientSocket.Connect(Elysium::Core::String("www.tutorialspoint.com"), 80);

			ClientSocket.Shutdown(SocketShutdown::Both);
			ClientSocket.Disconnect(false);
		}

		TEST_METHOD(ConnectUsingDnsEndPoint)
		{
			Elysium::Core::Net::DnsEndPoint RemoteEndPoint = Elysium::Core::Net::DnsEndPoint(Elysium::Core::String(u8"www.tutorialspoint.com"), 80,
				Elysium::Core::Net::Sockets::AddressFamily::InterNetwork);

			Socket ClientSocket = Socket(RemoteEndPoint.GetAddressFamily(), SocketType::Stream, ProtocolType::Tcp);
			ClientSocket.Connect(RemoteEndPoint);

			ClientSocket.Shutdown(SocketShutdown::Both);
			ClientSocket.Disconnect(false);
		}

		TEST_METHOD(ConnectUsingIpEndPoint)
		{
			Elysium::Core::Net::IPEndPoint RemoteEndPoint = Elysium::Core::Net::IPEndPoint(Elysium::Core::Net::IPAddress::Parse(Elysium::Core::String("93.184.220.42")),
				443);

			Socket ClientSocket = Socket(RemoteEndPoint.GetAddressFamily(), SocketType::Stream, ProtocolType::Tcp);
			ClientSocket.Connect(RemoteEndPoint);

			ClientSocket.Shutdown(SocketShutdown::Both);
			ClientSocket.Disconnect(false);
		}

		TEST_METHOD(Reconnect)
		{
			Socket ClientSocket = Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			ClientSocket.Connect(Elysium::Core::String("www.tutorialspoint.com"), 80);

			ClientSocket.Shutdown(SocketShutdown::Both);
			ClientSocket.Disconnect(false);

			try
			{
				ClientSocket.Connect(Elysium::Core::String("www.tutorialspoint.com"), 80);

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

		TEST_METHOD(AsyncReceive)
		{

			Socket AsyncClient = Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);

			ThreadPool IOPool = ThreadPool(1, true);
			const bool IsSocketBound = IOPool.BindIOCompletionCallback(AsyncClient);
			IOPool.Start();

			AsyncClient.Connect(Elysium::Core::String("demo.wftpserver.com"), 21);

			Elysium::Core::byte Buffer[256];
			Delegate<void, const SendReceiveAsyncResult&> DelegateReceiveCallback = Delegate<void, const SendReceiveAsyncResult&>::CreateDelegate<BlockingSocketTest, &BlockingSocketTest::ReceiveCallback>(*this);
			
			SendReceiveAsyncResult Result = AsyncClient.BeginReceive(&Buffer[0], 256, 0, SocketFlags::None, DelegateReceiveCallback, nullptr);
			_ReceiveDone.WaitOne();

			IOPool.Stop();
		}
	private:
		ManualResetEvent _ReceiveDone = ManualResetEvent(false);

		void ReceiveCallback(const SendReceiveAsyncResult& Result)
		{
			SocketError ErrorCode = SocketError::Success;
			const Socket& Socket = Result.GetSocket();
			const size_t BytesReceived = Socket.EndReceive(Result, ErrorCode);
			_ReceiveDone.Set();
		}
	};
}