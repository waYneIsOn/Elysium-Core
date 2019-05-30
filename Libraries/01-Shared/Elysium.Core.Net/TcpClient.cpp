#include "TcpClient.hpp"

Elysium::Core::Net::Sockets::TcpClient::TcpClient()
	: _Socket(Socket::Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp)),
	_Stream(&_Socket, true)
{
}
Elysium::Core::Net::Sockets::TcpClient::~TcpClient()
{
}

Elysium::Core::Net::Sockets::Socket * Elysium::Core::Net::Sockets::TcpClient::GetClient()
{
	return &_Socket;
}
Elysium::Core::Net::Sockets::NetworkStream * Elysium::Core::Net::Sockets::TcpClient::GetStream()
{
	return &_Stream;
}

void Elysium::Core::Net::Sockets::TcpClient::Connect(const string& Host, int Port)
{
	_Socket.Connect(Host, Port);
}
void Elysium::Core::Net::Sockets::TcpClient::Close()
{
	_Socket.Disconnect(true);
}
