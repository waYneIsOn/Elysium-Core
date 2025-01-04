#include "SerialPort.hpp"

Elysium::Core::IO::Ports::SerialPort::SerialPort(const Elysium::Core::Utf8String & PortName, const Elysium::Core::uint32_t BaudRate, const Elysium::Core::IO::Ports::Parity Parity, const Elysium::Core::uint32_t DataBits, const Elysium::Core::IO::Ports::StopBits StopBits)
{ }

Elysium::Core::IO::Ports::SerialPort::~SerialPort()
{ }

const Elysium::Core::Container::VectorOfUtf8String Elysium::Core::IO::Ports::SerialPort::GetPortNames()
{
	return Elysium::Core::Container::VectorOfUtf8String(0);
}
