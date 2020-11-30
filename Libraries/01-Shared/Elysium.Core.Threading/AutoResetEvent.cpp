#include "AutoResetEvent.hpp"

Elysium::Core::Threading::AutoResetEvent::AutoResetEvent(const bool InitialState)
	: EventWaitHandle(true, InitialState, u8"")
{ }
Elysium::Core::Threading::AutoResetEvent::~AutoResetEvent()
{ }
