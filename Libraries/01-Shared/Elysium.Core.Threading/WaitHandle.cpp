#include "WaitHandle.hpp"

#include <assert.h>

Elysium::Core::Threading::WaitHandle::~WaitHandle()
{
	if (_Handle != nullptr)
	{
		bool WasDestroyed = ELYSIUM_SYNCHRONIZATION_PRIMITIVE_DESTROY(_Handle);
		assert(WasDestroyed == true);
	}
}

const bool Elysium::Core::Threading::WaitHandle::WaitOne()
{
	return WaitOne(-1, false);
}
const bool Elysium::Core::Threading::WaitHandle::WaitOne(const TimeSpan & Timeout)
{
	return WaitOne(Timeout.GetTotalMilliseconds(), false);
}
const bool Elysium::Core::Threading::WaitHandle::WaitOne(const int32_t MillisecondsTimeout)
{
	return WaitOne(MillisecondsTimeout, false);
}
const bool Elysium::Core::Threading::WaitHandle::WaitOne(const TimeSpan & Timeout, const bool ExitContext)
{
	return WaitOne(Timeout.GetTotalMilliseconds(), ExitContext);
}
const bool Elysium::Core::Threading::WaitHandle::WaitOne(const int32_t MillisecondsTimeout, const bool ExitContext)
{
	return ELYSIUM_SYNCHRONIZATION_PRIMITIVE_WAIT_FOR_SINGLE_OBJECT(_Handle, MillisecondsTimeout) == WAIT_OBJECT_0;
}

Elysium::Core::Threading::WaitHandle::WaitHandle(const ELYSIUM_SYNCHRONIZATION_PRIMITIVE_HANDLE Handle)
	: _Handle(Handle)
{ }
