#include "Dns.hpp"

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
#endif

#ifndef _WS2TCPIP_H_
#include <Ws2tcpip.h>	// InetPton
#endif

#ifndef ELYSIUM_CORE_BITCONVERTER
#include "../Elysium.Core/BitConverter.hpp"
#endif

const Elysium::Core::Collections::Template::Array<Elysium::Core::Net::IPAddress> Elysium::Core::Net::Dns::GetHostAddresses(const Elysium::Core::String & HostNameOrAddress)
{
	const Text::Encoding& WindowsEncoding = Text::Encoding::UTF16LE();
	Collections::Template::Array<Elysium::Core::byte> Bytes = WindowsEncoding.GetBytes(&HostNameOrAddress[0], HostNameOrAddress.GetLength(), sizeof(char16_t));

	addrinfoW ServerInfo = {}, *Addresses;
	if (GetAddrInfo((const wchar_t*)&Bytes[0], NULL, &ServerInfo, &Addresses) != 0)
	{	// ToDo: throw a specific exception
		throw Exception(u8"couldn't get ip from host.\r\n");
	}

	Elysium::Core::int32_t Count = 0;
	for (addrinfoW* Item = Addresses; Item != NULL; Item = Item->ai_next)
	{
		Count++;
	}

	Elysium::Core::Collections::Template::Array<Elysium::Core::Net::IPAddress> Result = Elysium::Core::Collections::Template::Array<Elysium::Core::Net::IPAddress>(Count);
	for (Elysium::Core::int32_t i = 0; i < Count; i++)
	{
		switch (Addresses[i].ai_family)
		{
		case AF_INET:
			Result[i] = Elysium::Core::Net::IPAddress::IPAddress(BitConverter::ToUInt32((Elysium::Core::byte*)&Addresses[i].ai_addr->sa_data[2]));
			break;
		case AF_INET6:
			// ToDo:
			Result[i] = Elysium::Core::Net::IPAddress::IPAddress();
			break;
		default:
			// ToDo:
			Result[i] = Elysium::Core::Net::IPAddress::IPAddress();
			break;
		}
	}

	return Result;
}

const Elysium::Core::String Elysium::Core::Net::Dns::GetHostName()
{
	throw 1;
}
