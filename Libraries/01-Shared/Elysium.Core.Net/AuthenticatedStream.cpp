#include "AuthenticatedStream.hpp"

Elysium::Core::Net::Security::AuthenticatedStream::AuthenticatedStream(Elysium::Core::IO::Stream& InnerStream, const bool LeaveInnerStreamOpen)
	: _InnerStream(InnerStream), _LeaveInnerStreamOpen(LeaveInnerStreamOpen)
{ }

const bool Elysium::Core::Net::Security::AuthenticatedStream::GetCanRead() const
{
	return _InnerStream.GetCanRead();
}

const bool Elysium::Core::Net::Security::AuthenticatedStream::GetCanSeek() const
{
	return _InnerStream.GetCanSeek();
}

const bool Elysium::Core::Net::Security::AuthenticatedStream::GetCanTimeout() const
{
	return _InnerStream.GetCanTimeout();
}

const bool Elysium::Core::Net::Security::AuthenticatedStream::GetCanWrite() const
{
	return _InnerStream.GetCanWrite();
}

const Elysium::Core::size Elysium::Core::Net::Security::AuthenticatedStream::GetLength()  const
{
	return _InnerStream.GetLength();
}

const bool Elysium::Core::Net::Security::AuthenticatedStream::GetLeaveInnerStreamOpen() const
{
	return _LeaveInnerStreamOpen;
}

void Elysium::Core::Net::Security::AuthenticatedStream::SetLength(const Elysium::Core::size Value)
{
	_InnerStream.SetLength(Value);
}

void Elysium::Core::Net::Security::AuthenticatedStream::SetPosition(const Elysium::Core::uint64_t Position)
{
	_InnerStream.SetPosition(Position);
}

void Elysium::Core::Net::Security::AuthenticatedStream::Close()
{
	if (!_LeaveInnerStreamOpen)
	{
		_InnerStream.Close();
	}
}

const Elysium::Core::IO::Stream& Elysium::Core::Net::Security::AuthenticatedStream::GetInnerStream() const
{
	return _InnerStream;
}
