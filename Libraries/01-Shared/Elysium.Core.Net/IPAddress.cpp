#include "IPAddress.hpp"

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

Elysium::Core::Net::IPAddress Elysium::Core::Net::IPAddress::_Any = Elysium::Core::Net::IPAddress::IPAddress(0);

Elysium::Core::Net::IPAddress::IPAddress(const byte * Address, size_t AddressSize)
{

}
Elysium::Core::Net::IPAddress::IPAddress(const unsigned __int64 NewAddress)
{
	//Elysium::Core::Net::Sockets::AddressFamily::Unspecified

	//64.233.187.99
	//64 * 2 ^ 24 + 233 * 2 ^ 16 + 187 * 2 ^ 8 + 99 = 1089059683
}
Elysium::Core::Net::IPAddress::~IPAddress()
{
}

const Elysium::Core::Net::IPAddress & Elysium::Core::Net::IPAddress::Any()
{
	return _Any;
}

Elysium::Core::Net::Sockets::AddressFamily Elysium::Core::Net::IPAddress::GetAddressFamily() const
{
	int Family;

#ifdef BIGENDIAN
	Family = ((int)_Data[0] << 8) | _Data[1];
#else
	Family = _Data[0] | ((int)_Data[1] << 8);
#endif

	return (Elysium::Core::Net::Sockets::AddressFamily)Family;
}
