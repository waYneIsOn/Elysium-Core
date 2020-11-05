#include "IPAddress.hpp"

#ifndef ELYSIUM_CORE_STRINGVIEW
#include "../Elysium.Core/StringView.hpp"
#endif

#ifndef ELYSIUM_CORE_CONVERT
#include "../Elysium.Core/Convert.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

Elysium::Core::Net::IPAddress::IPAddress()
	: _Family(Elysium::Core::Net::Sockets::AddressFamily::InterNetwork), _Address(0)
{ }
Elysium::Core::Net::IPAddress::IPAddress(const Elysium::Core::uint32_t Address)
	: _Family(Elysium::Core::Net::Sockets::AddressFamily::InterNetwork), _Address(Address)
{ }
Elysium::Core::Net::IPAddress::~IPAddress()
{ }

const Elysium::Core::Net::Sockets::AddressFamily & Elysium::Core::Net::IPAddress::GetAddressFamily() const
{
	return _Family;
}

const Elysium::Core::Net::IPAddress & Elysium::Core::Net::IPAddress::Any()
{
	static const Elysium::Core::Net::IPAddress Address = Elysium::Core::Net::IPAddress::IPAddress(0);
	return Address;
}

const Elysium::Core::Net::IPAddress & Elysium::Core::Net::IPAddress::Broadcast()
{
	static const Elysium::Core::Net::IPAddress Address = Elysium::Core::Net::IPAddress::IPAddress(0xFFFFFFFF);
	return Address;
}

const Elysium::Core::Net::IPAddress & Elysium::Core::Net::IPAddress::Loopback()
{
	static const Elysium::Core::Net::IPAddress Address = Elysium::Core::Net::IPAddress::IPAddress(0x100007F);
	return Address;
}

const Elysium::Core::Net::IPAddress Elysium::Core::Net::IPAddress::Parse(const Elysium::Core::String & Value)
{
	// ToDo: IPv6, long etc.

	size_t StartIndexIpPart = 0;
	size_t EndIndexIpPart = Value.IndexOf('.', StartIndexIpPart);
	const Elysium::Core::uint8_t IpPart1 = Elysium::Core::Convert::ToInt32(&Value[StartIndexIpPart], 10);

	StartIndexIpPart = EndIndexIpPart + 1;
	EndIndexIpPart = StartIndexIpPart + Value.IndexOf('.', StartIndexIpPart);
	const Elysium::Core::uint8_t IpPart2 = Elysium::Core::Convert::ToInt32(&Value[StartIndexIpPart], 10);

	StartIndexIpPart = EndIndexIpPart + 1;
	EndIndexIpPart = StartIndexIpPart + Value.IndexOf('.', StartIndexIpPart);
	const Elysium::Core::uint8_t IpPart3 = Elysium::Core::Convert::ToInt32(&Value[StartIndexIpPart], 10);

	StartIndexIpPart = EndIndexIpPart + 1;
	EndIndexIpPart = StartIndexIpPart + Value.IndexOf('.', StartIndexIpPart);
	const Elysium::Core::uint8_t IpPart4 = Elysium::Core::Convert::ToInt32(&Value[StartIndexIpPart], 10);

	return IPAddress((IpPart1 << 24) + (IpPart2 << 16) + (IpPart3 << 8) + IpPart4);
}
