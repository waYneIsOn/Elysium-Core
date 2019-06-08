#include "CppUnitTest.h"

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKET
#include "../../../Libraries/01-Shared/Elysium.Core.Net/Socket.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_IPENDPOINT
#include "../../../Libraries/01-Shared/Elysium.Core.Net/IPEndPoint.hpp"
#endif

#ifndef _XSTRING_
#include <string>
#endif

using namespace Elysium::Core;
using namespace Elysium::Core::Net;
using namespace Elysium::Core::Net::Sockets;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsCoreNet
{
	TEST_CLASS(UnitTestSocket)
	{
	public:
		// methods
		TEST_METHOD(Core_Net_Socket_ConnectAndDisconnect)
		{
			Socket ClientSocket = Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			Logger::WriteMessage("instanced");

			try
			{
				// connect to the host
				ClientSocket.Connect(_Host, _Port);
				Logger::WriteMessage("connected");

				// set both timeouts (we don't want to wait forever!!!!)
				ClientSocket.SetReceiveTimeout(200);
				ClientSocket.SetSendTimeout(200);

				// send some data to the host
				byte Data[] = "GET /Hello.htm HTTP/1.1\r\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\r\nHost: www.tutorialspoint.com\r\nAccept-Language: en-us\r\nAccept-Encoding: gzip, deflate\r\nConnection: Keep-Alive\r\n\r\n";
				int DataLength = strlen((char*)Data);

				int BytesSent = ClientSocket.Send(Data, 0, DataLength);
				Logger::WriteMessage("bytes sent:");
				Logger::WriteMessage((char*)Data);

				// ...
				//Logger::WriteMessage("bytes available:");
				//Logger::WriteMessage(std::to_string(ClientSocket.GetAvailable()).c_str());

				// received some data from the host
				byte ReceivedData[1024];
				int BytesReceived = -1;
				do
				{
					BytesReceived = ClientSocket.Receive(ReceivedData, 0, 1024);
					//Logger::WriteMessage("bytes received:");
					//Logger::WriteMessage(std::to_string(BytesReceived).c_str());

					if (BytesReceived > 0)
					{
						std::string test;
						test.assign(&ReceivedData[0], &ReceivedData[BytesReceived]);

						Logger::WriteMessage("bytes received:");
						Logger::WriteMessage(test.c_str());
					}
				} while (BytesReceived < 0);

				// disconnect from the host
				ClientSocket.Disconnect(_ReuseSocket);
				Logger::WriteMessage("disconnected");
			}
			catch (std::exception e)
			{
				Logger::WriteMessage(e.what());
			}
		}
	private:
		// fields
		//String _Host = "http://www.tutorialspoint.com"; // we don't get the correct ip using the host atm
		String _Host = L"93.184.220.42";
		//String _Host = L"127.0.0.1";
		int _Port = 80;
		bool _ReuseSocket = false;
	};
}