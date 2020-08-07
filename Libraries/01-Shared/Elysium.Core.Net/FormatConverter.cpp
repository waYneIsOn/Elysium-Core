#include "FormatConverter.hpp"

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

int Elysium::Core::Net::FormatConverter::Convert(Elysium::Core::Net::Sockets::AddressFamily AddressFamily)
{
	switch (AddressFamily)
	{
		/*
	case Elysium::Core::Net::Sockets::AddressFamily::AppleTalk:
		throw exception("not implemented");
	case Elysium::Core::Net::Sockets::AddressFamily::Atm:
		throw exception("not implemented");
	case Elysium::Core::Net::Sockets::AddressFamily::Banyan:
		throw exception("not implemented");
	case Elysium::Core::Net::Sockets::AddressFamily::Ccitt:
		throw exception("not implemented");
	case Elysium::Core::Net::Sockets::AddressFamily::Chaos:
		throw exception("not implemented");
	case Elysium::Core::Net::Sockets::AddressFamily::Cluster:
		throw exception("not implemented");
	case Elysium::Core::Net::Sockets::AddressFamily::DataKit:
		throw exception("not implemented");
	case Elysium::Core::Net::Sockets::AddressFamily::DataLink:
		throw exception("not implemented");
	case Elysium::Core::Net::Sockets::AddressFamily::DecNet:
		throw exception("not implemented");
	case Elysium::Core::Net::Sockets::AddressFamily::Ecma:
		throw exception("not implemented");
	case Elysium::Core::Net::Sockets::AddressFamily::FireFox:
		throw exception("not implemented");
	case Elysium::Core::Net::Sockets::AddressFamily::HyperChannel:
		throw exception("not implemented");
	case Elysium::Core::Net::Sockets::AddressFamily::Ieee12844:
		throw exception("not implemented");
	case Elysium::Core::Net::Sockets::AddressFamily::ImpLink:
		throw exception("not implemented");
		*/
	case Elysium::Core::Net::Sockets::AddressFamily::InterNetwork:
		return AF_INET;
		/*
	case Elysium::Core::Net::Sockets::AddressFamily::InterNetworkV6:
		throw exception("not implemented");
	case Elysium::Core::Net::Sockets::AddressFamily::Ipx:
		throw exception("not implemented");
	case Elysium::Core::Net::Sockets::AddressFamily::AtmIrda:
		throw exception("not implemented");
	case Elysium::Core::Net::Sockets::AddressFamily::Iso:
		throw exception("not implemented");
	case Elysium::Core::Net::Sockets::AddressFamily::Lat:
		throw exception("not implemented");
	case Elysium::Core::Net::Sockets::AddressFamily::Max:
		throw exception("not implemented");
	case Elysium::Core::Net::Sockets::AddressFamily::NetBios:
		throw exception("not implemented");
	case Elysium::Core::Net::Sockets::AddressFamily::NetworkDesigners:
		throw exception("not implemented");
	case Elysium::Core::Net::Sockets::AddressFamily::NS:
		throw exception("not implemented");
	case Elysium::Core::Net::Sockets::AddressFamily::Osi:
		throw exception("not implemented");
	case Elysium::Core::Net::Sockets::AddressFamily::Pup:
		throw exception("not implemented");
	case Elysium::Core::Net::Sockets::AddressFamily::Sna:
		throw exception("not implemented");
	case Elysium::Core::Net::Sockets::AddressFamily::Unix:
		throw exception("not implemented");
	case Elysium::Core::Net::Sockets::AddressFamily::Unknown:
		throw exception("not implemented");
	case Elysium::Core::Net::Sockets::AddressFamily::Unspecified:
		throw exception("not implemented");
	case Elysium::Core::Net::Sockets::AddressFamily::VoiceView:
		throw exception("not implemented");
	*/
	default:
		throw NotImplementedException(u8"unknown address family");
	}
}
int Elysium::Core::Net::FormatConverter::Convert(Elysium::Core::Net::Sockets::ProtocolType ProtocolType)
{
	switch (ProtocolType)
	{
		/*
	case Elysium::Core::Net::Sockets::ProtocolType::Ggp:
		throw std::exception("not implemented");
	case Elysium::Core::Net::Sockets::ProtocolType::Icmp:
		throw std::exception("not implemented");
	case Elysium::Core::Net::Sockets::ProtocolType::IcmpV6:
		throw std::exception("not implemented");
	case Elysium::Core::Net::Sockets::ProtocolType::Idp:
		throw std::exception("not implemented");
	case Elysium::Core::Net::Sockets::ProtocolType::Igmp:
		throw std::exception("not implemented");
	case Elysium::Core::Net::Sockets::ProtocolType::IP:
		throw std::exception("not implemented");
	case Elysium::Core::Net::Sockets::ProtocolType::IPSecAuthenticationHeader:
		throw std::exception("not implemented");
	case Elysium::Core::Net::Sockets::ProtocolType::IPSecEncapsulatingSecurityPayload:
		throw std::exception("not implemented");
	case Elysium::Core::Net::Sockets::ProtocolType::IPv4:
		throw std::exception("not implemented");
	case Elysium::Core::Net::Sockets::ProtocolType::IPv6:
		throw std::exception("not implemented");
	case Elysium::Core::Net::Sockets::ProtocolType::IPv6DestinationOptions:
		throw std::exception("not implemented");
	case Elysium::Core::Net::Sockets::ProtocolType::IPv6FragmentHeader:
		throw std::exception("not implemented");
	case Elysium::Core::Net::Sockets::ProtocolType::IPv6HopByHopOptions:
		throw std::exception("not implemented");
	case Elysium::Core::Net::Sockets::ProtocolType::IPv6NoNextHeader:
		throw std::exception("not implemented");
	case Elysium::Core::Net::Sockets::ProtocolType::IPv6RoutingHeader:
		throw std::exception("not implemented");
	case Elysium::Core::Net::Sockets::ProtocolType::Ipx:
		throw std::exception("not implemented");
	case Elysium::Core::Net::Sockets::ProtocolType::ND:
		throw std::exception("not implemented");
	case Elysium::Core::Net::Sockets::ProtocolType::Pup:
		throw std::exception("not implemented");
	case Elysium::Core::Net::Sockets::ProtocolType::Raw:
		throw std::exception("not implemented");
	case Elysium::Core::Net::Sockets::ProtocolType::Spx:
		throw std::exception("not implemented");
	case Elysium::Core::Net::Sockets::ProtocolType::SpxII:
		throw std::exception("not implemented");
		*/
	case Elysium::Core::Net::Sockets::ProtocolType::Tcp:
		return IPPROTO_TCP;
		/*
	case Elysium::Core::Net::Sockets::ProtocolType::Udp:
		throw std::exception("not implemented");
	case Elysium::Core::Net::Sockets::ProtocolType::Unknown:
		throw std::exception("not implemented");
	case Elysium::Core::Net::Sockets::ProtocolType::Unspecified:
		throw std::exception("not implemented");
		*/
	default:
		throw NotImplementedException(u8"unknown protocol type");
	}
}
int Elysium::Core::Net::FormatConverter::Convert(Elysium::Core::Net::Sockets::SocketType SocketType)
{
	switch (SocketType)
	{
		/*
	case Elysium::Core::Net::Sockets::SocketType::Dgram:
		throw std::exception("not implemented");
	case Elysium::Core::Net::Sockets::SocketType::Raw:
		throw std::exception("not implemented");
	case Elysium::Core::Net::Sockets::SocketType::Rdm:
		throw std::exception("not implemented");
	case Elysium::Core::Net::Sockets::SocketType::Seqpacket:
		throw std::exception("not implemented");
		*/
	case Elysium::Core::Net::Sockets::SocketType::Stream:
		return SOCK_STREAM;
		/*
	case Elysium::Core::Net::Sockets::SocketType::Unknown:
		throw std::exception("not implemented");
		*/
	default:
		throw NotImplementedException(u8"unknown socket type");
	}
}

Elysium::Core::Net::Sockets::AddressFamily Elysium::Core::Net::FormatConverter::Convert(ADDRESS_FAMILY WinAddressFamily)
{
	switch (WinAddressFamily)
	{
	case AF_INET:
		return Elysium::Core::Net::Sockets::AddressFamily::InterNetwork;
		break;
	default:
		throw NotImplementedException(u8"unknown windows address family");
	}
}

Elysium::Core::Net::FormatConverter::FormatConverter()
{
}
Elysium::Core::Net::FormatConverter::~FormatConverter()
{
}
