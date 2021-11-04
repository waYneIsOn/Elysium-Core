#include "WaitHandle.hpp"

#include <assert.h>

Elysium::Core::Threading::WaitHandle::WaitHandle(const ELYSIUM_SYNCHRONIZATION_PRIMITIVE_HANDLE Handle)
	: _Handle(Handle)
{
	assert(_Handle != nullptr);
}

Elysium::Core::Threading::WaitHandle::~WaitHandle()
{
	bool WasDestroyed = ELYSIUM_SYNCHRONIZATION_PRIMITIVE_DESTROY(_Handle);
	assert(WasDestroyed == true);
}

const bool Elysium::Core::Threading::WaitHandle::WaitOne() const
{
	return WaitOne(INFINITE, false);
}

const bool Elysium::Core::Threading::WaitHandle::WaitOne(const Elysium::Core::TimeSpan & Timeout) const
{
	return WaitOne(static_cast<const Elysium::Core::int32_t>(Timeout.GetTotalMilliseconds()), false);
}

const bool Elysium::Core::Threading::WaitHandle::WaitOne(const Elysium::Core::int32_t MillisecondsTimeout) const
{
	return WaitOne(MillisecondsTimeout, false);
}

const bool Elysium::Core::Threading::WaitHandle::WaitOne(const Elysium::Core::TimeSpan & Timeout, const bool ExitContext) const
{
	return WaitOne(static_cast<const Elysium::Core::int32_t>(Timeout.GetTotalMilliseconds()), ExitContext);
}

const bool Elysium::Core::Threading::WaitHandle::WaitOne(const Elysium::Core::int32_t MillisecondsTimeout, const bool ExitContext) const
{
	return ELYSIUM_SYNCHRONIZATION_PRIMITIVE_WAIT_FOR_SINGLE_OBJECT(_Handle, MillisecondsTimeout) == WAIT_OBJECT_0;
	//GetLastError();
}
