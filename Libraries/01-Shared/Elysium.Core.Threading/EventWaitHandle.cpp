#include "EventWaitHandle.hpp"

Elysium::Core::Threading::EventWaitHandle::EventWaitHandle(const bool AutomaticallyReset, const bool InitialState, const WideString& Name)
	: _Handle(_SECURITY_ATTRIBUTES())
{
	ELYSIUM_SIGNAL_CREATE(&_Handle, AutomaticallyReset, InitialState, &Name[0]);
}
Elysium::Core::Threading::EventWaitHandle::~EventWaitHandle()
{
	// ToDo: do we need to clear before destroying?
	bool WasDestroyed = ELYSIUM_SIGNAL_DESTROY(&_Handle);
}

const bool Elysium::Core::Threading::EventWaitHandle::Set()
{
	return ELYSIUM_SIGNAL_RAISE(&_Handle);
}
const bool Elysium::Core::Threading::EventWaitHandle::Reset()
{
	return ELYSIUM_SIGNAL_CLEAR(&_Handle);
}
const bool Elysium::Core::Threading::EventWaitHandle::Wait()
{
	return ELYSIUM_SIGNAL_WAIT(&_Handle, 0) == WAIT_OBJECT_0;
}
