#include "AuthenticatedStream.hpp"

Elysium::Core::Net::Security::AuthenticatedStream::AuthenticatedStream(Elysium::Core::IO::Stream& InnerStream, const bool LeaveInnerStreamOpen)
	: _InnerStream(InnerStream), _LeaveInnerStreamOpen(LeaveInnerStreamOpen)
{ }

Elysium::Core::Net::Security::AuthenticatedStream::~AuthenticatedStream()
{
	if (!_LeaveInnerStreamOpen)
	{
		_InnerStream.Close();
	}
}

const Elysium::Core::IO::Stream & Elysium::Core::Net::Security::AuthenticatedStream::GetInnerStream() const
{
	return _InnerStream;
}
const bool Elysium::Core::Net::Security::AuthenticatedStream::GetLeaveInnerStreamOpen() const
{
	return _LeaveInnerStreamOpen;
}
