#include "SocketAddress.hpp"

Elysium::Core::Net::SocketAddress::SocketAddress(const Elysium::Core::Net::Sockets::AddressFamily AddressFamily, const Elysium::Core::uint8_t Size)
	: _Size(Size < WriteableOffset ? WriteableOffset : Size)
{
	memset(&_Data[0], 0, _Size);

#ifdef BIGENDIAN
	_Data[0] = static_cast<char>(static_cast<Elysium::Core::uint16_t>(AddressFamily) >> 8);
	_Data[1] = static_cast<char>(AddressFamily);
#else
	_Data[0] = static_cast<char>(AddressFamily);
	_Data[1] = static_cast<char>(static_cast<Elysium::Core::uint16_t>(AddressFamily) >> 8);
#endif
}
Elysium::Core::Net::SocketAddress::SocketAddress(const Elysium::Core::Net::Sockets::AddressFamily AddressFamily)
	: Elysium::Core::Net::SocketAddress::SocketAddress(AddressFamily, MaxSize)
{ }
Elysium::Core::Net::SocketAddress::~SocketAddress()
{ }

const Elysium::Core::Net::Sockets::AddressFamily Elysium::Core::Net::SocketAddress::GetFamily() const
{
	return static_cast<Elysium::Core::Net::Sockets::AddressFamily>(_Data[0] | (_Data[1] << 8));
}
const Elysium::Core::byte & Elysium::Core::Net::SocketAddress::operator[](size_t Index) const
{
	throw 1;
}
const Elysium::Core::uint8_t Elysium::Core::Net::SocketAddress::GetSize() const
{
	return _Size;
}

Elysium::Core::Net::SocketAddress::SocketAddress(const IPAddress & Address)
	: Elysium::Core::Net::SocketAddress::SocketAddress(Address.GetAddressFamily(), 
		Address.GetAddressFamily() == Elysium::Core::Net::Sockets::AddressFamily::InterNetwork ? IPv4AddressSize : IPv6AddressSize)
{
	if (Address.GetAddressFamily() == Elysium::Core::Net::Sockets::AddressFamily::InterNetworkV6)
	{
		// ToDo:
		throw 1;
	}
	else
	{
		_Data[4] = static_cast<char>(Address._Address >> 24);
		_Data[5] = static_cast<char>(Address._Address >> 16);
		_Data[6] = static_cast<char>(Address._Address >> 8);
		_Data[7] = static_cast<char>(Address._Address);
	}
}
Elysium::Core::Net::SocketAddress::SocketAddress(const IPAddress & Address, const Elysium::Core::uint16_t Port)
	: Elysium::Core::Net::SocketAddress::SocketAddress(Address)
{
	_Data[2] = static_cast<char>(Port >> 8);
	_Data[3] = static_cast<char>(Port);
}

