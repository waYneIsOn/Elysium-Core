/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_PORTS_SERIALPORT
#define ELYSIUM_CORE_IO_PORTS_SERIALPORT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_IO_PORTS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_PORTS_PARITY
#include "Parity.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_PORTS_STOPBITS
#include "StopBits.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../Elysium.Core/Array.hpp"
#endif

namespace Elysium::Core::IO::Ports
{
	class ELYSIUM_CORE_IO_PORTS_API SerialPort final
	{
	public:
		SerialPort(const Elysium::Core::Utf8String& PortName, const Elysium::Core::uint32_t BaudRate, const Elysium::Core::IO::Ports::Parity Parity, 
			const Elysium::Core::uint32_t DataBits, const Elysium::Core::IO::Ports::StopBits StopBits);
		SerialPort(const SerialPort& Source) = delete;
		SerialPort(SerialPort&& Right) = delete;
		~SerialPort();

		SerialPort& operator=(const SerialPort& Source) = delete;
		SerialPort& operator=(SerialPort&& Right) noexcept = delete;

		static const Elysium::Core::uint32_t InfiniteTimeout = -1;

		const Elysium::Core::Collections::Template::Array<Elysium::Core::Utf8String> GetPortNames();
	};
}
#endif
