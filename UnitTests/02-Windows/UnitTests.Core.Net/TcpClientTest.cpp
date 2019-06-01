#include "CppUnitTest.h"

#ifndef ELYSIUM_CORE_NET_SOCKETS_TCPCLIENT
#include "../../../Libraries/01-Shared/Elysium.Core.Net/TcpClient.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_NETWORKSTREAM
#include "../../../Libraries/01-Shared/Elysium.Core.Net/NetworkStream.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKETEXCEPTION
#include "../../../Libraries/01-Shared/Elysium.Core.Net/SocketException.hpp"
#endif

using namespace Elysium::Core;
using namespace Elysium::Core::Net::Sockets;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsCoreNet
{
	TEST_CLASS(UnitTestTcpClient)
	{
	public:
		// methods
		TEST_METHOD(Core_TcpClient_ConnectAndDisconnect)
		{
			try
			{
				// ...
				TcpClient Client = TcpClient();
				Client.GetClient()->SetReceiveTimeout(200);
				Client.GetClient()->SetSendTimeout(200);
				Logger::WriteMessage("instanced");

				// ...
				Client.Connect(_Host, _Port);
				Logger::WriteMessage("connected");

				// ...
				NetworkStream* Stream = Client.GetStream();
				byte Data[] = "GET /Hello.htm HTTP/1.1\r\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\r\nHost: www.tutorialspoint.com\r\nAccept-Language: en-us\r\nAccept-Encoding: gzip, deflate\r\nConnection: Keep-Alive\r\n\r\n";
				int DataLength = strlen((char*)Data);
				Stream->Write(Data, 0, DataLength);
				Stream->Flush();
				Logger::WriteMessage("data sent");

				// ...
				BYTE ReceivedData[1024];
				int BytesReceived = Stream->Read(&ReceivedData[0], 0, 1024);
				Assert::AreEqual(1024, BytesReceived);

				// ...
				Client.Close();
				Logger::WriteMessage("closed");
			}
			catch (Exception& ex)
			{
				Logger::WriteMessage(ex.GetExceptionMessage().ToCharArray());
				Assert::Fail();
			}
		}
	private:
		// fields
		std::string _Host = "93.184.220.42";
		//std::string _Host = "www.google.com";
		//std::string _Host = "127.0.0.1";
		int _Port = 80;
	};
}