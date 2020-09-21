#include "IPEndPoint.hpp"

Elysium::Core::Net::IPEndPoint::IPEndPoint(const IPAddress & Address, const Elysium::Core::uint16_t Port)
	: EndPoint(),
	_Address(Address), _Port(Port)
{ }
Elysium::Core::Net::IPEndPoint::~IPEndPoint()
{ }

const Elysium::Core::Net::Sockets::AddressFamily Elysium::Core::Net::IPEndPoint::GetAddressFamily() const
{
	return _Address.GetAddressFamily();
}
const int Elysium::Core::Net::IPEndPoint::GetPort() const
{
	return _Port;
}

const Elysium::Core::Net::SocketAddress Elysium::Core::Net::IPEndPoint::Serialize() const
{
	return SocketAddress(_Address, _Port);
}
