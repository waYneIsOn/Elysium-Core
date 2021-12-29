#include "ProcessStartInfo.hpp"

Elysium::Core::Diagnostics::ProcessStartInfo::ProcessStartInfo()
	: ProcessStartInfo(u8"", u8"")
{ }

Elysium::Core::Diagnostics::ProcessStartInfo::ProcessStartInfo(const Elysium::Core::Utf8String& FileName)
	: ProcessStartInfo(FileName, u8"")
{ }

Elysium::Core::Diagnostics::ProcessStartInfo::ProcessStartInfo(const Elysium::Core::Utf8String& FileName, const Elysium::Core::Utf8String& Arguments)
	: _FileName(FileName), _Arguments(Arguments), _WindowStyle(ProcessWindowStyle::Normal)
{ }

Elysium::Core::Diagnostics::ProcessStartInfo::~ProcessStartInfo()
{ }

const Elysium::Core::Utf8String& Elysium::Core::Diagnostics::ProcessStartInfo::GetArguments() const
{
	return _Arguments;
}

const Elysium::Core::Utf8String& Elysium::Core::Diagnostics::ProcessStartInfo::GetFileName() const
{
	return _FileName;
}

const Elysium::Core::Diagnostics::ProcessWindowStyle Elysium::Core::Diagnostics::ProcessStartInfo::GetWindowStyle() const
{
	return _WindowStyle;
}

void Elysium::Core::Diagnostics::ProcessStartInfo::SetArguments(const Elysium::Core::Utf8String& Value)
{
	_Arguments = Value;
}

void Elysium::Core::Diagnostics::ProcessStartInfo::SetFileName(const Elysium::Core::Utf8String& Value)
{
	_FileName = Value;
}

void Elysium::Core::Diagnostics::ProcessStartInfo::SetWindowStyle(const ProcessWindowStyle Value)
{
	_WindowStyle = Value;
}
