#include "NetworkInterface.hpp"

#ifndef ELYSIUM_CORE_NET_SOCKETS_ADDRESSFAMILY
#include "AddressFamily.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_NETWORKINFORMATION_GETADAPTERSADDRESSESFLAGS
#include "GetAdaptersAddressesFlags.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_FORMATCONVERTER
#include "FormatConverter.hpp"
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
#ifndef _WINSOCK2API_
#include <WinSock2.h>
#endif

#ifndef __IPHLPAPI_H__
#include <iphlpapi.h>
#endif
#elif defined(__ANDROID__)

#else
#error "undefined os"
#endif

#ifndef ELYSIUM_CORE_NET_NETWORKINFORMATION_NETWORKINFORMATIONEXCEPTION
#include "NetworkInformationException.hpp"
#endif

Elysium::Core::Net::NetworkInformation::NetworkInterface::~NetworkInterface()
{ }

const Elysium::Core::Collections::Template::Array<Elysium::Core::Net::NetworkInformation::NetworkInterface> Elysium::Core::Net::NetworkInformation::NetworkInterface::GetAllNetworkInterfaces()
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	Sockets::AddressFamily Family = Sockets::AddressFamily::Unspecified;
	GetAdaptersAddressesFlags Flags = GetAdaptersAddressesFlags::IncludeGateways | GetAdaptersAddressesFlags::IncludeWins;

	unsigned long BufferSize = 0;
	unsigned long Result;
	if (Result = GetAdaptersAddresses(FormatConverter::Convert(Family), FormatConverter::Convert(Flags), nullptr, nullptr, &BufferSize) != ERROR_BUFFER_OVERFLOW)
	{
		throw NetworkInformationException(WSAGetLastError());
	}

	PIP_ADAPTER_ADDRESSES AdapterAddresses;
	do
	{
		AdapterAddresses = (PIP_ADAPTER_ADDRESSES)malloc(BufferSize);
		Result = GetAdaptersAddresses(FormatConverter::Convert(Family), FormatConverter::Convert(Flags), nullptr, AdapterAddresses, &BufferSize);

		if (Result == ERROR_BUFFER_OVERFLOW)
		{
			free(AdapterAddresses);
			AdapterAddresses = nullptr;
			throw NetworkInformationException(WSAGetLastError());
		}
		else
		{
			break;
		}
	} while (Result == ERROR_BUFFER_OVERFLOW);

	if (Result == NO_ERROR)
	{
		PIP_ADAPTER_ADDRESSES CurrentAdapterAddress = AdapterAddresses;
		int NumberOfNetworkInterfaces = 0;
		while (CurrentAdapterAddress)
		{
			CurrentAdapterAddress = CurrentAdapterAddress->Next;
			NumberOfNetworkInterfaces++;
		}

		Elysium::Core::Collections::Template::Array<Elysium::Core::Net::NetworkInformation::NetworkInterface> NetworkInterfaces =
			Elysium::Core::Collections::Template::Array<Elysium::Core::Net::NetworkInformation::NetworkInterface>(NumberOfNetworkInterfaces);

		CurrentAdapterAddress = AdapterAddresses;
		NumberOfNetworkInterfaces = 0;
		while (CurrentAdapterAddress)
		{
			// ToDo: wchar_t -> char8_t
			//NetworkInterfaces[NumberOfNetworkInterfaces]._Id = CurrentAdapterAddress->AdapterName;
			NetworkInterfaces[NumberOfNetworkInterfaces]._Type = static_cast<NetworkInterfaceType>(CurrentAdapterAddress->IfType);
			NetworkInterfaces[NumberOfNetworkInterfaces]._Status = static_cast<OperationalStatus>(CurrentAdapterAddress->OperStatus);
			NetworkInterfaces[NumberOfNetworkInterfaces]._Speed = CurrentAdapterAddress->ReceiveLinkSpeed;
			NetworkInterfaces[NumberOfNetworkInterfaces]._IsReceiveOnly = CurrentAdapterAddress->ReceiveOnly == 1;
			NetworkInterfaces[NumberOfNetworkInterfaces]._SupportsMulticast = CurrentAdapterAddress->NoMulticast != 1;

			NetworkInterfaces[NumberOfNetworkInterfaces]._LoopbackInterfaceIndex = CurrentAdapterAddress->IfIndex;
			NetworkInterfaces[NumberOfNetworkInterfaces]._IPv6LoopbackInterfaceIndex = CurrentAdapterAddress->Ipv6IfIndex;

			// ToDo: just interpreting wchar_t as char is obviously bs
			//NetworkInterfaces[NumberOfNetworkInterfaces]._Name = (char*)CurrentAdapterAddress->FriendlyName;
			//NetworkInterfaces[NumberOfNetworkInterfaces]._Description = (char*)CurrentAdapterAddress->Description;

			//CurrentAdapterAddress->PhysicalAddress
			//CurrentAdapterAddress->PhysicalAddressLength

			//CurrentAdapterAddress->Alignment
			//CurrentAdapterAddress->CompartmentId
			//CurrentAdapterAddress->ConnectionType
			//CurrentAdapterAddress->DdnsEnabled
			//CurrentAdapterAddress->Dhcpv4Enabled
			//CurrentAdapterAddress->Dhcpv4Server
			//CurrentAdapterAddress->Dhcpv6ClientDuid
			//CurrentAdapterAddress->Dhcpv6ClientDuidLength
			//CurrentAdapterAddress->Dhcpv6Iaid
			//CurrentAdapterAddress->Dhcpv6Server
			//CurrentAdapterAddress->DnsSuffix
			//CurrentAdapterAddress->FirstAnycastAddress
			//CurrentAdapterAddress->FirstDnsServerAddress
			//CurrentAdapterAddress->FirstDnsSuffix
			//CurrentAdapterAddress->FirstGatewayAddress
			//CurrentAdapterAddress->FirstMulticastAddress
			//CurrentAdapterAddress->FirstPrefix
			//CurrentAdapterAddress->FirstUnicastAddress
			//CurrentAdapterAddress->FirstWinsServerAddress
			//CurrentAdapterAddress->Flags
			//CurrentAdapterAddress->Ipv4Enabled
			//CurrentAdapterAddress->Ipv4Metric
			//CurrentAdapterAddress->Ipv6Enabled
			//CurrentAdapterAddress->Ipv6ManagedAddressConfigurationSupported
			//CurrentAdapterAddress->Ipv6OtherStatefulConfig
			//CurrentAdapterAddress->Length
			//CurrentAdapterAddress->Luid
			//CurrentAdapterAddress->Mtu
			//CurrentAdapterAddress->NetbiosOverTcpipEnabled
			//CurrentAdapterAddress->NetworkGuid
			//CurrentAdapterAddress->RegisterAdapterSuffix
			//CurrentAdapterAddress->TransmitLinkSpeed
			//CurrentAdapterAddress->TunnelType
			//CurrentAdapterAddress->ZoneIndices

			CurrentAdapterAddress = CurrentAdapterAddress->Next;
			NumberOfNetworkInterfaces++;
		}

		if (AdapterAddresses)
		{
			free(AdapterAddresses);
			AdapterAddresses = nullptr;
		}

		return NetworkInterfaces;
	}
	else
	{
		if (AdapterAddresses)
		{
			free(AdapterAddresses);
			AdapterAddresses = nullptr;
		}

		return Elysium::Core::Collections::Template::Array<Elysium::Core::Net::NetworkInformation::NetworkInterface>(0);
	}
#else
#error "undefined os"
#endif
}

const Elysium::Core::Utf8String & Elysium::Core::Net::NetworkInformation::NetworkInterface::GetId() const
{
	return _Id;
}

const Elysium::Core::Utf8String & Elysium::Core::Net::NetworkInformation::NetworkInterface::GetName() const
{
	return _Name;
}

const Elysium::Core::Utf8String & Elysium::Core::Net::NetworkInformation::NetworkInterface::GetDescription() const
{
	return _Description;
}

const Elysium::Core::Net::NetworkInformation::NetworkInterfaceType & Elysium::Core::Net::NetworkInformation::NetworkInterface::GetNetworkInterfaceType() const
{
	return _Type;
}

const Elysium::Core::Net::NetworkInformation::OperationalStatus & Elysium::Core::Net::NetworkInformation::NetworkInterface::GetOperationalStatus() const
{
	return _Status;
}

const Elysium::Core::int64_t Elysium::Core::Net::NetworkInformation::NetworkInterface::GetSpeed() const
{
	return _Speed;
}

Elysium::Core::Net::NetworkInformation::NetworkInterface::NetworkInterface()
	: _Id(Elysium::Core::Utf8String()), _Name(Elysium::Core::Utf8String()), _Description(Elysium::Core::Utf8String())
{ }
