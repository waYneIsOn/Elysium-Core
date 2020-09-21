#include "FormatConverter.hpp"

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

Elysium::Core::int32_t Elysium::Core::Net::FormatConverter::Convert(Elysium::Core::Net::Sockets::AddressFamily AddressFamily)
{
	return static_cast<Elysium::Core::int32_t>(AddressFamily);
}
Elysium::Core::int32_t Elysium::Core::Net::FormatConverter::Convert(Elysium::Core::Net::Sockets::ProtocolType ProtocolType)
{
	return static_cast<Elysium::Core::int32_t>(ProtocolType);
}
Elysium::Core::int32_t Elysium::Core::Net::FormatConverter::Convert(Elysium::Core::Net::Sockets::SocketType SocketType)
{
	return static_cast<Elysium::Core::int32_t>(SocketType);
}

Elysium::Core::Net::FormatConverter::FormatConverter()
{ }
Elysium::Core::Net::FormatConverter::~FormatConverter()
{ }
