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

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../../../Libraries/01-Shared/Elysium.Core.Text/Encoding.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_THREADPOOL
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/ThreadPool.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_THREAD
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/Thread.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_MANUALRESETEVENT
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/ManualResetEvent.hpp"
#endif

using namespace Elysium::Core;
using namespace Elysium::Core::Collections::Template;
using namespace Elysium::Core::Net;
using namespace Elysium::Core::Net::Sockets;
using namespace Elysium::Core::Text;
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
			ClientSocket.Connect(Elysium::Core::String(u8"www.tutorialspoint.com"), 80);
			Assert::IsTrue(ClientSocket.GetBlocking());

			ClientSocket.Shutdown(SocketShutdown::Both);
			ClientSocket.Disconnect(false);
		}

		TEST_METHOD(PollAndSelectRead)
		{
			Socket HttpClientSocket = Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			HttpClientSocket.Connect(Elysium::Core::String(u8"www.tutorialspoint.com"), 80);
			Assert::IsFalse(HttpClientSocket.Poll(1000000, SelectMode::SelectRead));

			Socket FtpClientSocket = Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			FtpClientSocket.Connect(Elysium::Core::String(u8"demo.wftpserver.com"), 21);
			Assert::IsTrue(FtpClientSocket.Poll(1000000, SelectMode::SelectRead));
			List<Socket*> CheckRead = List<Socket*>(2);
			CheckRead[0] = &HttpClientSocket;
			CheckRead[1] = &FtpClientSocket;
			Socket::Select(&CheckRead, nullptr, nullptr, 1000000);
			Assert::AreEqual((Elysium::Core::size)1, CheckRead.GetCount());
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
			ClientSocket.Connect(Elysium::Core::String(u8"www.tutorialspoint.com"), 80);

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
			Elysium::Core::Net::IPEndPoint RemoteEndPoint = Elysium::Core::Net::IPEndPoint(Elysium::Core::Net::IPAddress::Parse(Elysium::Core::String(u8"93.184.220.42")),
				443);

			Socket ClientSocket = Socket(RemoteEndPoint.GetAddressFamily(), SocketType::Stream, ProtocolType::Tcp);
			ClientSocket.Connect(RemoteEndPoint);

			ClientSocket.Shutdown(SocketShutdown::Both);
			ClientSocket.Disconnect(false);
		}

		TEST_METHOD(Reconnect)
		{
			Socket ClientSocket = Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			ClientSocket.Connect(Elysium::Core::String(u8"www.tutorialspoint.com"), 80);

			ClientSocket.Shutdown(SocketShutdown::Both);
			ClientSocket.Disconnect(false);

			try
			{
				ClientSocket.Connect(Elysium::Core::String(u8"www.tutorialspoint.com"), 80);

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
			ClientSocket.Connect(Elysium::Core::String(u8"www.tutorialspoint.com"), 80);
			ClientSocket.SetReceiveTimeout(1000);

			try
			{
				byte Buffer[32];
				const Elysium::Core::size BytesReceived = ClientSocket.Receive(&Buffer[0], 32);

				Assert::Fail();
			}
			catch (const SocketException& ex)
			{ }
		}

		TEST_METHOD(AsyncClient)
		{
			DnsEndPoint RemoteEndPoint = DnsEndPoint(Elysium::Core::String(u8"demo.wftpserver.com"), 21, AddressFamily::InterNetwork);
			Socket AsyncClient = Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);

			const IAsyncResult* ConnectResult = AsyncClient.BeginConnect(RemoteEndPoint,
				Delegate<void, const Elysium::Core::IAsyncResult*>::Bind<BlockingSocketTest, &BlockingSocketTest::ConnectCallback>(*this), nullptr);
			ConnectResult->GetAsyncWaitHandle().WaitOne();
			
			Elysium::Core::byte ReceiveBuffer[256];
			const IAsyncResult* ReceiveResult = AsyncClient.BeginReceive(&ReceiveBuffer[0], 256, SocketFlags::None,
				Delegate<void, const Elysium::Core::IAsyncResult*>::Bind<BlockingSocketTest, &BlockingSocketTest::ReceiveCallback>(*this), nullptr);
			ReceiveResult->GetAsyncWaitHandle().WaitOne();
			
			Elysium::Core::String HelpMessage = Elysium::Core::String(u8"HELP\r\n");
			const Encoding& UTF8Encoding = Encoding::UTF8();
			Array<byte> Bytes = UTF8Encoding.GetBytes(&HelpMessage[0], HelpMessage.GetLength());
			const IAsyncResult* SendResult = AsyncClient.BeginSend(&Bytes[0], Bytes.GetLength(), SocketFlags::None,
				Delegate<void, const Elysium::Core::IAsyncResult*>::Bind<BlockingSocketTest, &BlockingSocketTest::SendCallback>(*this), nullptr);
			SendResult->GetAsyncWaitHandle().WaitOne();
			
			ReceiveResult = AsyncClient.BeginReceive(&ReceiveBuffer[0], 256, SocketFlags::None,
				Delegate<void, const Elysium::Core::IAsyncResult*>::Bind<BlockingSocketTest, &BlockingSocketTest::ReceiveCallback>(*this), nullptr);
			ReceiveResult->GetAsyncWaitHandle().WaitOne();
			
			//AsyncClient.Shutdown(SocketShutdown::Both);
			const IAsyncResult* DisconnectResult = AsyncClient.BeginDisconnect(true,
				Delegate<void, const Elysium::Core::IAsyncResult*>::Bind<BlockingSocketTest, &BlockingSocketTest::DisconnectCallback>(*this), nullptr);
			DisconnectResult->GetAsyncWaitHandle().WaitOne();
		}

		TEST_METHOD(CloseWhileWaitingForAsyncReceive)
		{
			DnsEndPoint RemoteEndPoint = DnsEndPoint(Elysium::Core::String(u8"www.google.com"), 80, AddressFamily::InterNetwork);
			Socket AsyncClient = Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			AsyncClient.Connect(RemoteEndPoint);

			Elysium::Core::byte ReceiveBuffer[256];
			const IAsyncResult* ReceiveResult = AsyncClient.BeginReceive(&ReceiveBuffer[0], 256, SocketFlags::None,
				Delegate<void, const Elysium::Core::IAsyncResult*>::Bind<BlockingSocketTest, &BlockingSocketTest::ReceiveCallback>(*this), nullptr);

			AsyncClient.Shutdown(SocketShutdown::Both);
			AsyncClient.Disconnect(false);

			ReceiveResult->GetAsyncWaitHandle().WaitOne();
		}
		
		TEST_METHOD(AsyncAccept)
		{
			IPEndPoint LocalEndPoint = IPEndPoint(IPAddress::Parse(u8"127.0.0.1"), 80);
			Socket AsyncServer = Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			AsyncServer.Bind(LocalEndPoint);
			AsyncServer.Listen(100);
			//AsyncServer.SetSocketOption(SocketOptionLevel::Socket, SocketOptionName::AcceptConnection, 1);

			const IAsyncResult* AcceptResult = AsyncServer.BeginAccept(
				Delegate<void, const IAsyncResult*>::Bind<BlockingSocketTest, &BlockingSocketTest::AcceptCallback>(*this), nullptr);
			
			Socket AsyncClient = Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			AsyncClient.Connect(LocalEndPoint);

			AcceptResult->GetAsyncWaitHandle().WaitOne();

			//AsyncServer.Shutdown(SocketShutdown::Both);	// ToDo: this throws an exception as a listening socket will never get into a "connected-state"
		}
	private:
		void AcceptCallback(const IAsyncResult* Result)
		{
			Elysium::Core::Net::Sockets::AcceptAsyncResult* AsyncAcceptResult = (Elysium::Core::Net::Sockets::AcceptAsyncResult*)Result;

			Socket& Socket = AsyncAcceptResult->GetSocket();
			Socket.EndAccept(Result);
		}
		
		void ConnectCallback(const Elysium::Core::IAsyncResult* Result)
		{

		}

		void DisconnectCallback(const Elysium::Core::IAsyncResult* Result)
		{

		}

		void ReceiveCallback(const Elysium::Core::IAsyncResult* Result)
		{
			//StateObject state = (StateObject)ar.AsyncState;
			//Socket client = state.workSocket;

			const SendReceiveAsyncResult* AsyncResult = (const SendReceiveAsyncResult*)Result;
			Socket& Socket = AsyncResult->GetSocket();

			SocketError ErrorCode = SocketError::Success;
			const Elysium::Core::size BytesReceived = Socket.EndReceive(Result, ErrorCode);
		}

		void SendCallback(const Elysium::Core::IAsyncResult* Result)
		{
			const SendReceiveAsyncResult* AsyncResult = (const SendReceiveAsyncResult*)Result;
			Socket& Socket = AsyncResult->GetSocket();

			SocketError ErrorCode = SocketError::Success;
			const Elysium::Core::size BytesSent = Socket.EndSend(Result, ErrorCode);
		}
	};
}