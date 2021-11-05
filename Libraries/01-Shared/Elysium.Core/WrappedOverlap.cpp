#include "WrappedOverlap.hpp"

Elysium::Core::Internal::WrappedOverlap::WrappedOverlap(const Elysium::Core::size Position, IAsyncResult* AsyncResult)
	: _Overlapped(), _AsyncResult(AsyncResult)
{
	_Overlapped.Offset = static_cast<unsigned long>(Position);
	_Overlapped.OffsetHigh = static_cast<unsigned long>(Position >> 32);
}

Elysium::Core::Internal::WrappedOverlap::~WrappedOverlap()
{ }
