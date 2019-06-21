#include "SocketAddress.hpp"

Elysium::Core::Net::SocketAddress::SocketAddress(Elysium::Core::Net::Sockets::AddressFamily AddressFamily, int Size)
	: _Size(Size <= INT_MAX ? Size : INT_MAX), _Data(Elysium::Core::Collections::Generic::List<byte>(_Size))
{
#ifdef BIGENDIAN
	_Data[0] = (byte)((int)AddressFamily >> 8);
	_Data[1] = (byte)((int)AddressFamily);
#else
	_Data[0] = (byte)((int)AddressFamily);
	_Data[1] = (byte)((int)AddressFamily >> 8);
#endif
}
Elysium::Core::Net::SocketAddress::SocketAddress(Elysium::Core::Net::Sockets::AddressFamily AddressFamily)
	: Elysium::Core::Net::SocketAddress::SocketAddress(AddressFamily, MaxSize)
{
}
Elysium::Core::Net::SocketAddress::~SocketAddress()
{
}

Elysium::Core::Net::Sockets::AddressFamily Elysium::Core::Net::SocketAddress::GetFamily()
{
	int Family;

#ifdef BIGENDIAN
	Family = ((int)_Data[0] << 8) | _Data[1];
#else
	Family = _Data[0] | ((int)_Data[1] << 8);
#endif

	return (Elysium::Core::Net::Sockets::AddressFamily)Family;
}
int Elysium::Core::Net::SocketAddress::GetPort()
{
	int Port;

#ifdef BIGENDIAN
	Port = ((int)_Data[2] << 8) | _Data[3];
#else
	Port = _Data[2] | ((int)_Data[3] << 8);
#endif

	return Port;
}
unsigned int Elysium::Core::Net::SocketAddress::GetSize()
{
	return _Size;
}

Elysium::Core::Net::SocketAddress::SocketAddress()
{
}
