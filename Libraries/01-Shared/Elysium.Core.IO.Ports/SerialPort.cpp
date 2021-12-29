#include "SerialPort.hpp"

Elysium::Core::IO::Ports::SerialPort::SerialPort(const Elysium::Core::Utf8String & PortName, const Elysium::Core::uint32_t BaudRate, const Elysium::Core::IO::Ports::Parity Parity, const Elysium::Core::uint32_t DataBits, const Elysium::Core::IO::Ports::StopBits StopBits)
{ }
Elysium::Core::IO::Ports::SerialPort::~SerialPort()
{ }

const Elysium::Core::Collections::Template::Array<Elysium::Core::Utf8String> Elysium::Core::IO::Ports::SerialPort::GetPortNames()
{
	return Elysium::Core::Collections::Template::Array<Elysium::Core::Utf8String>(0);
}
