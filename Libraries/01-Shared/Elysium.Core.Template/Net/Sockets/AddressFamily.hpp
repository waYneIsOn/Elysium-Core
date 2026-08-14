/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_ADDRESSFAMILY
#define ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_ADDRESSFAMILY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Net::Sockets
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class AddressFamily
		: Elysium::Core::Template::System::uint16_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class AddressFamily
#else
#error "undefined os"
#endif
	{
		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_UNSPEC (under windows)
		/// - ... (under linux)
		/// </summary>
		Unspecified = 0,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_UNIX (under windows)
		/// - ... (under linux)
		/// </summary>
		Unix = 1,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_INET (under windows)
		/// - ... (under linux)
		/// </summary>
		InterNetwork = 2,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_IMPLINK (under windows)
		/// - ... (under linux)
		/// </summary>
		ImpLink = 3,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_PUP (under windows)
		/// - ... (under linux)
		/// </summary>
		Pup = 4,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_CHAOS (under windows)
		/// - ... (under linux)
		/// </summary>
		Chaos = 5,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_NS (under windows)
		/// - ... (under linux)
		/// </summary>
		NS = 6,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_IPX (under windows)
		/// - ... (under linux)
		/// </summary>
		Ipx = NS,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_ISO (under windows)
		/// - ... (under linux)
		/// </summary>
		Iso = 7,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_OSI (under windows)
		/// - ... (under linux)
		/// </summary>
		Osi = Iso,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_ECMA (under windows)
		/// - ... (under linux)
		/// </summary>
		Ecma = 8,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_DATAKIT (under windows)
		/// - ... (under linux)
		/// </summary>
		DataKit = 9,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_CCITT (under windows)
		/// - ... (under linux)
		/// </summary>
		Ccitt = 10,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_SNA (under windows)
		/// - ... (under linux)
		/// </summary>
		Sna = 11,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_DECnet (under windows)
		/// - ... (under linux)
		/// </summary>
		DecNet = 12,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_DLI (under windows)
		/// - ... (under linux)
		/// </summary>
		DataLink = 13,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_LAT (under windows)
		/// - ... (under linux)
		/// </summary>
		Lat = 14,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_HYLINK (under windows)
		/// - ... (under linux)
		/// </summary>
		HyperChannel = 15,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_APPLETALK (under windows)
		/// - ... (under linux)
		/// </summary>
		AppleTalk = 16,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_NETBIOS (under windows)
		/// - ... (under linux)
		/// </summary>
		NetBios = 17,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_VOICEVIEW (under windows)
		/// - ... (under linux)
		/// </summary>
		VoiceView = 18,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_FIREFOX (under windows)
		/// - ... (under linux)
		/// </summary>
		FireFox = 19,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_UNKNOWN1 (under windows)
		/// - ... (under linux)
		/// </summary>
		Unknown1 = 20,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_BAN (under windows)
		/// - ... (under linux)
		/// </summary>
		Banyan = 21,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_ATM (under windows)
		/// - ... (under linux)
		/// </summary>
		Atm = 22,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_INET6 (under windows)
		/// - ... (under linux)
		/// </summary>
		InterNetworkV6 = 23,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_CLUSTER (under windows)
		/// - ... (under linux)
		/// </summary>
		Cluster = 24,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_12844 (under windows)
		/// - ... (under linux)
		/// </summary>
		Ieee12844 = 25,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_IRDA (under windows)
		/// - ... (under linux)
		/// </summary>
		AtmIrda = 26,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_NETDES (under windows)
		/// - ... (under linux)
		/// </summary>
		NetworkDesigners = 28,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_TCNPROCESS (under windows)
		/// - ... (under linux)
		/// </summary>
		TCNPROCESS = 29,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_TCNMESSAGE (under windows)
		/// - ... (under linux)
		/// </summary>
		TCNMESSAGE = 30,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_ICLFXBM (under windows)
		/// - ... (under linux)
		/// </summary>
		ICLFXBM = 31,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_BTH (under windows)
		/// - ... (under linux)
		/// </summary>
		Bluetooth = 32,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_LINK (under windows)
		/// - ... (under linux)
		/// </summary>
		LINK = 33,

		/// <summary>
		/// 
		/// 
		/// Equals:
		/// - AF_HYPERV (under windows)
		/// - ... (under linux)
		/// </summary>
		HYPERV = 34,

		Packet = 65536,
		ControllerAreaNetwork = 65537
	};
}
#endif
