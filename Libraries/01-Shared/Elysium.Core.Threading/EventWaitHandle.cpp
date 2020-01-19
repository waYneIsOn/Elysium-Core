#include "EventWaitHandle.hpp"

Elysium::Core::Threading::EventWaitHandle::EventWaitHandle(const bool AutomaticallyReset, const bool InitialState, const WideString& Name)
	: WaitHandle(ELYSIUM_SIGNAL_CREATE(nullptr, AutomaticallyReset, InitialState, &Name[0]))
{ }
Elysium::Core::Threading::EventWaitHandle::~EventWaitHandle()
{ }

const bool Elysium::Core::Threading::EventWaitHandle::Set()
{
	return ELYSIUM_SIGNAL_RAISE(_Handle);
}
const bool Elysium::Core::Threading::EventWaitHandle::Reset()
{
	return ELYSIUM_SIGNAL_CLEAR(_Handle);
}
