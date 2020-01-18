#include "EventWaitHandle.hpp"

#include <assert.h>

Elysium::Core::Threading::EventWaitHandle::EventWaitHandle(const bool AutomaticallyReset, const bool InitialState, const WideString& Name)
	: _Handle(ELYSIUM_SIGNAL_CREATE(nullptr, AutomaticallyReset, InitialState, &Name[0]))
{ }
Elysium::Core::Threading::EventWaitHandle::~EventWaitHandle()
{
	bool WasDestroyed = ELYSIUM_SIGNAL_DESTROY(_Handle);
	assert(WasDestroyed == true);
}

const bool Elysium::Core::Threading::EventWaitHandle::Set()
{
	return ELYSIUM_SIGNAL_RAISE(_Handle);
}
const bool Elysium::Core::Threading::EventWaitHandle::Reset()
{
	return ELYSIUM_SIGNAL_CLEAR(_Handle);
}
const bool Elysium::Core::Threading::EventWaitHandle::WaitOne()
{
	return ELYSIUM_SIGNAL_WAIT(_Handle, -1) == WAIT_OBJECT_0;
}
