#include "IPEndPoint.hpp"

Elysium::Core::Net::IPEndPoint::IPEndPoint(const IPAddress & Address, const int Port)
	: EndPoint(Address),
	_Port(Port)
{
}
Elysium::Core::Net::IPEndPoint::~IPEndPoint()
{
}

const Elysium::Core::Net::IPAddress & Elysium::Core::Net::IPEndPoint::GetAddress() const
{
	return _Address;
}
const int Elysium::Core::Net::IPEndPoint::GetPort() const
{
	return _Port;
}

void Elysium::Core::Net::IPEndPoint::Serialize(SocketAddress * Address) const
{
	// byte 0 & 1: address family
	// byte 2 & 3: port
	// byte rest: ip address

	//*Address = SocketAddress(GetAddressFamily())
}
