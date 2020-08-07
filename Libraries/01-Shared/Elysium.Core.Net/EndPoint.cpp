#include "EndPoint.hpp"

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

Elysium::Core::Net::EndPoint::~EndPoint()
{
}

Elysium::Core::Net::Sockets::AddressFamily Elysium::Core::Net::EndPoint::GetAddressFamily() const
{
	return _Address.GetAddressFamily();
}

void Elysium::Core::Net::EndPoint::Create(Elysium::Core::Net::SocketAddress * Address, Elysium::Core::Net::EndPoint * EndPoint)
{
	throw NotImplementedException(u8"void Elysium::Core::Net::EndPoint::Create");
}
Elysium::Core::Net::EndPoint * Elysium::Core::Net::EndPoint::Create(Elysium::Core::Net::SocketAddress * Address)
{
	throw NotImplementedException(u8"Elysium::Core::Net::EndPoint * Elysium::Core::Net::EndPoint::Create");
}

Elysium::Core::Net::EndPoint::EndPoint(const IPAddress& Address)
	: _Address(Address)
{
}
