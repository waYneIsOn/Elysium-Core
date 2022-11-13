#include "IPAddress.hpp"

#ifndef ELYSIUM_CORE_STRINGVIEW
#include "../Elysium.Core/StringView.hpp"
#endif

#ifndef ELYSIUM_CORE_OBJECT
#include "../Elysium.Core/Object.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CONVERT
#include "../Elysium.Core.Template/Convert.hpp"
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

const Elysium::Core::Net::IPAddress Elysium::Core::Net::IPAddress::Parse(const Elysium::Core::Utf8String & Value)
{
	// ToDo: IPv6, long etc.

	Elysium::Core::size StartIndexIpPart = 0;
	Elysium::Core::size EndIndexIpPart = Value.IndexOf('.', StartIndexIpPart);
	const Elysium::Core::uint8_t IpPart1 = Elysium::Core::Template::Text::Convert<char8_t>::ToInt32(&Value[StartIndexIpPart], EndIndexIpPart - StartIndexIpPart, 10);

	StartIndexIpPart = EndIndexIpPart + 1;
	EndIndexIpPart = StartIndexIpPart + Value.IndexOf('.', StartIndexIpPart);
	const Elysium::Core::uint8_t IpPart2 = Elysium::Core::Template::Text::Convert<char8_t>::ToInt32(&Value[StartIndexIpPart], EndIndexIpPart - StartIndexIpPart, 10);

	StartIndexIpPart = EndIndexIpPart + 1;
	EndIndexIpPart = StartIndexIpPart + Value.IndexOf('.', StartIndexIpPart);
	const Elysium::Core::uint8_t IpPart3 = Elysium::Core::Template::Text::Convert<char8_t>::ToInt32(&Value[StartIndexIpPart], EndIndexIpPart - StartIndexIpPart, 10);

	StartIndexIpPart = EndIndexIpPart + 1;
	EndIndexIpPart = StartIndexIpPart + Value.IndexOf('.', StartIndexIpPart);
	const Elysium::Core::uint8_t IpPart4 = Elysium::Core::Template::Text::Convert<char8_t>::ToInt32(&Value[StartIndexIpPart], EndIndexIpPart - StartIndexIpPart, 10);

	return IPAddress((IpPart1 << 24) + (IpPart2 << 16) + (IpPart3 << 8) + IpPart4);
}

const Elysium::Core::Utf8String Elysium::Core::Net::IPAddress::ToString() const
{	// ToDo
	throw 1;
	/*
	Elysium::Core::byte* Data = (Elysium::Core::byte*)&_Address;

	Elysium::Core::uint8_t b1 = Data[0];
	Elysium::Core::uint8_t b2 = Data[1];
	Elysium::Core::uint8_t b3 = Data[2];
	Elysium::Core::uint8_t b4 = Data[3];
	
	switch (_Family)
	{
	case Elysium::Core::Net::Sockets::AddressFamily::InterNetwork:
		return Elysium::Core::Utf8String();
	case Elysium::Core::Net::Sockets::AddressFamily::InterNetworkV6:
		return Elysium::Core::Utf8String();
	default:
		return Elysium::Core::Utf8String();
	}
	*/
}
