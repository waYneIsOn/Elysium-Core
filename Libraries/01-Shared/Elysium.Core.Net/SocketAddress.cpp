#include "SocketAddress.hpp"

#ifndef ELYSIUM_CORE_MATH_MATHHELPER
#include "../Elysium.Core.Math/MathHelper.hpp"
#endif

Elysium::Core::Net::SocketAddress::SocketAddress(Elysium::Core::Net::Sockets::AddressFamily AddressFamily, int Size)
	: //_Size(Elysium::Core::Math::MathHelper::Max((unsigned int)WriteableOffset, Size)),
	_Size(Size), _Buffer(std::vector<byte>(_Size))
{
#ifdef BIGENDIAN
	_Buffer[0] = (byte)((int)AddressFamily >> 8);
	_Buffer[1] = (byte)((int)AddressFamily);
#else
	_Buffer[0] = (byte)((int)AddressFamily);
	_Buffer[1] = (byte)((int)AddressFamily >> 8);
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
	Family = ((int)_Buffer[0] << 8) | _Buffer[1];
#else
	Family = _Buffer[0] | ((int)_Buffer[1] << 8);
#endif

	return (Elysium::Core::Net::Sockets::AddressFamily)Family;
}
unsigned int Elysium::Core::Net::SocketAddress::GetSize()
{
	return _Size;
}
