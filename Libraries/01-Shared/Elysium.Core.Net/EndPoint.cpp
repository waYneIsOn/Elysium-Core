#include "EndPoint.hpp"

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

Elysium::Core::Net::Sockets::AddressFamily Elysium::Core::Net::EndPoint::GetAddressFamily() const
{
	return _AddressFamily;
}

void Elysium::Core::Net::EndPoint::Create(Elysium::Core::Net::SocketAddress * Address, Elysium::Core::Net::EndPoint * EndPoint)
{
	throw NotImplementedException("void Elysium::Core::Net::EndPoint::Create");
}
Elysium::Core::Net::EndPoint * Elysium::Core::Net::EndPoint::Create(Elysium::Core::Net::SocketAddress * Address)
{
	throw NotImplementedException("Elysium::Core::Net::EndPoint * Elysium::Core::Net::EndPoint::Create");
}

Elysium::Core::Net::EndPoint::EndPoint()
	: _AddressFamily(Elysium::Core::Net::Sockets::AddressFamily::Unspecified)
{
}
