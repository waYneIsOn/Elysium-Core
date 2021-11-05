#include "AutoResetEvent.hpp"

Elysium::Core::Threading::AutoResetEvent::AutoResetEvent(const bool InitialState)
	: EventWaitHandle(true, InitialState, nullptr)
{ }

Elysium::Core::Threading::AutoResetEvent::~AutoResetEvent()
{ }
