#include "EventWaitHandle.hpp"

Elysium::Core::Threading::EventWaitHandle::EventWaitHandle(const bool AutomaticallyReset, const bool InitialState, const Utf8String::Character* Name)
	: WaitHandle(ELYSIUM_SIGNAL_CREATE(nullptr, AutomaticallyReset, InitialState, nullptr))	// ToDo: last parameter (char8_t -> wchar_t)
{ }

Elysium::Core::Threading::EventWaitHandle::EventWaitHandle(const bool AutomaticallyReset, const bool InitialState, const Utf8String& Name)
	: EventWaitHandle(AutomaticallyReset, InitialState, &Name[0])
{ }

Elysium::Core::Threading::EventWaitHandle::~EventWaitHandle()
{ }

const bool Elysium::Core::Threading::EventWaitHandle::Set()  const
{
	return ELYSIUM_SIGNAL_RAISE(_Handle);
}

const bool Elysium::Core::Threading::EventWaitHandle::Reset() const
{
	return ELYSIUM_SIGNAL_CLEAR(_Handle);
}
