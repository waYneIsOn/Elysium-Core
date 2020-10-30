#include "FormatConverter.hpp"

const Elysium::Core::int32_t Elysium::Core::Net::FormatConverter::Convert(Elysium::Core::Net::Sockets::AddressFamily AddressFamily)
{
	return static_cast<Elysium::Core::int32_t>(AddressFamily);
}
const Elysium::Core::int32_t Elysium::Core::Net::FormatConverter::Convert(Elysium::Core::Net::Sockets::ProtocolType ProtocolType)
{
	return static_cast<Elysium::Core::int32_t>(ProtocolType);
}
const Elysium::Core::int32_t Elysium::Core::Net::FormatConverter::Convert(Elysium::Core::Net::Sockets::SocketType SocketType)
{
	return static_cast<Elysium::Core::int32_t>(SocketType);
}

const Elysium::Core::int32_t Elysium::Core::Net::FormatConverter::Convert(Elysium::Core::Net::NetworkInformation::GetAdaptersAddressesFlags GetAdaptersAddressesFlags)
{
	return static_cast<Elysium::Core::int32_t>(GetAdaptersAddressesFlags);
}

Elysium::Core::Net::FormatConverter::FormatConverter()
{ }
Elysium::Core::Net::FormatConverter::~FormatConverter()
{ }
