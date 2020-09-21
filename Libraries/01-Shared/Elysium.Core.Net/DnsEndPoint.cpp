#include "DnsEndPoint.hpp"

#ifndef ELYSIUM_CORE_NET_DNS
#include "Dns.hpp"
#endif

Elysium::Core::Net::DnsEndPoint::DnsEndPoint(const Elysium::Core::String & Host, const Elysium::Core::uint16_t Port, const Sockets::AddressFamily AddressFamily)
	: EndPoint(),
	_Host(Host), _Port(Port), _AddressFamily(AddressFamily)
{ }
Elysium::Core::Net::DnsEndPoint::~DnsEndPoint()
{ }

const Elysium::Core::Net::Sockets::AddressFamily Elysium::Core::Net::DnsEndPoint::GetAddressFamily() const
{
	return _AddressFamily;
}
const Elysium::Core::String & Elysium::Core::Net::DnsEndPoint::GetHost() const
{
	return _Host;
}
const Elysium::Core::uint16_t Elysium::Core::Net::DnsEndPoint::GetPort() const
{
	return _Port;
}

const Elysium::Core::Net::SocketAddress Elysium::Core::Net::DnsEndPoint::Serialize() const
{
	Elysium::Core::Collections::Template::Array<Elysium::Core::Net::IPAddress> _Addresses = Dns::GetHostAddresses(_Host);
	return SocketAddress(_Addresses[0], _Port);
}
